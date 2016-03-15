#include "FBXProgram.h"
#include "MyApplication.h"
#include "Camera.h"
//#include "aieutilities\Gizmos.h"
#include "Grid.h"
#include "glfw\glfw3.h"
#include "PerlinNoise.h"
#include "Texture.h"

#include <cstdio>

using glm::vec4;
using glm::mat4;

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{

	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	if (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d\n",
			file, line);
		retCode = 1;
	}
	return retCode;
}

MyApplication& MyApplication::GetApplication()
{
	static MyApplication instance;
	return instance;
}

int MyApplication::Startup()
{
	renderer = new Renderer;
	if (renderer->Startup())
		return -1;

	grid = new Grid;
	grid->LoadShader();
	grid->GenerateGrid(64, 64);

	bunny = new FBXProgram;
	bunny->Startup("./data/Bunny.fbx");

	//dragon = new FBXProgram;
	//mat4 dragonPos = mat4();
	//dragonPos[3] = vec4(10, 10, 10, 0);
	//dragon->Startup("./data/Dragon.fbx", dragonPos);

	perlinNoise = new PerlinNoise;
	perlinNoise->Create(64, 64);

	crate = new Texture;
	crate->Create();

	printOpenGLError();

	//test.LoadShader();
	//test.GenerateGrid(10, 10);

	lastFrameTime = glfwGetTime();
	//gui.Startup(renderer->GetWindow());

	//Gizmos::create();

	return 0;
}

void MyApplication::Shutdown()
{
	//delete dragon;
	bunny->CleanUp();
	crate->Destroy();
	renderer->Shutdown();
	delete bunny;
	delete crate;
	delete renderer;
}

int MyApplication::Run()
{
	printOpenGLError();

	while (glfwWindowShouldClose(renderer->GetWindow()) == false &&
		glfwGetKey(renderer->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		Update();
		Draw();
		printOpenGLError();
	}
	return 0;
}

int MyApplication::Update()
{
	//Calculate delta time
	double now = glfwGetTime();
	dt = now - lastFrameTime;
	lastFrameTime = now;

	//Get keyboard events
	glfwPollEvents();

	renderer->GetCamera()->Update(dt);
	return 0;
}

void MyApplication::Draw()
{
	renderer->BeginRender();

	glm::mat4 projectionView = renderer->GetCamera()->GetProjectionView();
	//grid->Draw(dt, lastFrameTime, projectionView);
	perlinNoise->Draw(dt, lastFrameTime, projectionView);
	crate->Draw(projectionView);
	//bunny->Draw(projectionView);
	//dragon->Draw(projectionView);
	//test.Draw(dt, lastFrameTime);
	//gui.Render();

	renderer->EndRender();
	//return 0;
}
