#ifndef SHADER_H
#define SHADER_H

#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;
};

class Shader
{
public:
	~Shader();

	void LoadShader();
	//Create a grid
	void GenerateGrid(unsigned int rows, unsigned int cols);
	//Draw grid
	void Draw(float deltatime, float time);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_programID;
	unsigned int rows;
	unsigned int cols;
};

#endif // !SHADER_H