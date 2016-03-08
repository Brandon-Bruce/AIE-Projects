#ifndef VERTEX_H
#define VERTEX_H

#include "glm\vec4.hpp"
#include "glm\vec2.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;
};

struct TexVertex
{
	glm::vec4 position;
	glm::vec2 texcoord;
};

#endif