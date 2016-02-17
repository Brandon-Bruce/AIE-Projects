#include "MyApplication.h"

int main()
{
	if (APPLICATION.Startup() == false)
	{
		APPLICATION.Run();
		APPLICATION.Shutdown();
	}
	//Gizmos::create();

	//mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	//mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
	//								16 / 9.f, 0.1f, 1000.f);
	//mat4 sun;
	//while (glfwWindowShouldClose(window) == false &&
	//	glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Gizmos::clear();

	//	Gizmos::addTransform(glm::mat4(1));

	//	vec4 white(1);
	//	vec4 black(0, 0, 0, 1);

	//	for (int i = 0; i < 21; ++i)
	//	{
	//		Gizmos::addLine(vec3(-10 + i, 0, 10),
	//			vec3(-10 + i, 0, -10),
	//			i == 10 ? white : black);

	//		Gizmos::addLine(vec3(10, 0, -10 + i),
	//			vec3(-10, 0, -10 + i),
	//			i == 10 ? white : black);
	//	}

	//	for (int i = 0; i < 5; ++i)
	//	{
	//		Gizmos::addSphere(vec3(i * 5, 0, 0), 2.f, 50, 50, white, &sun);
	//		sun = glm::rotate(sun, 3.f, vec3(0, 1, 0));
	//	}

	//		Gizmos::draw(projection * view);

	//	//Game loop

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	//Gizmos::destroy();

	//glfwTerminate();
	return 0;
}