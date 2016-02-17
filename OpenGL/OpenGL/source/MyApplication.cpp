#include "MyApplication.h"
#include "glfw\glfw3.h"
#include "GraphicsManager.h"
#include "Camera.h"

MyApplication& MyApplication::GetApplication()
{
	static MyApplication instance;
	return instance;
}

int MyApplication::Startup()
{
	if (GRAPHICSMANAGER.Startup())
	{
		return -1;
	}

	test.LoadShader();
	test.GenerateGrid(10, 10);

	lastFrameTime = glfwGetTime();

	return 0;
}

void MyApplication::Shutdown()
{
	glfwTerminate();
}

int MyApplication::Run()
{
	while (glfwWindowShouldClose(GRAPHICSMANAGER.GetWindow()) == false &&
		glfwGetKey(GRAPHICSMANAGER.GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		Update();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Draw();
		glfwSwapBuffers(GRAPHICSMANAGER.GetWindow());
	}
	return 0;
}

int MyApplication::Update()
{
	//Calculate delta time
	float now = glfwGetTime();
	dt = now - lastFrameTime;
	lastFrameTime = now;

	GRAPHICSMANAGER.GetCamera()->Update(dt);
	return 0;
}

int MyApplication::Draw()
{
	test.Draw(dt, lastFrameTime);
	return 0;
}
