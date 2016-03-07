#ifndef TEXTURE_H
#define TEXTURE_H

#include "Program.h"
#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

class Texture
{
public:
	void Create();
	void Destroy();
};

#endif