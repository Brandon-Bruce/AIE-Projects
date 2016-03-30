#include "gl_core_4_4.h"
#include "aieutilities\Gizmos.h"
#include "CollisionDetection.h"
#include "Sphere.h"
#include "glm\vec4.hpp"
#include "glm\ext.hpp"
#include "Camera.h"
#include <iostream>

bool CollisionDetection::DetectCollision(SphereCollider* sphere, Camera* camera, const char* name)
{
	glm::vec4* frustrum = camera->GetFrustrumPlanes();
	glm::vec3 projectionView = (glm::vec3)camera->GetProjectionView()[3];
	glm::vec3 spherePosition = sphere->position + sphere->centre;
	Gizmos::addSphere(spherePosition, sphere->radius, 50, 50, glm::vec4(1.f, 1.f, 1.f, 1.f));
	
	for (int i = 0; i < 6; ++i)
	{
		float d = glm::dot(glm::vec3(frustrum[i]), spherePosition) +
			frustrum[i].w;

		if (d < -sphere->radius)
		{
			printf("Don't Render: %s\n", name);
			return false;
		}
	}

	printf("Do Render: %s\n", name);
	return true;
}
