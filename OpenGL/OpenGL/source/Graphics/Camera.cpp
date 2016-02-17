#include "Camera.h"
#include "glm\ext.hpp"

using glm::mat4;
using glm::vec3;

Camera::Camera()
{
	projectionTransform = glm::perspective(glm::pi<float>() * 0.25f,
										16 / 9.f, 0.1f, 1000.0f);
	SetLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
}


Camera::~Camera()
{

}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
}

void Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	mat4 viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);
}

void Camera::SetPosition(glm::vec3 position)
{
	worldTransform = glm::translate(position);
}

glm::mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}

glm::mat4 Camera::GetView()
{
	return glm::inverse(worldTransform);
}

glm::mat4 Camera::GetProjection()
{
	return projectionTransform;
}

glm::mat4 Camera::GetProjectionView()
{
	return projectionTransform * glm::inverse(worldTransform);
}
