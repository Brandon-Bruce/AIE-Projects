#include "glm\ext.hpp"
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include "PerlinNoise.h"
#include "Vertex.h"
#include "Program.h"
#include "Mesh.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

void PerlinNoise::Create(unsigned int rows, unsigned int colums)
{
	LoadShader();
	GenerateMeshAndNoise(rows, colums);
}

void PerlinNoise::LoadShader()
{
	//Create shader
	const char* vsSource = "#version 410\n \
							layout(location = 0) in vec4 Position; \
							layout(location = 1) in vec2 TexCoord; \
							uniform mat4 ProjectionView; \
							out vec2 FragTexCoord; \
							void main() \
							{ \
								FragTexCoord = TexCoord; \
								gl_Position = ProjectionView * Position; \
							}";

	const char* fsSource = "#version 410\n \
							in vec2 FragTexCoord; \
							out vec4 Color; \
							uniform sampler2D PerlinTexture; \
							void main() \
							{ \
								Color = texture(PerlinTexture, FragTexCoord).rrrr; \
								Color.a = 1; \
							}";

	program = new Program;
	program->Create(vsSource, fsSource);
}

void PerlinNoise::GenerateMeshAndNoise(unsigned int rows, unsigned int colums)
{
	float scale = GeneratePerlinNoise(rows, colums);

	int vertexCount = rows * colums;
	NoiseVertex* verticies = new NoiseVertex[vertexCount];


	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < colums; ++c)
		{
			unsigned int index = r * colums + c;
			verticies[index].position = vec4((float)c, 0, (float)r, 1);

			vec2 texCoord = (vec2(r, c) * scale) * 0.5f + 0.5f;
			verticies[index].texcoord = vec2(r, c) * scale;
		}
	}

	//Defining index count based off quad count (2 triangles per quad)
	int indexCount = (rows - 1) * (colums - 1) * 6;
	unsigned int* auiIndices = new unsigned int[indexCount];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (colums - 1); ++c)
		{
			//triangle 1
			auiIndices[index++] = r * colums + c;
			auiIndices[index++] = (r + 1) * colums + c;
			auiIndices[index++] = (r + 1) * colums + (c + 1);

			//triangle 2
			auiIndices[index++] = r * colums + c;
			auiIndices[index++] = (r + 1) * colums + (c + 1);
			auiIndices[index++] = r * colums + (c + 1);
		}
	}

	mesh = new Mesh;
	mesh->Create(indexCount, auiIndices, vertexCount * sizeof(NoiseVertex), nullptr, nullptr, verticies);
}

float PerlinNoise::GeneratePerlinNoise(unsigned int rows, unsigned int colums)
{
	float* perlinData = new float[rows * colums];
	float scale = (1.0f / rows) * 3;

	for (unsigned int x = 0; x < rows; ++x)
	{
		for (unsigned int y = 0; y < colums; ++y)
		{
			unsigned int index = x * colums + y;
			perlinData[index] = glm::perlin(vec2(x, y) * scale) * 0.5f + 0.5f;
		}
	}

	//generate perlin noise texture
	glGenTextures(1, &perlinTexture);
	glBindTexture(GL_TEXTURE_2D, perlinTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, colums, rows, 0, GL_RED, GL_FLOAT, perlinData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return scale;
}

void PerlinNoise::Draw(double deltatime, double time, glm::mat4 projectionView)
{
	GLuint m_programID = program->GetProgramID();
	glUseProgram(m_programID);

	//Set variables for shader

	//Camera
	unsigned int loc = glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE,
		glm::value_ptr(projectionView));

	//Perlin noise texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, perlinTexture);

	loc = glGetUniformLocation(m_programID, "PerlinTexture");
	glUniform1i(loc, 0);

	//bind verticies
	glBindVertexArray(mesh->GetVAO());
	glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}
