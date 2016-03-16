#include "gl_core_4_4.h"
#include "Program.h"
#include "FBXProgram.h"
#include "FBX\FBXFile.h"
#include "Mesh.h"
#include "glm\ext.hpp"
#include "AssetLoader.h"
#include <string>

void FBXProgram::Startup(const char* fileName)
{
	this->position = position;

	fbx = new FBXFile();
	fbx->load(fileName);
	CreateOpenGLBuffers();

	std::string vsSource = AssetLoader::ReadFile("./data/FBXShaderVS.txt");

	std::string fsSource = AssetLoader::ReadFile("./data/FBXShaderFS.txt");

	Create(vsSource, fsSource);
}

void FBXProgram::CreateOpenGLBuffers()
{
	//Create openGL VAO,VBO/IBO data
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);

		//storage for openGL data in Mesh
		Mesh* glData = new Mesh;
		unsigned int indexSize = mesh->m_indices.size();
		unsigned int vertexSize = mesh->m_vertices.size() * sizeof(FBXVertex);

		glData->Create(indexSize, mesh->m_indices.data(),
			vertexSize, nullptr, mesh->m_vertices.data());

		mesh->m_userData = glData;
	}
}

void FBXProgram::CleanUpOpenGLBuffers()
{
	//Clean up vertex data attached to meshs
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);
		Mesh* glData = (Mesh*)mesh->m_userData;
		glData->Destroy();
		delete glData;
	}
}

void FBXProgram::Draw(glm::mat4 projectionView)
{
	GLuint program = GetProgramID();
	glUseProgram(program);
	glGetError();

	//bind camera
	unsigned int loc = glGetUniformLocation(program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionView));
	glGetError();

	//Bind vertex array object and draw mesh
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);

		Mesh* glData = (Mesh*)mesh->m_userData;

		glBindVertexArray(glData->GetVAO());
		glGetError();
		glDrawElements(GL_TRIANGLES, (unsigned int)glData->GetIndexCount(),
			GL_UNSIGNED_INT, 0);
		glGetError();
	}
}
