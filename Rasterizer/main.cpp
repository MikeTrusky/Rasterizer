#include <iostream>
#include "TGABuffer.h"
#include "Color.h"
#include "Triangle.h"
#include "Helper.h"
#include "Rasterizer.h"
#include "VertexProcessor.h"

int main()
{
	TGABuffer colorBuffer = TGABuffer(500, 500);
	Rasterizer rasterizer = Rasterizer(colorBuffer);
	VertexProcessor vp = VertexProcessor();

	vp.setPerspective(90.0f, 1.0f/1.0f, 1.0f, 1000.0f);
	
	vp.setIdentityView();
	//vp.setLookAt(float3(0, 0, 5.0f), float3(0, 0, -1.0f), float3(1, 1, 0));
	//vp.setIdentity();
	vp.transform();

	//TEST
	/*float4x4 matrix = { {float4(3.17, 0, 0, 0)}, {float4(0, 3.17, 0, 0)}, {float4(0, 0, -1, -1)}, {float4(0, 0, -2, 0)} };
	float4 value = float4(-0.5, -0.5, -1, 1);
	float4 result = mul(matrix, value);
	std::cout << "TUTAJ" << std::endl << std::endl;
	std::cout << result.x << " " << result.y << " " << result.z << " " << result.w << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << matrix[i][j] << "\t";
		std::cout << std::endl;
	}*/

	Color color(0, 0, 0, 0);

	Triangle triangle = Triangle(vp.tr(float3(-0.5f, -0.5f, -0.5f)), vp.tr(float3(0.5f, 0.5f, -1.5f)), vp.tr(float3(1.5f, -0.5f, -0.5f)),
								Color(255, 0, 0, 0), Color(0, 255, 0, 0), Color(0, 0, 255, 0));

	Triangle triangle2 = Triangle(vp.tr(float3(-0.3f, -0.3f, -0.1f)), vp.tr(float3(0.0f, 0.9f, -0.2f)), vp.tr(float3(0.4f, 0.7f, -0.3f)),
							Color(255, 0, 0, 0), Color(0, 255, 0, 0), Color(0, 0, 255, 0));

	colorBuffer.clearColor(color);
	colorBuffer.clearDepth();

	rasterizer.DrawTriangle(triangle);
	rasterizer.DrawTriangle(triangle2);

	colorBuffer.saveFile("outputFile.tga");

	return 0;
}