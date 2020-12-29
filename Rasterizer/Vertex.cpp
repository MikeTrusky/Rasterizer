#include "Vertex.h"

Vertex::Vertex(float vx, float vy, float vz)
{
	position = float3(vx, vy, vz);
	color = Color(255, 255, 255);
}

Vertex::Vertex(float vx, float vy, float vz, Color color)
{
	position = float3(vx, vy, vz);
	this->color = color;
}