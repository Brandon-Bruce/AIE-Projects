#ifndef SPHERE_H
#define SPHERE_H

#include "glm\vec3.hpp"
#include "CollisionDetection.h"
#include <vector>

class SphereCollider
{
public:
	void Set(std::vector<glm::vec3>& points, float scale);
	void Update(glm::vec3& position);

private:
	glm::vec3 position;
	glm::vec3 centre;
	float radius;

	friend CollisionDetection;
};

#endif