#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H
#define APPLICATION MyApplication::GetApplication()

#include "Renderer.h"

class Renderer;
class Grid;
class FBXProgram;
class PerlinNoise;
class Texture;
class ParticleEmitter;
class GUI;

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
	FBXProgram* soulSpear;
	FBXProgram* demoMan;
	PerlinNoise* perlinNoise;
	ParticleEmitter* emitter;

	Texture* crate;
	GUI* gui;
	double lastFrameTime;
	double dt;
};
#endif // !MYAPPLICATION_H
