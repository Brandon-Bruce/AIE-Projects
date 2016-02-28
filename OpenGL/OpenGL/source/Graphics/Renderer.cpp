#include "Renderer.h"
#include <iostream>
#include "gl_core_4_4.h"
#include "glfw\glfw3.h"
#include "glm\ext.hpp"
#include "FlyCamera.h"
#include "Program.h"
#include "Mesh.h"

using namespace std;
using glm::vec4;

void APIENTRY openglCallbackFunction(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	cout << "---------------------opengl-callback-start------------" << endl;
	cout << "message: " << message << endl;
	cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "OTHER";
		break;
	}
	cout << endl;

	cout << "id: " << id;
	cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "HIGH";
		break;
	}
	cout << endl;
	cout << "---------------------opengl-callback-end--------------" << endl;
}

void TurnOnDebugLogging()
{
	if (glDebugMessageCallback == nullptr) return;
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	GLuint unusedIds = 0;
	glDebugMessageControl(
		GL_DONT_CARE, // source
		GL_DONT_CARE, // type
		GL_DONT_CARE, // severity
		0,
		&unusedIds,
		true);
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

int Renderer::Startup()
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

	TurnOnDebugLogging();

	clearColor = vec4(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST); //Enable depth buffer

	camera = new FlyCamera;

	return 0;
}

void Renderer::Shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete camera;
}

void Renderer::BeginRender()
{
	//Clear render buffer
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndRender()
{	
	//Draw buffers
	glfwSwapBuffers(window);
}

Camera* Renderer::GetCamera()
{
	return camera;
}

GLFWwindow* Renderer::GetWindow()
{
	return window;
}


