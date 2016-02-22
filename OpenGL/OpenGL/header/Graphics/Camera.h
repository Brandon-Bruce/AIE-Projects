#ifndef CAMERA_H
#define CAMERA_H

#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"

class Camera
{
public:
	Camera();
	~Camera();
	virtual void Update(double deltaTime) = 0;
	void SetPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	glm::mat4 GetWorldTransform();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::mat4 GetProjectionView();

protected:

	glm::mat4 worldTransform;
	//glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	//glm::mat4 projectionViewTransform;
};

#endif // !CAMERA_H

