#ifndef MESH_H
#define MESH_H

struct Vertex;
struct TexVertex;
class FBXVertex;
struct ParticleVertex;

class Mesh
{
public:
	unsigned int GetVAO();
	unsigned int GetVBO();
	unsigned int GetIndexCount();
	void Create(unsigned int indexCount, unsigned int* auiIndices, int vertexSize,
		Vertex* aoVerticies = nullptr,
		FBXVertex* fbxVerticies = nullptr,
		TexVertex* noiseVerticies = nullptr,
		ParticleVertex* particleVertices = nullptr);
	void Destroy();

private:
	void SetUpVertixArrayObject(int vertexSize,
		Vertex* AoVerticies,
		FBXVertex* fbxVerticies,
		TexVertex* noiseVerticies,
		ParticleVertex* particleVertices);
	void SetUpVertexBuffers(Vertex* verticies);
	void SetUpVertexBuffers(FBXVertex* verticies);
	void SetUpVertexBuffers(TexVertex* noiseVerticies);
	void SetUpVertexBuffers(ParticleVertex* particleVertices);

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int indexCount;
};

#endif