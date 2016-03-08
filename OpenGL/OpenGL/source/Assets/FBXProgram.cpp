#include "gl_core_4_4.h"
#include "Program.h"
#include "FBXProgram.h"
#include "FBX\FBXFile.h"
#include "Mesh.h"
#include "glm\ext.hpp"

void FBXProgram::Startup(const char* fileName)
{
	this->position = position;

	fbx = new FBXFile();
	fbx->load(fileName);
	CreateOpenGLBuffers();

	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 Position; \
							layout(location=1) in vec4 Normal; \
							out vec4 vNormal; \
							uniform mat4 ProjectionView; \
							void main() { vNormal = Normal; \
							gl_Position = ProjectionView * Position; }";

	const char* fsSource = "#version 410\n \
							in vec4 vNormal; \
							out vec4 FragColor; \
							void main() { \
							FragColor = vec4(1,1,1,1); }";

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

	//bind camera
	unsigned int loc = glGetUniformLocation(program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionView));

	//Bind vertex array object and draw mesh
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);

		Mesh* glData = (Mesh*)mesh->m_userData;

		glBindVertexArray(glData->GetVAO());
		glDrawElements(GL_TRIANGLES, (unsigned int)glData->GetIndexCount(),
			GL_UNSIGNED_INT, 0);
	}
}
