#ifndef FBXPROGRAM_H
#define FBXPROGRAM_H

#include "Program.h"
#include "glm\mat4x4.hpp"

class FBXFile;

class FBXProgram : public Program
{
public:
	void Startup(const char* fileName);
	void CreateOpenGLBuffers();
	void CleanUpOpenGLBuffers();

	void Draw(glm::mat4 projectionView);

private:
	FBXFile* fbx;
	glm::mat4 position;
};

#endif