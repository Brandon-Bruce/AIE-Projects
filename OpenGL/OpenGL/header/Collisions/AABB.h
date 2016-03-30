#ifndef AABB_H
#define AABB_H

#include "glm\vec3.hpp"
#include <vector>

class AABB
{
public:
	void Set(std::vector<glm::vec3>& points);

	glm::vec3 min, max;
};

#endif