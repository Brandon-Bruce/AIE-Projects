#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "gl_core_4_4.h"
#include "Mesh.h"
#include "Program.h"
#include "glm\mat4x4.hpp"

class PerlinNoise
{
public:
	void Create(unsigned int rows, unsigned int colums);
	void Draw(double deltatime, double time, glm::mat4 projectionView);

private:
	void LoadShader();
	void GenerateGrid(unsigned int rows, unsigned int colums);
	void GeneratePerlinNoise(unsigned int rows, unsigned int colums);

	Mesh mesh;
	GLuint perlinTexture;
	Program program;
};

#endif // !PERLINNOISE_H