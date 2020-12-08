#pragma once
#include "Helper.h"
#include "Color.h"
#include "Mesh.h"

class Triangle : public Mesh
{
public:
	Triangle();
	Triangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3);
	Triangle(const Triangle &t);
};