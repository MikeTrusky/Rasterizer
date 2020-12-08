#include "Cylinder.h"

Cylinder::Cylinder(int v, int h)
{
	SetArrays((h * v) + 2, 2 * h * v);

	float height = 1.0f;
	float heightStep = 1.0f / (h - 1);
	float r = 0.5f;
	float angle = 2 * PI / v;
	vertices[0].position = float3(0.0f, height, 0.0f);
	vertices[verticesSize - 1].position = float3(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 1; i <= v; ++i)
	{
		float x = r * cos((i - 1) * angle);
		float z = r * sin((i - 1) * angle);
		for (unsigned int j = 0; j < h; ++j)
			vertices[i + j * v].position = float3(x, height - j * heightStep, z);
	}

	indices[v - 1] = int3(0, v, 1);

	//Podstawa górna
	for (unsigned int i = 0; i < v - 1; ++i)
	{
		indices[i] = int3(0, i + 1, i + 2);
	}

	//Œciany boczne
	for (unsigned int i = v; i < v * h; ++i)
	{
		if (i % v != 0)
			indices[i] = int3(i - v, i, (i - v) + 1);
		else
			indices[i] = int3(i, i + v, (i - v + 1));
	}

	//Œciany boczne pt. 2
	for (unsigned int i = v * h; i < (v * h + (h - 1) * v); ++i)
	{
		if (i % v == 0)
			indices[i] = int3(i - h * v + 1, i - (h - 2) * v, i - h * v + v + 1);
		else
			indices[i] = int3(i - h * v + 1, i - h * v + v, i - h * v + v + 1);
	}

	//Podstawa dolna
	for (unsigned int i = (v * h + (h - 1) * v); i < (v * h + (h - 1) * v) + v; ++i)
	{
		if (i % v == 0)
			indices[i] = int3(i - (h-1) * v, verticesSize - 1, i - (h * v) + 1);
		else
			indices[i] = int3(i - (h * v), verticesSize - 1, i - (h * v) + 1);
	}

	//for (int i = 0; i < trianglesSize; ++i)
	//	std::cout << "i: " << i << " " << indices[i] << std::endl;
}