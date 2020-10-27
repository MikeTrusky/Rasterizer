#include <iostream>
#include "TGABuffer.h"
#include "Color.h"
#include "Triangle.h"
#include "Helper.h"
#include "Rasterizer.h"

int main()
{
	TGABuffer colorBuffer = TGABuffer(500, 500);
	Rasterizer rasterizer = Rasterizer(colorBuffer);

	Color color(0, 0, 0, 0);

	Triangle triangle = Triangle(float3(-0.9f, 0.5f, 0.9f), float3(0.3f, 0.0f, -0.1f), float3(-0.9f, -0.5f, 0.5f),
								 Color(255, 0, 0, 0), Color(0, 255, 0, 0), Color(0, 0, 255, 0));

	Triangle triangle2 = Triangle(float3(-0.5f, -0.5f, 0.0f), float3(0.0f, 0.5f, 0.0f), float3(0.5f, -0.5f, 0.0f),
		Color(0, 255, 255, 0), Color(0, 255, 255, 0), Color(0, 255, 255, 0));

	colorBuffer.clearColor(color);
	colorBuffer.clearDepth();
	rasterizer.DrawTriangle(triangle);
	rasterizer.DrawTriangle(triangle2);
	colorBuffer.saveFile("outputFile.tga");

	return 0;
}