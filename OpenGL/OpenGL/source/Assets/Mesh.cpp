#include "gl_core_4_4.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Particles.h"
#include "FBX\FBXFile.h"

unsigned int Mesh::GetVAO()
{
	return m_VAO;
}

unsigned int Mesh::GetIndexCount()
{
	return indexCount;
}

void Mesh::Create(unsigned int indexCount, unsigned int* auiIndices, int vertexSize,
	Vertex* aoVerticies,
	FBXVertex* fbxVerticies,
	TexVertex* noiseVerticies,
	ParticleVertex* particleVertices)
{
	this->indexCount = indexCount;

	//Generate GL buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Generate VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	SetUpVertixArrayObject(vertexSize, aoVerticies, fbxVerticies, noiseVerticies, particleVertices);

	//Bind buffers to a index array object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount *
		sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetUpVertixArrayObject(int vertexSize,
	Vertex* aoVerticies,
	FBXVertex* fbxVerticies,
	TexVertex* noiseVerticies,
	ParticleVertex* particleVertices)
{
	//Set up Vertex Array Object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (aoVerticies != nullptr)
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize,
			aoVerticies, GL_STATIC_DRAW);
		SetUpVertexBuffers(aoVerticies);
		delete[] aoVerticies;
	}
	if (fbxVerticies != nullptr)
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize,
			fbxVerticies, GL_STATIC_DRAW);
		SetUpVertexBuffers(fbxVerticies);
		//delete[] fbxVerticies;
	}
	if (noiseVerticies != nullptr)
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize,
			noiseVerticies, GL_STATIC_DRAW);
		SetUpVertexBuffers(noiseVerticies);
	}
	if (particleVertices != nullptr)
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize,
			particleVertices, GL_DYNAMIC_DRAW);
		SetUpVertexBuffers(particleVertices);
	}
}

void Mesh::SetUpVertexBuffers(Vertex* verticies)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)(sizeof(glm::vec4)));
}

void Mesh::SetUpVertexBuffers(FBXVertex* verticies)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(FBXVertex), 
		((char*)0) + FBXVertex::NormalOffset);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex),
		((char*)0) + FBXVertex::TexCoord1Offset);
}

void Mesh::SetUpVertexBuffers(TexVertex * noiseVerticies)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(TexVertex),
		0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TexVertex),
		(void*)(sizeof(glm::vec4)));
}

void Mesh::SetUpVertexBuffers(ParticleVertex * particleVertices)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		((char*)0) + 16);
}

void Mesh::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}