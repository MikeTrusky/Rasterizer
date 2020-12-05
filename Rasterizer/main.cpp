#include <iostream>
#include <vector>
#include "TGABuffer.h"
#include "Color.h"
#include "Triangle.h"
#include "Helper.h"
#include "Rasterizer.h"
#include "VertexProcessor.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

void DrawBox(VertexProcessor& vp, Rasterizer& rasterizer, Color first, Color second, Color third, float3 *vertices)
{
	Color c_1 = first;
	Color c_2 = second;
	Color c_3 = third;

	//Bottom
	Triangle triangle = Triangle(vp.tr(vertices[0]), vp.tr(vertices[2]), vp.tr(vertices[1]), first, first, first);
	Triangle triangle2 = Triangle(vp.tr(vertices[3]), vp.tr(vertices[2]), vp.tr(vertices[0]), first, first, first);
	////Left
	Triangle triangle3 = Triangle(vp.tr(vertices[7]), vp.tr(vertices[0]), vp.tr(vertices[1]), second, second, second);
	Triangle triangle4 = Triangle(vp.tr(vertices[4]), vp.tr(vertices[0]), vp.tr(vertices[7]), second, second, second);
	////Back
	Triangle triangle5 = Triangle(vp.tr(vertices[4]), vp.tr(vertices[3]), vp.tr(vertices[0]), third, third, third);
	Triangle triangle6 = Triangle(vp.tr(vertices[5]), vp.tr(vertices[3]), vp.tr(vertices[4]), third, third, third);
	////Right
	Triangle triangle7 = Triangle(vp.tr(vertices[3]), vp.tr(vertices[6]), vp.tr(vertices[2]), second, second, second);
	Triangle triangle8 = Triangle(vp.tr(vertices[5]), vp.tr(vertices[6]), vp.tr(vertices[3]), second, second, second);
	////Top
	Triangle triangle9 = Triangle(vp.tr(vertices[4]), vp.tr(vertices[6]), vp.tr(vertices[5]), first, first, first);
	Triangle triangle10 = Triangle(vp.tr(vertices[7]), vp.tr(vertices[6]), vp.tr(vertices[4]), first, first, first);
	//////Front
	Triangle triangle11 = Triangle(vp.tr(vertices[6]), vp.tr(vertices[2]), vp.tr(vertices[1]), third, third, third);
	Triangle triangle12 = Triangle(vp.tr(vertices[7]), vp.tr(vertices[6]), vp.tr(vertices[1]), third, third, third);

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
	TGABuffer colorBuffer = TGABuffer(800, 800);
	Rasterizer rasterizer = Rasterizer(colorBuffer);
	VertexProcessor vp = VertexProcessor();

	float3 vertex_1(-0.5f, -0.5f, 0.5f);
	float3 vertex_2(-0.5f, -0.5f, -0.5f);
	float3 vertex_3(0.5f, -0.5f, -0.5f);
	float3 vertex_4(0.5f, -0.5f, 0.5f);
	float3 vertex_5(-0.5f, 0.5f, 0.5f);
	float3 vertex_6(0.5f, 0.5f, 0.5f);
	float3 vertex_7(0.5f, 0.5f, -0.5f);
	float3 vertex_8(-0.5f, 0.5f, -0.5f);

	float3 vertices[8] = { vertex_1, vertex_2, vertex_3, vertex_4, vertex_5, vertex_6, vertex_7, vertex_8 };
	
	vp.setPerspective(60.0f, 1.0f/1.0f, 0.1f, 1000.0f);
	vp.setIdentityView();
	vp.setIdentity();
	vp.setLookAt(float3(0, 1, 7), float3(0, 0, 0), float3(0, 1, 0));
	vp.transform();

	Color color(0, 0, 0, 0);
	colorBuffer.clearColor(color);
	colorBuffer.clearDepth();

	//Prawa kostka
	/*vp.setIdentity();
	vp.multByScale(float3(1.5f, 1.5f, 5.0f));
	vp.multByRotation(-45.0f, float3(0, 1, 0));
	vp.multByTranslation(float3(3.0f, 0, -2.0f));
	vp.transform();

	DrawBox(vp, rasterizer, Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));*/

	//Lewa kostka
	vp.setIdentity();
	vp.multByScale(float3(2.0f, 2.0f, 3.0f));
	vp.multByRotation(45.0f, float3(0, 1, 0));
	vp.multByTranslation(float3(-3.0f, 0, -2.0f));
	vp.transform();

	/*DrawBox(vp, rasterizer, Color(0, 255, 0), Color(0, 0, 255), Color(255, 0, 0));*/

	/*colorBuffer.saveFile("outputFile.tga");*/

#pragma region GLFW stuff

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(colorBuffer.w, colorBuffer.h, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((const char*)"#version 130");

#pragma endregion

	float boxPosition[3] = { 0.0f, 0.0f, 0.0f };
	float boxScale[3] = { 1.0f, 1.0f, 1.0f };
	float angleX, angleY, angleZ = 0.0f;

	float eye[3] = { 0, 1, 7 };
	float center[3] = { 0, 0, 0 };
	float near = 0.001f;
	float far = 100.0f;
	float fov = 60.0f;
	float aspect = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		colorBuffer.clearColor(color);
		colorBuffer.clearDepth();

		ImGui::Begin("Look at");
		ImGui::SliderFloat3("Eye", eye, -10.0f, 10.0f);
		ImGui::SliderFloat3("Center", center, -10.0f, 10.0f);
		ImGui::End();

		ImGui::Begin("Perspective");
		ImGui::SliderFloat("FOV", &fov, 10.0f, 150.0f);
		ImGui::SliderFloat("Aspect", &aspect, 0.5f, 5.0f);
		ImGui::SliderFloat("Far", &far, 1.0f, 10.0f);
		ImGui::SliderFloat("near", &near, 0.001f, 10.0f);
		ImGui::End();

		ImGui::Begin("Box transformations");
		ImGui::SliderFloat3("Position", boxPosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale", boxScale, 0.0f, 5.0f);
		ImGui::SliderFloat("Angle Y", &angleY, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle X", &angleX, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle Z", &angleZ, -360.0f, 360.0f);
		ImGui::End();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		vp.setPerspective(fov, aspect, near, far);
		vp.setIdentityView();
		vp.setIdentity();
		vp.setLookAt(float3(eye[0], eye[1], eye[2]), float3(center[0], center[1], center[2]), float3(0, 1, 0));
		vp.transform();

		vp.setIdentity();
		vp.multByScale(float3(boxScale[0], boxScale[1], boxScale[2]));
		vp.multByRotation(angleY, float3(0, 1, 0));
		vp.multByRotation(angleX, float3(1, 0, 0));
		vp.multByRotation(angleZ, float3(0, 0, 1));
		vp.multByTranslation(float3(boxPosition[0], boxPosition[1], boxPosition[2]));
		vp.transform();

		DrawBox(vp, rasterizer, Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255), vertices);

		glDrawPixels(colorBuffer.w, colorBuffer.h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, colorBuffer.frame);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}