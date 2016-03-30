#include "gl_core_4_4.h"
#include "Program.h"
#include "FBXProgram.h"
#include "FBX\FBXFile.h"
#include "Mesh.h"
#include "glm\ext.hpp"
#include "glm\vec3.hpp"
#include "AssetLoader.h"
#include "Sphere.h"
#include <string>
#include <vector>

void FBXProgram::Startup(const char* fileName, glm::mat4 position,
	char* name, float scale)
{
	this->scale = scale;
	this->name = name;
	this->position = position;

	fbx = new FBXFile();
	fbx->load(fileName);
	fbx->initialiseOpenGLTextures();
	CreateOpenGLBuffers();

	std::string vsSource = AssetLoader::ReadFile("./data/Shaders/FBXVS.txt");

	std::string fsSource = AssetLoader::ReadFile("./data/Shaders/FBXFS.txt");

	Create(vsSource, fsSource);
}

void FBXProgram::CreateOpenGLBuffers()
{
	std::vector<glm::vec3> points;
	//Create openGL VAO,VBO/IBO data
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);

		//storage for openGL data in Mesh
		Mesh* glData = new Mesh;
		unsigned int indexSize = mesh->m_indices.size();
		unsigned int vertexSize = mesh->m_vertices.size() * sizeof(FBXVertex);
		FBXVertex* vertices = mesh->m_vertices.data();

		glData->Create(indexSize, mesh->m_indices.data(),
			vertexSize, nullptr, vertices);

		unsigned int vertexCount = mesh->m_vertices.size();
		//collect data for sphere collider
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			points.push_back((glm::vec3)vertices[i].position);
		}

		mesh->m_userData = glData;
	}

	collider = new SphereCollider;
	collider->Set(points, scale);
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

void FBXProgram::Draw(glm::mat4 projectionView, Camera* camera)
{
	//Frustrum culling
	collider->Update((glm::vec3)position[3]);
	if (CollisionDetection::DetectCollision(collider, camera, name) == false)
		return;

	GLuint program = GetProgramID();
	glUseProgram(program);

	//bind camera
	unsigned int loc = glGetUniformLocation(program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionView));

	loc = glGetUniformLocation(program, "lightDirection");
	glm::vec3 lightDirection = glm::normalize(glm::vec3(1, 1, 1));
	glUniform3f(loc, lightDirection.x, lightDirection.y, lightDirection.z);

	loc = glGetUniformLocation(program, "lightColor");
	glUniform3f(loc, 1.f, 1.f, 1.f);
	
	loc = glGetUniformLocation(program, "diffuse");
	glUniform1i(loc, 0);

	loc = glGetUniformLocation(program, "World");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(position));

	//Bind vertex array object and draw mesh
	for (unsigned int i = 0; i < fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = fbx->getMeshByIndex(i);
		Mesh* glData = (Mesh*)mesh->m_userData;

		FBXTexture* texture = mesh->m_material->textures[FBXMaterial::DiffuseTexture];
		if (texture != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->handle);
		}

		glBindVertexArray(glData->GetVAO());
		glDrawElements(GL_TRIANGLES, (unsigned int)glData->GetIndexCount(),
			GL_UNSIGNED_INT, 0);
	}
}
