#include "Cube.h"
#include "Triangle.h"

Cube::Cube()
{
	SetArrays(8, 12);

	vertices[0].position = float3(-0.5f, -0.5f, 0.5f);
	vertices[1].position = float3(-0.5f, -0.5f, -0.5f);
	vertices[2].position = float3(0.5f, -0.5f, -0.5f);
	vertices[3].position = float3(0.5f, -0.5f, 0.5f);
	vertices[4].position = float3(-0.5f, 0.5f, 0.5f);
	vertices[5].position = float3(0.5f, 0.5f, 0.5f);
	vertices[6].position = float3(0.5f, 0.5f, -0.5f);
	vertices[7].position = float3(-0.5f, 0.5f, -0.5f);
	//Front
	indices[0] = int3(0, 4, 3);
	indices[1] = int3(4, 5, 3);
	//Top
	indices[2] = int3(4, 7, 6);
	indices[3] = int3(6, 5, 4);
	//Left
	indices[4] = int3(1, 7, 0);
	indices[5] = int3(4, 0, 7);
	//Back
	indices[6] = int3(6, 7, 2);
	indices[7] = int3(1, 2, 7);
	//Right
	indices[8] = int3(5, 6, 3);
	indices[9] = int3(2, 3, 6);
	//Bottom
	indices[10] = int3(0, 2, 1);
	indices[11] = int3(3, 2, 0);
}