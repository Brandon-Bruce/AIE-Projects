#include "ParticleEmitter.h"
#include "Particles.h"
#include "Mesh.h"

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
	this->minVelocity = minVelocity; this->maxVeocity = maxVelocity;
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
}

void ParticleEmitter::UpdateParticles()
{
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
