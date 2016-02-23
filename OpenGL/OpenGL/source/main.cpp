#include "MyApplication.h"

int main()
{
	if (APPLICATION.Startup() == false)
	{
		APPLICATION.Run();
		APPLICATION.Shutdown();
	}
	else return -1;
	return 0;
}