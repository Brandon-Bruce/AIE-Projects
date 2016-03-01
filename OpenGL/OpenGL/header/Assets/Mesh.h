#ifndef MESH_H
#define MESH_H

struct Vertex;
struct NoiseVertex;
class FBXVertex;

class Mesh
{
public:
	unsigned int GetVAO();
	unsigned int GetIndexCount();
	void Create(unsigned int indexCount, unsigned int* auiIndices, int vertexSize,
		Vertex* aoVerticies = nullptr,
		FBXVertex* fbxVerticies = nullptr,
		NoiseVertex* noiseVerticies = nullptr);
	void Destroy();

private:
	void SetUpVertixArrayObject(int vertexSize, Vertex* AoVerticies, FBXVertex* fbxVerticies, NoiseVertex* noiseVerticies);
	void SetUpVertexBuffers(Vertex* verticies);
	void SetUpVertexBuffers(FBXVertex* verticies);
	void SetUpVertexBuffers(NoiseVertex* noiseVerticies);

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int indexCount;
};

#endif