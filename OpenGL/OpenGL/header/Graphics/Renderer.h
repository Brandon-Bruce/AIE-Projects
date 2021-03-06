#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Program.h"
#include "glm\vec4.hpp"

class Camera;
struct GLFWwindow;
class Grid;
class Program;
class Mesh;
class GUI;

class Renderer
{
public:
	Renderer();
	~Renderer();

	int Startup(GUI* gui);
	void Shutdown();
	void BeginRender();
	void EndRender();

	Camera* GetCamera();
	GLFWwindow* GetWindow();

	Renderer(Renderer &app) = delete;
	void operator=(Renderer &app) = delete;
private:
	bool active;
	Camera* camera;
	GLFWwindow* window;
	glm::vec4 clearColor;
};

#endif  // !GRAPHICSMANAGER_H

