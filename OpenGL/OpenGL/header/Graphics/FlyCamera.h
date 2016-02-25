#ifndef FLYCAMERA_H
#define FLYCAMERA_H

#include "Camera.h"

class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	void Update(double deltaTime);
	void SetSpeed(float speed);

private:
	float speed;
	double prevMousePosX;
	double prevMousePosY;
	float rotationSpeed;
};

#endif // !FLYCAMERA_H