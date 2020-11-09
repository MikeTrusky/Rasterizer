#include "VertexProcessor.h"
#include <math.h>
#include <iostream>

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= PI / 360;
	float f = cos(fovy) / sin(fovy);
	view2proj.matrix[0] = float4(f / aspect, 0, 0, 0);
	view2proj.matrix[1] = float4(0, f, 0, 0);
	view2proj.matrix[2] = float4(0, 0, (far + near) / (near - far), -1);
	view2proj.matrix[3] = float4(0, 0, 2 * far * near / (near - far), 0);
}

void VertexProcessor::setLookAt(float3 eye, float3 center, float3 up)
{
	float3 f = center - eye;
	normalize(f);	
	normalize(up);
	float3 s = cross(f, up);
	float3 u = cross(s, f);
	world2view.matrix[0] = float4(s.x, u.x, -f.x, 0);
	world2view.matrix[1] = float4(s.y, u.y, -f.y, 0);
	world2view.matrix[2] = float4(s.z, u.z, -f.z, 0);
	world2view.matrix[3] = float4(0, 0, 0, 1);

	float4x4 m(float4(1, 0, 0, 0),
			   float4(0, 1, 0, 0),
			   float4(0, 0, 1, 0),
			   float4(-eye.x, -eye.y, -eye.z, 1));
	world2view = mul(world2view, m);
}

void VertexProcessor::setIdentityView()
{
	world2view.matrix[0] = float4(1, 0, 0, 0);
	world2view.matrix[1] = float4(0, 1, 0, 0);
	world2view.matrix[2] = float4(0, 0, 1, 0);
	world2view.matrix[3] = float4(0, 0, 0, 1);
}

void VertexProcessor::setIdentity()
{
	obj2world.matrix[0] = float4(1, 0, 0, 0);
	obj2world.matrix[1] = float4(0, 1, 0, 0);
	obj2world.matrix[2] = float4(0, 0, 1, 0);
	obj2world.matrix[3] = float4(0, 0, 0, 1);
}

void VertexProcessor::multByRot(float a, float3 v)
{
	/*float s = sin(a * PI / 180), c = cos(a * PI / 180);
	normalize(v);
	float4x4 m();
	obj2world = mul(obj2world, m);*/
}

void VertexProcessor::multByTrans(float3)
{
	float4x4 m(float4(1, 0, 0, 0), float4(0, 1, 0, 0), float4(0, 0, 1, 0), float4(0, 0, 0, 1));
	obj2world = mul(obj2world, m);
}

void VertexProcessor::transform(void)
{
	/*obj2view = mul(world2view, obj2world);
	obj2proj = mul(view2proj, obj2view);
*/
	/*std::cout << "obj2world" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << obj2world[i][j] << "\t";
		std::cout << std::endl;
	}*/
	std::cout << "\t\t" << "view2proj" << std::endl << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "[";
		for (int j = 0; j < 4; j++)
			std::cout << view2proj[i][j] << "\t\t";
		std::cout << "]" << std::endl;
	}
	/*std::cout << "world2view" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << world2view[i][j] << "\t";
		std::cout << std::endl;
	}
	std::cout << "obj2proj" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << obj2proj[i][j] << "\t";
		std::cout << std::endl;
	}*/
}

float3 VertexProcessor::tr(const float3 &v)
{
	float4 r = mul(view2proj, float4(v.x, v.y, v.z, 1));
	std::cout << std::endl << std::endl;
	if (r.w != 0)
	{
		std::cout << "[" << r.x / r.w << ", " << r.y / r.w << ", " << r.z / r.w << " ]" << std::endl;
		return float3(r.x / r.w, r.y / r.w, r.z / r.w);
	}
	else
	{
		std::cout << "[" << r.x << ", " << r.y << ", " << r.z << " ]" << std::endl;
		return float3(r.x, r.y, r.z);
	}
}

float3 VertexProcessor::lt(const float3 &, const float3 &, const float3 &)
{
	return float3();
}