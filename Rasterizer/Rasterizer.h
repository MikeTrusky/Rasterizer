#pragma once
#include "Buffer.h"
#include "Triangle.h"

class Rasterizer
{
public:
	Rasterizer(Buffer& Buffer) : buffer(Buffer) {};
	void DrawTriangle(Triangle& triangle);
	float CalculateCanonicalViewX(float x);
	float CalculateCanonicalViewY(float y);

	Buffer& buffer;
};