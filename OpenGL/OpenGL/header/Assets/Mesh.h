#ifndef MESH_H
#define MESH_H

class Mesh
{
public:
	void Create(unsigned int indexCount, Vertex* aoVerticies, unsigned int* auiIndices);
	~Mesh();

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int indexCount;
};

#endif