#include "MyApplication.h"
#include "glfw\glfw3.h"
#include "Renderer.h"
#include "Camera.h"
#include "aieutilities\Gizmos.h"

using glm::vec4;

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

	test.LoadShader();
	test.GenerateGrid(10, 10);

	lastFrameTime = glfwGetTime();
	gui.Startup(renderer->GetWindow());

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
	while (glfwWindowShouldClose(renderer->GetWindow()) == false &&
		glfwGetKey(renderer->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		Update();
		Draw();
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

	test.Draw(dt, lastFrameTime);
	gui.Render();

	renderer->EndRender();
	return 0;
}
