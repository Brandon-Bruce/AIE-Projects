#ifndef GUI_H
#define GUI_H

struct GLFWwindow;

class GUI
{
public:
	void Startup(GLFWwindow* window);
	void Shutdown();

	void BeginRender();
	void AddElement(char* name, float col[3]);
	void EndRender();
};

#endif