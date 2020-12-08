#pragma once
#include "Helper.h"
#include "Color.h"

class Vertex
{
private:

public:
	Vertex() = default;
	Vertex(float vx, float vy, float vz);
	Vertex(float vx, float vy, float vz, Color color);
	float3 position;
	float3 normal;
	Color color;
};

