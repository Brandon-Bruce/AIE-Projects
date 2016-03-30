#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <vector>
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"

struct Particle;
struct ParticleVertex;
class Mesh;
class Program;
class GUI;

class ParticleEmitter
{
public:
	ParticleEmitter();
	void Initalise(unsigned int maxParticles,
		unsigned int emitRate,
		float minLifeTime, float maxLifeTime,
		float minVelocity, float maxVelocity,
		float startSize, float endSize,
		const glm::vec4& startColor, const glm::vec4& endColor,
		GUI* gui);
	~ParticleEmitter();

	void EmitParticles();
	void UpdateParticles(double deltaTime,
		const glm::mat4& cameraTransform);
	void DrawParticles(const glm::mat4& cameraTransform);

private:
	unsigned int* CreateIndexBuffer(unsigned int indexCount);
	void GUIRender();

	Particle* particles;
	unsigned int firstDead;
	unsigned int maxParticles;
	ParticleVertex* vertexData;

	Program* program;
	Mesh* mesh;

	glm::vec3 position;

	float emitTimer;
	float emitRate;

	float minLifeSpan;
	float maxLifeSpan;

	float minVelocity;
	float maxVelocity;

	float startSize;
	float endSize;

	glm::vec4 startColor;
	glm::vec4 endColor;

	GUI* gui;
};

#endif