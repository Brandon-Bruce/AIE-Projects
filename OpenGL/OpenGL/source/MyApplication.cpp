#include "FBXProgram.h"
#include "aieutilities\Gizmos.h"
#include "MyApplication.h"
#include "FlyCamera.h"
#include "Grid.h"
#include "glfw\glfw3.h"
#include "PerlinNoise.h"
#include "Texture.h"
#include "glm\ext.hpp"
#include "ParticleEmitter.h"
#include "GUI.h"

#include <cstdio>

using glm::vec4;
using glm::mat4;

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{

	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	if (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d\n",
			file, line);
		retCode = 1;
	}
	return retCode;
}

MyApplication& MyApplication::GetApplication()
{
	static MyApplication instance;
	return instance;
}

int MyApplication::Startup()
{
	renderer = new Renderer;
	if (renderer->Startup(gui))
		return -1;

	grid = new Grid;
	grid->LoadShader();
	grid->GenerateGrid(64, 64);

	soulSpear = new FBXProgram;
	mat4 souldSpearPos = glm::translate(glm::vec3(10, 5, 2));
	soulSpear->Startup("./data/SoulSpear/soulspear.fbx", souldSpearPos, "Soul Spear", 1.f);

	demoMan = new FBXProgram;
	mat4 demoManPos = glm::translate(glm::vec3(50, 10, 5));
	demoManPos *= glm::scale(glm::vec3(0.01f, 0.01f, 0.01f));
	demoMan->Startup("./data/DemoMan/demolition.fbx", demoManPos, "Demo Man", 0.01f);

	perlinNoise = new PerlinNoise;
	perlinNoise->Create(64, 64);

	crate = new Texture;
	crate->Create("./data/crate.png");

	gui = new GUI;
	gui->Startup(glfwGetCurrentContext());

	emitter = new ParticleEmitter;
	emitter->Initalise(1000, 500,
		0.1f, 1.0f,
		1, 5,
		1, 0.1f,
		glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1),
		gui);

	Gizmos::create();
	printOpenGLError();

	lastFrameTime = glfwGetTime();


	return 0;
}

void MyApplication::Shutdown()
{
	Gizmos::destroy();
	gui->Shutdown();
	soulSpear->CleanUp();
	crate->Destroy();
	renderer->Shutdown();
	delete gui;
	delete soulSpear;
	delete crate;
	delete renderer;
}

int MyApplication::Run()
{
	printOpenGLError();

	while (glfwWindowShouldClose(renderer->GetWindow()) == false &&
		glfwGetKey(renderer->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		Update();
		Draw();
		printOpenGLError();
	}
	return 0;
}

int MyApplication::Update()
{
	//Calculate delta time
	double now = glfwGetTime();
	dt = now - lastFrameTime;
	lastFrameTime = now;

	//Get keyboard events
	glfwPollEvents();

	renderer->GetCamera()->Update(dt);

	emitter->UpdateParticles(dt, renderer->GetCamera()->GetWorldTransform());
	return 0;
}

void MyApplication::Draw()
{
	renderer->BeginRender();
	gui->BeginRender();
	Gizmos::clear();

	glm::mat4 projectionView = renderer->GetCamera()->GetProjectionView();
	perlinNoise->Draw(dt, lastFrameTime, projectionView);
	crate->Draw(projectionView);
	soulSpear->Draw(projectionView, renderer->GetCamera());
	demoMan->Draw(projectionView, renderer->GetCamera());
	emitter->DrawParticles(projectionView);
	((FlyCamera*)renderer->GetCamera())->SetSpeed();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Gizmos::draw(projectionView);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gui->EndRender();
	renderer->EndRender();
}
