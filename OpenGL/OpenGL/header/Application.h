#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
	virtual int Startup() = 0;
	virtual void Shutdown() = 0;
	virtual int Update() = 0;
	virtual int Draw() = 0;

protected:
	Application() {};
	Application(Application &app) = delete;
	void operator=(Application &app) = delete;
	~Application() {};
};

#endif // !APPLICATION_H
