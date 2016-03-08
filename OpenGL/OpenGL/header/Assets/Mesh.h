#ifndef MESH_H
#define MESH_H

struct Vertex;
struct TexVertex;
class FBXVertex;

class Mesh
{
public:
	unsigned int GetVAO();
	unsigned int GetIndexCount();
	void Create(unsigned int indexCount, unsigned int* auiIndices, int vertexSize,
		Vertex* aoVerticies = nullptr,
		FBXVertex* fbxVerticies = nullptr,
		TexVertex* noiseVerticies = nullptr);
	void Destroy();

private:
	void SetUpVertixArrayObject(int vertexSize, Vertex* AoVerticies, FBXVertex* fbxVerticies, TexVertex* noiseVerticies);
	void SetUpVertexBuffers(Vertex* verticies);
	void SetUpVertexBuffers(FBXVertex* verticies);
	void SetUpVertexBuffers(TexVertex* noiseVerticies);

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int indexCount;
};

#endif