#pragma once
#include "MathLibrary/Helper.h"
#include "Color.h"

class Vertex
{
private:

public:
	Vertex() = default;
	Vertex(float vx, float vy, float vz);
	Vertex(float vx, float vy, float vz, float normx, float normy, float normz, float texx, float texy);
	Vertex(float vx, float vy, float vz, Color color);
	Vertex(float3 pos, float3 norm, Color col, float3 tex) : position(pos), normal(norm), color(col), texturePos(tex) {};
	float3 position;
	float3 texturePos;
	float3 normal;
	Color color;
};