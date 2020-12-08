#pragma once
#include "Buffer/Buffer.h"
#include "MathLibrary/Helper.h"

class Triangle;

class Rasterizer
{
public:
	Rasterizer(Buffer& Buffer) : buffer(Buffer) {};
	void DrawTriangle(Triangle& triangle);
	void DrawTriangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3);
	float CalculateCanonicalViewX(float x);
	float CalculateCanonicalViewY(float y);

	Buffer& buffer;
};