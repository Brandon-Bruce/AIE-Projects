#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "glm\vec4.hpp"

class Camera;
struct GLFWwindow;
class Grid;
class Program;
class Mesh;

class Renderer
{
public:
	Renderer();
	~Renderer();

	int Startup();
	void Shutdown();
	void BeginRender();
	void RenderMesh(Program* program, Mesh* mesh, float time);
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

