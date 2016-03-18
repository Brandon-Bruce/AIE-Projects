#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particles.h"
#include <vector>

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	void EmitParticles();
	void UpdateParticles();
	void DrawParticles();

private:
	std::vector<Particle>
};

#endif