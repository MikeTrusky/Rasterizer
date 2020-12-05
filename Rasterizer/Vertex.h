#pragma once
#include "Helper.h"

class Vertex
{
private:

public:
	Vertex(float v1, float v2, float v3);
	Vertex(float v1, float v2, float v3, float c1, float c2, float c3);
	float3 position;
	float3 normal;
};

