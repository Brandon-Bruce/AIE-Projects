#ifndef FLYCAMERA_H
#define FLYCAMERA_H

#include "Camera.h"

class GUI;

class FlyCamera : public Camera
{
public:
	FlyCamera(GUI* gui);
	~FlyCamera();

	void Update(double deltaTime);
	void SetSpeed();

private:
	float speed;
	double prevMousePosX;
	double prevMousePosY;
	float rotationSpeed;
	GUI* gui;
};

#endif // !FLYCAMERA_H