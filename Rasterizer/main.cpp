#include <iostream>
#include <vector>

#include "Buffer/TGABuffer.h"

#include "Color.h"

#include "Meshes/Triangle.h"
#include "Meshes/Cube.h"
#include "Meshes/Cone.h"
#include "Meshes/Sphere.h"
#include "Meshes/Cylinder.h"

#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"

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
	TGABuffer colorBuffer = TGABuffer(1000, 1000);
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

	float cubePosition[3] = { 0.0, 0.0f, 0.0f };
	float cubeScale[3] = { 1.0f, 1.0f, 1.0f };
	float cubeAngleX = 0.0f, cubeAngleY = 0.0f, cubeAngleZ = 0.0f;

	float conePosition[3] = { -1.0f, 0.0f, 0.0f };
	float coneScale[3] = { 1.0f, 1.0f, 1.0f };
	float coneAngleX = 0.0f, coneAngleY = 0.0f, coneAngleZ = 0.0f;
	int coneVerticalDivisions = 7;

	float spherePosition[3] = { 0.0f, 0.0f, 0.0f };
	float sphereScale[3] = { 1.0f, 1.0f, 1.0f };
	float sphereAngleX = 0.0f, sphereAngleY = 0.0f, sphereAngleZ = 0.0f;
	int sphereVerticalDivisions = 15;
	int sphereHorizontalDivisions = 10;

	float cylinderPosition[3] = { 0.0f, 0.0f, 0.0f };
	float cylinderScale[3] = { 1.0f, 1.0f, 1.0f };
	float cylinderAngleX = 0.0f, cylinderAngleY = 0.0f, cylinderAngleZ = 0.0f;
	int cylinderVerticalDivisions = 15;
	int cylinderHorizontalDivisions = 8;

	float dirLightPosition[3] = { 0, 1, 0 };
	float dirLightAmbient[3] = { 0.1f, 0.1f, 0.1f };
	float dirLightDiffuse[3] = { 0.0f, 0.0f, 1.0f };
	float dirLightSpecular[3] = { 1, 1, 1 };
	float dirShine = 10;

	float pointLightPosition[3] = { 0, 0, -15 };
	float pointLightAmbient[3] = { 0, 0.6f, 0 };
	float pointLightDiffuse[3] = { 0, 0, 0.6f };
	float pointLightSpecular[3] = { 1, 0, 0 };
	float pointShine = 10;

	float eye[3] = { 0, 1, 15 };
	float center[3] = { 0, 0, -1 };
	float near = 0.001f;
	float far = 100.0f;
	float fov = 45.0f;
	float aspect = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		colorBuffer.clearColor(color);
		colorBuffer.clearDepth();

