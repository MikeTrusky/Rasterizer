#pragma once
#include "MathLibrary/Helper.h"
#include "Color.h"

class Vertex
{
private:

public:
	Vertex() = default;
	Vertex(float vx, float vy, float vz);
	Vertex(float vx, float vy, float vz, float normx, float normy, float normz);
	Vertex(float vx, float vy, float vz, Color color);
	Vertex(float3 pos, float3 norm, Color col) : position(pos), normal(norm), color(col) {};
	float3 position;
	float3 normal;
	Color color;
};