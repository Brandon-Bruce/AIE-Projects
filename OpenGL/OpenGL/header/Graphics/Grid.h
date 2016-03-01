#ifndef SHADER_H
#define SHADER_H

#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"
#include "Program.h"
#include "Mesh.h"

class Grid
{
public:
	~Grid();

	virtual void LoadShader();
	//Create a grid
	void GenerateGrid(unsigned int rows, unsigned int cols);
	//Draw grid
	void Draw(double deltatime, double time, glm::mat4 projectionView);

protected:
	Mesh mesh;
	Program program;
};

#endif // !SHADER_H