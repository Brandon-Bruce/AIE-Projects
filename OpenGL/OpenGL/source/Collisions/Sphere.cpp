#include "Sphere.h"
#include "glm\ext.hpp"

void SphereCollider::Set(std::vector<glm::vec3>& points, float scale)
{
	glm::vec3 min, max;
	min.x = min.y = min.z = std::numeric_limits<float>::max();
	max.x = max.y = max.z = std::numeric_limits<float>::lowest();

	for (glm::vec3& p : points)
	{
		if (p.x * scale < min.x) min.x = p.x * scale;
		if (p.y * scale < min.y) min.y = p.y * scale;
		if (p.z * scale < min.z) min.z = p.z * scale;

		if (p.x * scale > max.x) max.x = p.x * scale;
		if (p.y * scale > max.y) max.y = p.y * scale;
		if (p.z * scale > max.z) max.z = p.z * scale;
	}
	centre = (min + max) * 0.5f;
	radius = glm::distance(min, centre);
}

void SphereCollider::Update(glm::vec3& position)
{
	this->position = position;
}
