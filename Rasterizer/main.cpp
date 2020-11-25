#include <iostream>
#include <vector>
#include "TGABuffer.h"
#include "Color.h"
#include "Triangle.h"
#include "Helper.h"
#include "Rasterizer.h"
#include "VertexProcessor.h"

void DrawBox(VertexProcessor& vp, Rasterizer& rasterizer, Color first, Color second, Color third)
{
	float3 vertex_1(-0.5f, -0.5f, 0.5f);
	float3 vertex_2(-0.5f, -0.5f, 0.1f);
	float3 vertex_3(0.5f, -0.5f, 0.1f);
	float3 vertex_4(0.5f, -0.5f, 0.5f);
	float3 vertex_5(-0.5f, 0.5f, 0.5f);
	float3 vertex_6(0.5f, 0.5f, 0.5f);
	float3 vertex_7(0.5f, 0.5f, 0.1f);
	float3 vertex_8(-0.5f, 0.5f, 0.1f);

	Color c_1 = first;
	Color c_2 = second;
	Color c_3 = third;

	//Bottom
	Triangle triangle = Triangle(vp.tr(vertex_1), vp.tr(vertex_3), vp.tr(vertex_2), first, first, first);
	Triangle triangle2 = Triangle(vp.tr(vertex_4), vp.tr(vertex_3), vp.tr(vertex_1), first, first, first);
	////Left
	Triangle triangle3 = Triangle(vp.tr(vertex_8), vp.tr(vertex_1), vp.tr(vertex_2), second, second, second);
	Triangle triangle4 = Triangle(vp.tr(vertex_5), vp.tr(vertex_1), vp.tr(vertex_8), second, second, second);
	////Back
	Triangle triangle5 = Triangle(vp.tr(vertex_5), vp.tr(vertex_4), vp.tr(vertex_1), third, third, third);
	Triangle triangle6 = Triangle(vp.tr(vertex_6), vp.tr(vertex_4), vp.tr(vertex_5), third, third, third);
	////Right
	Triangle triangle7 = Triangle(vp.tr(vertex_4), vp.tr(vertex_7), vp.tr(vertex_3), second, second, second);
	Triangle triangle8 = Triangle(vp.tr(vertex_6), vp.tr(vertex_7), vp.tr(vertex_4), second, second, second);
	////Top
	Triangle triangle9 = Triangle(vp.tr(vertex_5), vp.tr(vertex_7), vp.tr(vertex_6), first, first, first);
	Triangle triangle10 = Triangle(vp.tr(vertex_8), vp.tr(vertex_7), vp.tr(vertex_5), first, first, first);
	//////Front
	Triangle triangle11 = Triangle(vp.tr(vertex_7), vp.tr(vertex_3), vp.tr(vertex_2), third, third, third);
	Triangle triangle12 = Triangle(vp.tr(vertex_8), vp.tr(vertex_7), vp.tr(vertex_2), third, third, third);


	rasterizer.DrawTriangle(triangle);
	rasterizer.DrawTriangle(triangle2);
	rasterizer.DrawTriangle(triangle3);
	rasterizer.DrawTriangle(triangle4);
	rasterizer.DrawTriangle(triangle5);
	rasterizer.DrawTriangle(triangle6);
	rasterizer.DrawTriangle(triangle7);
	rasterizer.DrawTriangle(triangle8);
	rasterizer.DrawTriangle(triangle9);
	rasterizer.DrawTriangle(triangle10);
	rasterizer.DrawTriangle(triangle11);
	rasterizer.DrawTriangle(triangle12);
}

int main()
{
	TGABuffer colorBuffer = TGABuffer(500, 500);
	Rasterizer rasterizer = Rasterizer(colorBuffer);
	VertexProcessor vp = VertexProcessor();

	vp.setPerspective(60.0f, 1.0f/1.0f, 0.1f, 100.0f);
	vp.setIdentityView();
	vp.setIdentity();
	vp.setLookAt(float3(0, 1, 7), float3(0, 0, 0), float3(0, 1, 0));
	vp.transform();

	Color color(0, 0, 0, 0);
	colorBuffer.clearColor(color);
	colorBuffer.clearDepth();

	//Prawa kostka
	vp.setIdentity();
	vp.multByScale(float3(1.5f, 1.5f, 5.0f));
	vp.multByRotation(-45.0f, float3(0, 1, 0));
	vp.multByTranslation(float3(3.0f, 0, -2.0f));
	vp.transform();

	DrawBox(vp, rasterizer, Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));

	//Lewa kostka
	vp.setIdentity();
	vp.multByScale(float3(2.0f, 2.0f, 3.0f));
	vp.multByRotation(45.0f, float3(0, 1, 0));
	vp.multByTranslation(float3(-3.0f, 0, -2.0f));
	vp.transform();

	DrawBox(vp, rasterizer, Color(0, 255, 0), Color(0, 0, 255), Color(255, 0, 0));

	colorBuffer.saveFile("outputFile.tga");

	return 0;
}