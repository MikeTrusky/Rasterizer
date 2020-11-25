#include "Triangle.h"

Triangle::Triangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;

	colors[0] = c1;
	colors[1] = c2;
	colors[2] = c3;
}

Triangle::Triangle(const Triangle & t)
{
	vertices[0] = t.vertices[0];
	vertices[1] = t.vertices[1];
	vertices[2] = t.vertices[2];

	colors[0] = t.colors[0];
	colors[1] = t.colors[1];
	colors[2] = t.colors[2];
}
