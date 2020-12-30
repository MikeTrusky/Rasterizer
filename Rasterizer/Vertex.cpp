#include "Vertex.h"

Vertex::Vertex(float vx, float vy, float vz)
{
	position = float3(vx, vy, vz);
	color = Color(255, 255, 255);
}

Vertex::Vertex(float vx, float vy, float vz, float normx, float normy, float normz)
{
	position = float3(vx, vy, vz);
	normal = float3(normx, normy, normz);
	color = Color(255, 255, 255);
}

Vertex::Vertex(float vx, float vy, float vz, Color color)
{
	position = float3(vx, vy, vz);
	this->color = color;
}