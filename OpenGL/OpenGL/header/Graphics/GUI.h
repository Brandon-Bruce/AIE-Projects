#ifndef GUI_H
#define GUI_H

#include "glm\vec3.hpp"
#include "glm\vec4.hpp"

struct GLFWwindow;

class GUI
{
public:
	void Startup(GLFWwindow* window);
	void Shutdown();

	void BeginRender();
	void AddElement(char* name, glm::vec3& var);
	void AddElement(char* name, glm::vec4& var);
	void AddElement(char* name, float* var);
	void EndRender();
};

#endif