#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H
#define APPLICATION MyApplication::GetApplication()

//#include "glm\vec4.hpp"
//#include "GUI.h"

class Renderer;
class Grid;

class MyApplication
{
public:
	static MyApplication& GetApplication();
	int Startup();
	void Shutdown();
	int Run();

private:
	MyApplication() {};
	MyApplication(MyApplication &app) = delete;
	void operator=(MyApplication &app) = delete;
	~MyApplication() {};

	int Update();
	void Draw();

	Renderer* renderer;
	Grid* grid;

	//GUI gui;
	double lastFrameTime;
	double dt;
};
#endif // !MYAPPLICATION_H
