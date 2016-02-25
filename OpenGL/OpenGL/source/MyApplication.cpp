#include "MyApplication.h"
#include "Renderer.h"
#include "Camera.h"
#include "aieutilities\Gizmos.h"
#include "Grid.h"
#include "glfw\glfw3.h"

#include <cstdio>

using glm::vec4;


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
	grid->GenerateGrid(10, 10);


	printOpenGLError();

	//test.LoadShader();
	//test.GenerateGrid(10, 10);

	lastFrameTime = glfwGetTime();
	//gui.Startup(renderer->GetWindow());

	Gizmos::create();

	return 0;
}

void MyApplication::Shutdown()
{
	renderer->Shutdown();
	delete renderer;
}

int MyApplication::Run()
{
	printOpenGLError();

	while (glfwWindowShouldClose(renderer->GetWindow()) == false &&
		glfwGetKey(renderer->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		printOpenGLError();
		Update();
		printOpenGLError();
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
	grid->Draw(dt, lastFrameTime, projectionView);
	//test.Draw(dt, lastFrameTime);
	//gui.Render();

	renderer->EndRender();
	//return 0;
}
