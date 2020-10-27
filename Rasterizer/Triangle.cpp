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
