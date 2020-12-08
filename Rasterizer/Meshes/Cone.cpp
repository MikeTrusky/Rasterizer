#include "Cone.h"
#include "Triangle.h"

Cone::Cone(int v)
{
	SetArrays(v + 2, 2 * v);

	float r = 0.5f;
	float angle = 2 * PI / v;
	vertices[0].position = float3(0.0f, 0.0f, 0.0f);
	vertices[v + 2 - 1].position = float3(0.0f, 1.0f, 0.0f);
	for (int i = 1; i < v + 1; i++)
	{
		float x = r * cos((i - 1) * angle);
		float z = r * sin((i - 1) * angle);
		vertices[i].position = float3(x, 0.0f, z);
	}
	
	indices[0] = int3(0, 1, v);
	indices[2 * v - 1] = int3(v + 1, v, 1);

	for (int i = 1; i < v; ++i)
	{
		indices[i] = int3(0, i + 1, i);
	}
	
	for (int i = 0; i < v - 1; i++)
	{
		indices[i + v] = int3(v + 1, i + 1, i + 2);
	}
}