#include "Mesh.h"
#include "gl_core_4_4.h"
#include "Vertex.h"
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
	NoiseVertex* noiseVerticies)
{
	this->indexCount = indexCount;

	//Generate GL buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Generate VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	SetUpVertixArrayObject(vertexSize, aoVerticies, fbxVerticies, noiseVerticies);

	//Bind buffers to a index array object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount *
		sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetUpVertixArrayObject(int vertexSize, Vertex* aoVerticies, FBXVertex* fbxVerticies, NoiseVertex* noiseVerticies)
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
}

void Mesh::SetUpVertexBuffers(NoiseVertex * noiseVerticies)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(NoiseVertex),
		0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(NoiseVertex),
		(void*)(sizeof(glm::vec4)));
}

void Mesh::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}