#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H
#define APPLICATION MyApplication::GetApplication()

#include "Application.h"
#include "Shader.h"

class MyApplication : public Application
{
public:
	static MyApplication& GetApplication();
	int Startup();
	void Shutdown();
	int Run();
	int Update();
	int Draw();

private:
	MyApplication() {};
	MyApplication(MyApplication &app) = delete;
	void operator=(MyApplication &app) = delete;
	~MyApplication() {};

	Shader test;
	float lastFrameTime;
	float dt;
};

#endif // !MYAPPLICATION_H
