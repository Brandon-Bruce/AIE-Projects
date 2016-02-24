#include "Mesh.h"
#include "gl_core_4_4.h"
#include "Vertex.h"

unsigned int Mesh::GetVAO()
{
	return m_VAO;
}

unsigned int Mesh::GetIndexCount()
{
	return indexCount;
}

void Mesh::Create(unsigned int indexCount, Vertex* aoVerticies, unsigned int* auiIndices)
{
	//Generate GL buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Generate VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//Bind buffers to a vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, indexCount * sizeof(Vertex),
		aoVerticies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)(sizeof(glm::vec4)));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * 6 *
		sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] aoVerticies;
}

Mesh::~Mesh()
{

}
