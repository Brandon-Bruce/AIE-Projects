#include "AABB.h"
#include <limits>

void AABB::Set(std::vector<glm::vec3>& points)
{
	min.x = min.y = min.z = std::numeric_limits<float>::max();
	max.x = max.y = max.z = std::numeric_limits<float>::lowest();

	for (glm::vec3& p : points)
	{
		if (p.x < min.x) min.x = p.x;
		if (p.y < min.y) min.y = p.y;
		if (p.z < min.z) min.z = p.z;

		if (p.x > max.x) max.x = p.x;
		if (p.y > max.y) max.y = p.y;
		if (p.z > max.z) max.z = p.z;
	}
}
