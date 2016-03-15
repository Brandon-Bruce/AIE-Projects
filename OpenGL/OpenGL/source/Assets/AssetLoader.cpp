#include "AssetLoader.h"
#include <fstream>

using namespace std;

std::string AssetLoader::ReadFile(const char * fileName)
{
	string data;

	fstream file;
	file.open(fileName, std::ios_base::in);

	if (file.is_open())
	{
		//while(file.)
	}

	return string();
}
