#ifndef PARTICLES_H
#define PARTICLES_H

#include "glm\vec3.hpp"
#include "glm\vec4.hpp"

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 color;
	float size;
	double lifetime;
	double lifespan;
};

struct ParticleVertex
{
	glm::vec4 position;
	glm::vec4 color;
};


#endif