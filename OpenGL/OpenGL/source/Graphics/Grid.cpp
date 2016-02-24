#include "Grid.h"
#include "glm\vec3.hpp"
#include "glm\ext.hpp"
#include "Vertex.h"

using glm::vec4;
using glm::vec3;


Grid::~Grid()
{

}

void Grid::LoadShader()
{
	//Create shader
	const char* vsSource =	"#version 410\n"
							"layout(location = 0) in vec4 Position;"
							"layout(location = 1) in vec4 Colour;"
							"out vec4 vColour;"
							"uniform mat4 ProjectionView;"
							"uniform float time;"
							"uniform float heightScale;"
							"void main()"
							"{"
								"vColour = Colour;"
								"vec4 P = Position;"
								"P.y += sin( time + Position.x ) * heightScale;"
								"gl_Position = ProjectionView * P;"
							"}";

	const char* fsSource =	"#version 410\n"
							"in vec4 vColour;"
							"out vec4 FragColor;"
							"void main() { FragColor = vColour; }";

	program.Create(vsSource, fsSource);
}

void Grid::GenerateGrid(unsigned int rows, unsigned int cols)
{
	Vertex* aoVerticies = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVerticies[r*cols + c].position = vec4((float)c, 0, (float)r, 1);

			//create arbitrary colour based off something
			//that might not be related to tiling a texture
			vec3 colour = vec3(sinf((c / (float)(cols - 1)) *
									(r / (float)(rows - 1))));
			aoVerticies[r * cols + c].colour = vec4(colour, 1);
		}
	}

	//Defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			//triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	mesh.Create(rows * cols, aoVerticies, auiIndices);
}

void Grid::Draw(double deltatime, double time)
{

}