#pragma region Sliders

		ImGui::Begin("Look at");
		ImGui::SliderFloat3("Eye", eye, -10.0f, 30.0f);
		ImGui::SliderFloat3("Center", center, -10.0f, 10.0f);
		ImGui::End();

		ImGui::Begin("Perspective");
		ImGui::SliderFloat("FOV", &fov, 10.0f, 150.0f);
		ImGui::SliderFloat("Aspect", &aspect, 0.5f, 5.0f);
		ImGui::SliderFloat("Far", &far, 1.0f, 10.0f);
		ImGui::SliderFloat("near", &near, 0.001f, 10.0f);
		ImGui::End();

		ImGui::Begin("Cube transformations");
		ImGui::SliderFloat3("Position", cubePosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale", cubeScale, 0.0f, 5.0f);
		ImGui::SliderFloat("Angle Y", &cubeAngleY, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle X", &cubeAngleX, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle Z", &cubeAngleZ, -360.0f, 360.0f);
		ImGui::End();

		ImGui::Begin("Cone transformations");
		ImGui::SliderFloat3("Position", conePosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale", coneScale, 0.0f, 5.0f);
		ImGui::SliderFloat("Angle Y", &coneAngleY, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle X", &coneAngleX, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle Z", &coneAngleZ, -360.0f, 360.0f);
		ImGui::SliderInt("Vertical Divisions", &coneVerticalDivisions, 3, 30);
		ImGui::End();

		ImGui::Begin("Sphere transformations");
		ImGui::SliderFloat3("Position", spherePosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale", sphereScale, 0.0f, 5.0f);
		ImGui::SliderFloat("Angle Y", &sphereAngleY, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle X", &sphereAngleX, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle Z", &sphereAngleZ, -360.0f, 360.0f);
		ImGui::SliderInt("Vertical Divisions", &sphereVerticalDivisions, 3, 30);
		ImGui::SliderInt("Horizontal Divisions", &sphereHorizontalDivisions, 2, 20);
		ImGui::End();

		ImGui::Begin("Cylinder transformations");
		ImGui::SliderFloat3("Position", cylinderPosition, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale", cylinderScale, 0.0f, 5.0f);
		ImGui::SliderFloat("Angle Y", &cylinderAngleY, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle X", &cylinderAngleX, -360.0f, 360.0f);
		ImGui::SliderFloat("Angle Z", &cylinderAngleZ, -360.0f, 360.0f);
		ImGui::SliderInt("Vertical Divisions", &cylinderVerticalDivisions, 3, 30);
		ImGui::SliderInt("Horizontal Divisions", &cylinderHorizontalDivisions, 2, 20);
		ImGui::End();

		ImGui::Begin("Dir Light transformations");
		ImGui::SliderFloat3("Position", dirLightPosition, -1.0f, 1.0f);
		ImGui::SliderFloat3("Ambient", dirLightAmbient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse", dirLightDiffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", dirLightSpecular, 0.0f, 1.0f);
		ImGui::SliderFloat("Shine", &dirShine, 0.0f, 100.0f);
		ImGui::End();

		ImGui::Begin("Point Light transformations");
		ImGui::SliderFloat3("Position", pointLightPosition, -50.0f, 50.0f);
		ImGui::SliderFloat3("Ambient", pointLightAmbient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse", pointLightDiffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", pointLightSpecular, 0.0f, 1.0f);
		ImGui::SliderFloat("Shine", &pointShine, 0.0f, 100.0f);
		ImGui::End();

#pragma endregion

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		vp.setPerspective(fov, aspect, near, far);
		vp.setIdentityView();
		vp.setIdentity();
		vp.setLookAt(float3(eye[0], eye[1], eye[2]), float3(center[0], center[1], center[2]), float3(0, 1, 0));
		vp.transform();

		PointLight pLight = PointLight(float3(pointLightPosition[0], pointLightPosition[1], pointLightPosition[2]),
			float3(pointLightAmbient[0], pointLightAmbient[1], pointLightAmbient[2]),
			float3(pointLightDiffuse[0], pointLightDiffuse[1], pointLightDiffuse[2]),
			float3(pointLightSpecular[0], pointLightSpecular[1], pointLightSpecular[2]),
			float(pointShine));

		/*DirectionalLight pLight = DirectionalLight(float3(dirLightPosition[0], dirLightPosition[1], dirLightPosition[2]),
			float3(dirLightAmbient[0], dirLightAmbient[1], dirLightAmbient[2]),
			float3(dirLightDiffuse[0], dirLightDiffuse[1], dirLightDiffuse[2]),
			float3(dirLightSpecular[0], dirLightSpecular[1], dirLightSpecular[2]),
			float(dirShine));*/

#pragma region Cube
		/*vp.setIdentity();
		vp.multByScale(float3(cubeScale[0], cubeScale[1], cubeScale[2]));
		vp.multByRotation(cubeAngleY, float3(0, 1, 0));
		vp.multByRotation(cubeAngleX, float3(1, 0, 0));
		vp.multByRotation(cubeAngleZ, float3(0, 0, 1));
		vp.multByTranslation(float3(cubePosition[0], cubePosition[1], cubePosition[2]));
		vp.transform();

		Cube cube = Cube();
		cube.makeNormals();
		cube.draw(rasterizer, vp, pLight);*/
#pragma endregion

#pragma region Cone
		//vp.setIdentity();
		//vp.multByScale(float3(coneScale[0], coneScale[1], coneScale[2]));
		//vp.multByRotation(coneAngleY, float3(0, 1, 0));
		//vp.multByRotation(coneAngleX, float3(1, 0, 0));
		//vp.multByRotation(coneAngleZ, float3(0, 0, 1));
		//vp.multByTranslation(float3(conePosition[0], conePosition[1], conePosition[2]));
		//vp.transform();

		//Cone cone = Cone(coneVerticalDivisions);
		//cone.makeNormals();
		//cone.draw(rasterizer, vp, pLight);
#pragma endregion

#pragma region Sphere
		vp.setIdentity();
		vp.multByScale(float3(sphereScale[0], sphereScale[1], sphereScale[2]));
		vp.multByRotation(sphereAngleY, float3(0, 1, 0));
		vp.multByRotation(sphereAngleX, float3(1, 0, 0));
		vp.multByRotation(sphereAngleZ, float3(0, 0, 1));
		vp.multByTranslation(float3(-3.0f, 0.0f, 0.0f));
		vp.transform();

		Sphere sphere = Sphere(sphereVerticalDivisions, sphereHorizontalDivisions);
		sphere.makeNormals();
		sphere.draw(rasterizer, vp, pLight);

		vp.setIdentity();
		vp.multByTranslation(float3(3.0f, 0.0f, 0.0f));
		vp.transform();
		sphere.draw(rasterizer, vp, pLight);

		vp.setIdentity();
		vp.multByTranslation(float3(0.0f, 2.0f, 0.0f));
		vp.transform();
		sphere.draw(rasterizer, vp, pLight, true);

		vp.setIdentity();
		vp.multByTranslation(float3(0.0f, -2.0f, 0.0f));
		vp.transform();
		sphere.draw(rasterizer, vp, pLight, true);
#pragma endregion

#pragma region Cylinder
		/*vp.setIdentity();
		vp.multByScale(float3(cylinderScale[0], cylinderScale[1], cylinderScale[2]));
		vp.multByRotation(cylinderAngleY, float3(0, 1, 0));
		vp.multByRotation(cylinderAngleX, float3(1, 0, 0));
		vp.multByRotation(cylinderAngleZ, float3(0, 0, 1));
		vp.multByTranslation(float3(cylinderPosition[0], cylinderPosition[1], cylinderPosition[2]));
		vp.transform();

		Cylinder cylinder = Cylinder(cylinderVerticalDivisions, cylinderHorizontalDivisions);
		cylinder.makeNormals();
		cylinder.draw(rasterizer, vp, pLight);*/
#pragma endregion

		glDrawPixels(colorBuffer.w, colorBuffer.h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, colorBuffer.frame);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	colorBuffer.saveFile("outputFile.tga");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}