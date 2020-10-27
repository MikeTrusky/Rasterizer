#pragma once
#include "Helper.h"
#include "Color.h"

class Triangle
{
public:
	float3 vertices[3];
	Color colors[3];

	Triangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3);
};