#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "glm\vec4.hpp"
class SphereCollider;
class Camera;

class CollisionDetection
{
public:
	static bool DetectCollision(SphereCollider* sphere, Camera* camera, const char* name);
};

#endif