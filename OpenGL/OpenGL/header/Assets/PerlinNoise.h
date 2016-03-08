#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "glm\mat4x4.hpp"

class Program;
class Mesh;

class PerlinNoise
{
public:
	void Create(unsigned int rows, unsigned int colums);
	void Draw(double deltatime, double time, glm::mat4 projectionView);

private:
	void LoadShader();
	void GenerateMeshAndNoise(unsigned int rows, unsigned int colums);
	float GeneratePerlinNoise(unsigned int rows, unsigned int colums);

	Mesh* mesh;
	Program* program;
	unsigned int perlinTexture;
};

#endif // !PERLINNOISE_H