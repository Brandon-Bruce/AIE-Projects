#ifndef FBXPROGRAM_H
#define FBXPROGRAM_H

#include "Program.h"
#include "glm\mat4x4.hpp"

class FBXFile;
class Camera;
class SphereCollider;

class FBXProgram : public Program
{
public:
	void Startup(const char* fileName, glm::mat4 position,
		char* name, float scale);
	void CreateOpenGLBuffers();
	void CleanUpOpenGLBuffers();

	void Draw(glm::mat4 projectionView, Camera* camera);

private:
	FBXFile* fbx;
	glm::mat4 position;
	char* name;
	SphereCollider* collider;
	float scale;
};

#endif