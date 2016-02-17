#include "GraphicsManager.h"
#include <iostream>
#include "gl_core_4_4.h"
#include "glfw\glfw3.h"
#include "FlyCamera.h"
#include "Shader.h"

using std::cout;

void openglCallbackFunction(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar * message,
	const void * userParam);

GraphicsManager& GraphicsManager::GetGraphicsManager()
{
	static GraphicsManager instance;
	return instance;
}

int GraphicsManager::Startup()
{
	//Initiate GLFW library
	if (glfwInit() == false)
		return -1;

	//Create window
	window = glfwCreateWindow(1280, 720,
		"Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	//Make window current
	glfwMakeContextCurrent(window);

	//Load openGL functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	glClearColor(0.5f, 0.5f, 0.25f, 1); //Set background colour
	glEnable(GL_DEPTH_TEST); //Enable depth buffer

	camera = new FlyCamera;

	return 0;
}

void GraphicsManager::Shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete camera;
}

Camera* GraphicsManager::GetCamera()
{
	return camera;
}

GLFWwindow* GraphicsManager::GetWindow()
{
	return window;
}


