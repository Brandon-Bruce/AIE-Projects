#include "gl_core_4_4.h"
#include "ParticleEmitter.h"
#include "Particles.h"
#include "Mesh.h"
#include "glm\ext.hpp"
#include "Program.h"
#include "AssetLoader.h"

using glm::vec3;
using glm::vec4;

ParticleEmitter::ParticleEmitter()
	: particles(nullptr),
	firstDead(0),
	maxParticles(0),
	position(0, 0, 0),
	vertexData(nullptr)
{
	mesh = new Mesh;
}

void ParticleEmitter::Initalise(unsigned int maxParticles,
	unsigned int emitRate,
	float minLifeTime, float maxLifeTime,
	float minVelocity, float maxVelocity,
	float startSize, float endSize,
	const glm::vec4& startColor, const glm::vec4& endColor)
{
	//Set up emit timer
	this->emitTimer = 0; this->emitRate = 1.0f / emitRate;

	//store variables passed in
	this->maxParticles = maxParticles;
	this->minLifeSpan = minLifeTime, this->maxLifeSpan = maxLifeTime;
	this->minVelocity = minVelocity; this->maxVelocity = maxVelocity;
	this->startSize = startSize; this->endSize = endSize;
	this->startColor = startColor; this->endColor = endColor;

	//create particle array
	particles = new Particle[maxParticles];
	firstDead = 0;

	//create array for vertices
	unsigned int vertexCount = maxParticles * 4;
	vertexData = new ParticleVertex[vertexCount];

	//creat index buffer
	unsigned int indexCount = maxParticles * 6;
	unsigned int* indexData = CreateIndexBuffer(indexCount);

	mesh->Create(indexCount, indexData, vertexCount * sizeof(ParticleVertex), nullptr, nullptr, nullptr, vertexData);

	delete[] indexData;

	std::string vsShader = AssetLoader::ReadFile("./data/Shaders/ParticleVS.txt");
	std::string fsShader = AssetLoader::ReadFile("./data/Shaders/ParticleFS.txt");

	program = new Program;
	program->Create(vsShader, fsShader);
}

ParticleEmitter::~ParticleEmitter()
{
	delete[] particles;
	delete[] vertexData;

	mesh->Destroy();
	program->CleanUp();
	delete mesh;
	delete program;
}

void ParticleEmitter::EmitParticles()
{
	//Only emit if there is a dead particle to use
	if (firstDead >= maxParticles)
		return;

	//resurrect the first dead particle
	Particle& particle = particles[firstDead++];

	//assign its start position
	particle.position = position;

	//randomise its lifespan
	particle.lifetime = 0;
	particle.lifespan = (rand() / (float)RAND_MAX) *
		(maxLifeSpan - minLifeSpan) + minLifeSpan;

	//set starting color and size
	particle.color = startColor;
	particle.size = startSize;

	//randomize velocity direction and strength
	float velocity = (rand() / (float)RAND_MAX) *
		(maxVelocity - minVelocity) + minVelocity;
	particle.velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity = glm::normalize(particle.velocity) *
		velocity;
}

void ParticleEmitter::UpdateParticles(double deltaTime,
	const glm::mat4& cameraTransform)
{
	//spawn particles
	emitTimer += deltaTime;
	while (emitTimer > emitRate)
	{
		EmitParticles();
		emitTimer -= emitRate;
	}
	unsigned int quad = 0;

	//update particles and turn live paricles into billboard quads
	for (unsigned int i = 0; i < firstDead; ++i)
	{
		Particle* particle = &particles[i];

		particle->lifetime += deltaTime;
		if (particle->lifetime >= particle->lifespan)
		{
			//swap last alive particle with this one
			*particle = particles[firstDead - 1];
			--firstDead;
		}

		if (i < firstDead)
		{
			//move particle
			particle->position += particle->velocity * deltaTime;

			//size particle
			particle->size = glm::mix(startSize, endSize,
				particle->lifetime / particle->lifespan);

			//colour particle
			particle->color = glm::mix(startColor, endColor,
				particle->lifetime / particle->lifespan);

			//make quad with correct size and colour
			float halfSize = particle->size * 0.5f;

			vertexData[quad * 4 + 0].position = vec4(halfSize,
				halfSize, 0, 1);
			vertexData[quad * 4 + 0].color = particle->color;

			vertexData[quad * 4 + 1].position = vec4(-halfSize,
				halfSize, 0, 1);
			vertexData[quad * 4 + 1].color = particle->color;

			vertexData[quad * 4 + 2].position = vec4(-halfSize,
				-halfSize, 0, 1);
			vertexData[quad * 4 + 2].color = particle->color;

			vertexData[quad * 4 + 3].position = vec4(halfSize,
				-halfSize, 0, 1);
			vertexData[quad * 4 + 3].color = particle->color;

			//create billboard transform
			vec3 zAxis = glm::normalize(vec3(cameraTransform[3]) -
				particle->position);
			vec3 xAxis = glm::cross(vec3(cameraTransform[1]), zAxis);
			vec3 yAxis = glm::cross(zAxis, xAxis);
			glm::mat4 billboard(vec4(xAxis, 0),
				vec4(yAxis, 0),
				vec4(zAxis, 0),
				vec4(0, 0, 0, 1));

			for (int j = 0; j < 4; ++j)
			{
				vertexData[quad * 4 + j].position = billboard *
					vertexData[quad * 4 + j].position +
					vec4(particle->position, 0);
			}
			++quad;
		}
	}
}

void ParticleEmitter::DrawParticles(const glm::mat4& cameraTransform)
{
	//set upprogram and projection view uniform
	unsigned int programID = program->GetProgramID();
	glUseProgram(programID);
	int loc = glGetUniformLocation(programID, "projectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(cameraTransform));

	//sync particle vertex buffer based on alive particles
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, firstDead * 4 *
		sizeof(ParticleVertex), vertexData);

	//draw particles
	glBindVertexArray(mesh->GetVAO());
	glDrawElements(GL_TRIANGLES, firstDead * 6, GL_UNSIGNED_INT, 0);
}

unsigned int* ParticleEmitter::CreateIndexBuffer(unsigned int indexCount)
{
	unsigned int* indexData = new unsigned int[indexCount];
	for (unsigned int i = 0; i < maxParticles; ++i)
	{
		indexData[i * 6 + 0] = i * 4 + 0;
		indexData[i * 6 + 1] = i * 4 + 1;
		indexData[i * 6 + 2] = i * 4 + 2;

		indexData[i * 6 + 3] = i * 4 + 0;
		indexData[i * 6 + 4] = i * 4 + 2;
		indexData[i * 6 + 5] = i * 4 + 3;
	}

	return indexData;
}
