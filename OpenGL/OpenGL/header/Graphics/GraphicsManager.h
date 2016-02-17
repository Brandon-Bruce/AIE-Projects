#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#define GRAPHICSMANAGER GraphicsManager::GetGraphicsManager()

class Camera;
struct GLFWwindow;
class Shader;

class GraphicsManager
{
public:
	static GraphicsManager& GetGraphicsManager();
	int Startup();
	void Shutdown();
	Camera* GetCamera();
	GLFWwindow* GetWindow();

private:
	GraphicsManager() {};
	GraphicsManager(GraphicsManager &app) = delete;
	void operator=(GraphicsManager &app) = delete;
	~GraphicsManager() {};

	Camera* camera;
	GLFWwindow* window;
};

#endif  // !GRAPHICSMANAGER_H

