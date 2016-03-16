#include "AssetLoader.h"
#include <fstream>
#include <assert.h>

using namespace std;

std::string AssetLoader::ReadFile(const char* fileName)
{
	string contents;
	string line;
	fstream file;
	file.open(fileName, std::ios_base::in);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			contents.append(line + '\n');
		}
		file.close();
	}
	else
	{
		assert(false);
	}

	return contents;
}
