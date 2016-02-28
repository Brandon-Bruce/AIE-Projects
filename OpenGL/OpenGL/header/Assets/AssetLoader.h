#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <string>

class AssetLoader
{
public:
	static std::string ReadFile(const char* fileName);
};

#endif