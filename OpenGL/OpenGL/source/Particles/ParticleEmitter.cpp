#include "ParticleEmitter.h"
#include "Particles.h"
#include "Mesh.h"
#include "glm\ext.hpp"

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

	mesh->Create(indexCount, indexData, vertexCount, nullptr, nullptr, nullptr, vertexData);

	delete[] indexData;
}

ParticleEmitter::~ParticleEmitter()
{
	delete[] particles;
	delete[] vertexData;

	mesh->Destroy();
	delete mesh;
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
	particle.lifespan = 0;
	particle.lifespan = (rand() / (float)RAND_MAX) *
		(maxLifeSpan - minLifeSpan) + minLifeSpan;

	//ste starting color and size
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

void ParticleEmitter::UpdateParticles(float deltaTime,
	const glm::mat4& cameraTransform)
{
	//spawn particles
	emitTimer += deltaTime;
	while (emitTimer > emitRate)
	{
		EmitParticles();
		emitTimer -= emitRate;
	}
}

void ParticleEmitter::DrawParticles()
{
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
