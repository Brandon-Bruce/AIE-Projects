#include "Renderer.h"
#include <iostream>
#include "gl_core_4_4.h"
#include "glfw\glfw3.h"
#include "glm\ext.hpp"
#include "FlyCamera.h"
#include "Program.h"
#include "Mesh.h"

using std::cout;
using glm::vec4;

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

void Renderer::RenderMesh(Program* program, Mesh* mesh, float time)
{
	GLuint m_programID = program->GetProgramID();
	glUseProgram(m_programID);
	//Set variables for shader
	unsigned int projectionViewUniform =
		glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false,
		glm::value_ptr(camera->GetProjectionView()));

	unsigned int timeUniform = glGetUniformLocation(m_programID, "time");
	glUniform1f(timeUniform, (float)time);

	unsigned int heightScaleUniform =
		glGetUniformLocation(m_programID, "heightScale");
	glUniform1f(heightScaleUniform, 2.0f);

	glBindVertexArray(mesh->GetVAO());
	unsigned int indexCount = mesh->GetIndexCount() * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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


