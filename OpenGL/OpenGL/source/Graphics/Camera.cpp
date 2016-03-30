#include "Camera.h"
#include "glm\ext.hpp"

using glm::mat4;
using glm::vec3;
using glm::vec4;

Camera::Camera()
{
	projectionTransform = glm::perspective(glm::pi<float>() * 0.25f,
										16 / 9.f, 0.1f, 1000.0f);
	SetLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
}


Camera::~Camera()
{

}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float _near, float _far)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, _near, _far);
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

glm::vec4* Camera::GetFrustrumPlanes()
{
	vec4* planes = new vec4[6];
	mat4 projectionView = GetProjectionView();

	//right side
	planes[0] = vec4(projectionView[0][3] - projectionView[0][0],
		projectionView[1][3] - projectionView[1][0],
		projectionView[2][3] - projectionView[2][0],
		projectionView[3][3] - projectionView[3][0]);

	//left side
	planes[1] = vec4(projectionView[0][3] - projectionView[0][0],
		projectionView[1][3] - projectionView[1][0],
		projectionView[2][3] - projectionView[2][0],
		projectionView[3][3] - projectionView[3][0]);

	//top
	planes[2] = vec4(projectionView[0][3] - projectionView[0][1],
		projectionView[1][3] - projectionView[1][1],
		projectionView[2][3] - projectionView[2][1],
		projectionView[3][3] - projectionView[3][1]);

	//bottom
	planes[3] = vec4(projectionView[0][3] - projectionView[0][1],
		projectionView[1][3] - projectionView[1][1],
		projectionView[2][3] - projectionView[2][1],
		projectionView[3][3] - projectionView[3][1]);

	//far
	planes[4] = vec4(projectionView[0][3] - projectionView[0][2],
		projectionView[1][3] - projectionView[1][2],
		projectionView[2][3] - projectionView[2][2],
		projectionView[3][3] - projectionView[3][2]);

	//plan normalisation bases on length of normal
	for (int i = 0; i < 6; ++i)
	{
		float d = glm::length(vec3(planes[i]));
		planes[i] /= d;
	}

	return planes;
}
