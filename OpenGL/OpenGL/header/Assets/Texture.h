#ifndef TEXTURE_H
#define TEXTURE_H

#include <STB\stb_image.h>
#include "glm\mat4x4.hpp"

class Program;
class Mesh;

class Texture
{
public:
	void Create(const char* filename);
	void Destroy();

	void Draw(glm::mat4 projectionView);

private:
	void CreateMesh();

	Program* program;
	Mesh* mesh;
	unsigned int m_texture;
	int height;
	int width;
	int format;
};

#endif