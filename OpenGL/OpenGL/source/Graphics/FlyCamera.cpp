#include "FlyCamera.h"
#include "glfw\glfw3.h"
#include "glm\ext.hpp"
#include "GraphicsManager.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

FlyCamera::FlyCamera() : speed(0.1f), rotationSpeed(1.0f)
{
	int windowHeight, windowWidth;
	GLFWwindow* window = GRAPHICSMANAGER.GetWindow();
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwSetCursorPos(window, (double)(windowWidth / 2), (double)(windowHeight / 2));
	glfwGetCursorPos(GRAPHICSMANAGER.GetWindow(), &prevMousePosX, &prevMousePosY);
}

FlyCamera::~FlyCamera()
{

}

void FlyCamera::Update(float deltaTime)
{
	//Get window
	GLFWwindow* window = GRAPHICSMANAGER.GetWindow();

	//Get directions

	vec4 right = vec4(worldTransform[0].x, worldTransform[0].y, worldTransform[0].z, 0);
	vec4 up = vec4(worldTransform[1].x, worldTransform[1].y, worldTransform[1].z, 0);
	vec4 forward = vec4(worldTransform[2].x, worldTransform[2].y, worldTransform[2].z, 0);
	right = glm::normalize(right);
	up = glm::normalize(up);
	forward = glm::normalize(forward);

	//Moved camera based on key presses
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		worldTransform[3] -= forward * speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		worldTransform[3] += forward * speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		worldTransform[3] -= right * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		worldTransform[3] += right * speed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		worldTransform[3] -= up * speed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		worldTransform[3] += up * speed;

	//calculate delta mouse movement
	double mouseX = 0, mouseY = 0;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	double deltaX = mouseX - prevMousePosX;
	double deltaY = mouseY - prevMousePosY;

	//Reset mouse position
	int windowHeight, windowWidth;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwSetCursorPos(window, (double)(windowWidth / 2), (double)(windowHeight / 2));
	glfwGetCursorPos(window, &prevMousePosX, &prevMousePosY);

	mat4 mMat;

	//Add rotation to world position
	vec3 axis = vec3(worldTransform[0].x, worldTransform[0].y, worldTransform[0].z);
	mMat = glm::axisAngleMatrix(axis, ((float)-deltaY / 150.0f) * rotationSpeed);
	worldTransform[0] = mMat * worldTransform[0];
	worldTransform[1] = mMat * worldTransform[1];
	worldTransform[2] = mMat * worldTransform[2];

	mMat = glm::axisAngleMatrix(vec3(0,1,0), ((float)-deltaX / 150.0f) * rotationSpeed);
	worldTransform[0] = mMat * worldTransform[0];
	worldTransform[1] = mMat * worldTransform[1];
	worldTransform[2] = mMat * worldTransform[2];
}

void FlyCamera::SetSpeed(float speed)
{
	this->speed = speed;
}
