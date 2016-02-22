#include "GUI.h"
#include "glfw\glfw3.h"
#include "ImGUI\imgui.h"
#include "aieutilities\imgui_impl_glfw_gl3.h"

void GUI::Startup(GLFWwindow* window)
{
	//Initialise ImGUI
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGuiIO& io = ImGui::GetIO();

	//Get window size and give to ImGUI
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);
	io.DisplaySize.x = (float)width;
	io.DisplaySize.y = (float)height;
}

void GUI::Shutdown()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

void GUI::BeginRender()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void GUI::AddElement(char* name, float col[3])
{
	ImGui::ColorEdit3(name, col);
}

void GUI::EndRender()
{
	ImGui::Render();
}
