#include <iostream>
#include <vector>
#include "Buffer/TGABuffer.h"
#include "Color.h"
#include "Meshes/Triangle.h"
#include "Meshes/Cube.h"
#include "Meshes/Cone.h"
#include "Meshes/Sphere.h"
#include "Meshes/Cylinder.h"
#include "MathLibrary/Helper.h"
#include "Rasterizer.h"
#include "Processors/VertexProcessor.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

int main()
{
	TGABuffer colorBuffer = TGABuffer(800, 800);
	Rasterizer rasterizer = Rasterizer(colorBuffer);
	VertexProcessor vp = VertexProcessor();
	
	vp.setPerspective(60.0f, 1.0f/1.0f, 0.1f, 1000.0f);
	vp.setIdentityView();
	vp.setIdentity();
	vp.setLookAt(float3(0, 1, 7), float3(0, 0, 0), float3(0, 1, 0));
	vp.transform();

	Color color(0, 0, 0, 0);
	colorBuffer.clearColor(color);
	colorBuffer.clearDepth();

#pragma region Save to file
	/*colorBuffer.saveFile("outputFile.tga");*/
#pragma endregion

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
	float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

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

		/*Triangle triang = Triangle();
		triang.draw(rasterizer, vp);*/

		/*Cube cube = Cube(8, 12);
		cube.draw(rasterizer, vp);*/

		/*Cone cone = Cone(7);
		cone.draw(rasterizer, vp);*/

		/*Sphere sphere = Sphere(10, 15);
		sphere.draw(rasterizer, vp);*/

		Cylinder cylinder = Cylinder(15, 8);
		cylinder.draw(rasterizer, vp);

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