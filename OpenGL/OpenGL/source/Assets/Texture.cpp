#include "gl_core_4_4.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Program.h"
#include "Mesh.h"
#include "Vertex.h"
#include "glm\ext.hpp"

using glm::vec4;
using glm::vec2;

void Texture::Create(const char* filename)
{
	height = 0; width = 0; format = 0;

	unsigned char* texelData = stbi_load(filename, &width, &height, &format, STBI_default);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texelData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(texelData);

	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 Position; \
							layout(location=1) in vec2 TexCoord; \
							out vec2 vTexCoord; \
							uniform mat4 ProjectionView; \
							void main() {\
							vTexCoord = TexCoord; \
							gl_Position = ProjectionView * Position; }";

	const char* fsSource = "#version 410\n \
							in vec2 vTexCoord; \
							out vec4 FragColor; \
							uniform sampler2D Diffuse; \
							void main() {\
							FragColor = texture(Diffuse,vTexCoord); }";

	program = new Program;
	program->Create(vsSource, fsSource);

	CreateMesh();
}

void Texture::Destroy()
{
	program->CleanUp();
	mesh->Destroy();

	delete program;
	delete mesh;
}

void Texture::Draw(glm::mat4 projectionView)
{
	//use program
	unsigned int programID = program->GetProgramID();
	glUseProgram(programID);

	//bind camera
	int loc = glGetUniformLocation(programID, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionView));

	//set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//tell shader texture location
	loc = glGetUniformLocation(programID, "Diffuse");
	glUniform1i(loc, 0);

	//draw
	glBindVertexArray(mesh->GetVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Texture::CreateMesh()
{
	TexVertex verticies[] = { {vec4(-5,0,5,1),vec2(0,1)},
							{vec4(5,0,5,1),vec2(1,1)},
							{vec4(5,0,-5,1),vec2(1,0)},
							{vec4(-5,0,-5,1),vec2(0,0)} };

	unsigned int indexData[] = { 0,1,2,
								0,2,3 };

	mesh = new Mesh;
	mesh->Create(sizeof(unsigned int) * 6, indexData, sizeof(TexVertex) * 4, nullptr, nullptr, verticies);
}
