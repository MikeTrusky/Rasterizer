#include "Triangle.h"

Triangle::Triangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3)
{
	vertices[0].position = v1;
	vertices[1].position = v2;
	vertices[2].position = v3;

	vertices[0].color = c1;
	vertices[1].color = c2;
	vertices[2].color = c3;
}

Triangle::Triangle(const Triangle & t)
{
	vertices[0] = t.vertices[0];
	vertices[1] = t.vertices[1];
	vertices[2] = t.vertices[2];
}

Triangle::Triangle()
{
	SetArrays(3, 1);

	vertices[0].position = float3(-1.5f, 0.0f, 0.0f);
	vertices[1].position = float3(0.0f, 0.5f, 0.0f);
	vertices[2].position = float3(0.5f, 0.0f, 0.0f);
	indices[0] = int3(0, 1, 2);
}