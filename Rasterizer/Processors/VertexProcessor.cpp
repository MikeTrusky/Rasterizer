#include "VertexProcessor.h"
#include <math.h>
#include <iostream>

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= PI / 360;
	float f = cos(fovy) / sin(fovy);
	view2proj.matrix[0] = float4(f / aspect, 0, 0, 0);
	view2proj.matrix[1] = float4(0, f, 0, 0);
	view2proj.matrix[2] = float4(0, 0, (far + near) / (near - far), 2 * far * near / (near - far));
	view2proj.matrix[3] = float4(0, 0, -1, 0);
}

void VertexProcessor::setLookAt(float3 eye, float3 center, float3 up)
{
	float3 f = center - eye;
	normalize(f);
	normalize(up);
	float3 s = cross(f, up);
	float3 u = cross(s, f);
	world2view.matrix[0] = float4(s.x, s.y, s.z, -eye.x);
	world2view.matrix[1] = float4(u.x, u.y, u.z, -eye.y);
	world2view.matrix[2] = float4(-f.x, -f.y, -f.z, -eye.z);
	world2view.matrix[3] = float4(0, 0, 0, 1);
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

void VertexProcessor::multByRotation(float a, float3 vec)
{
	float s = sin(a * PI / 180), c = cos(a * PI / 180);
	normalize(vec);
	float4x4 m(float4(vec.x * vec.x * (1 - c) + c, vec.y * vec.x * (1 - c) - vec.z * s, vec.x * vec.z * (1 - c) + vec.y * s, 0),
		float4(vec.x * vec.y * (1 - c) + vec.z * s, vec.y * vec.y * (1 - c) + c, vec.y * vec.z * (1 - c) - vec.x * s, 0),
		float4(vec.x * vec.z * (1 - c) - vec.y * s, vec.y * vec.z * (1 - c) + vec.x * s, vec.z * vec.z * (1 - c) + c, 0),
		float4(0, 0, 0, 1));
	obj2world = mul(m, obj2world);
}

void VertexProcessor::multByTranslation(float3 vec)
{
	float4x4 m(float4(1, 0, 0, vec.x),
		float4(0, 1, 0, vec.y),
		float4(0, 0, 1, vec.z),
		float4(0, 0, 0, 1));
	obj2world = mul(m, obj2world);
}

void VertexProcessor::multByScale(float3 vec)
{
	float4x4 m(float4(vec.x, 0, 0, 0),
		float4(0, vec.y, 0, 0),
		float4(0, 0, vec.z, 0),
		float4(0, 0, 0, 1));
	obj2world = mul(m, obj2world);
}

void VertexProcessor::transform(void)
{
	obj2view = mul(world2view, obj2world);
	obj2proj = mul(view2proj, obj2view);

#pragma region wypisywanie
	/*std::cout << "obj2world" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << obj2world[i][j] << "\t";
		std::cout << std::endl;
	}*/
	/*std::cout << "\t\t" << "view2proj" << std::endl << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "[";
		for (int j = 0; j < 4; j++)
			std::cout << view2proj[i][j] << "\t\t";
		std::cout << "]" << std::endl;
	}*/
	/*std::cout << "world2view" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << world2view[i][j] << "\t";
		std::cout << std::endl;
	}*/
	/*std::cout << "obj2proj" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << obj2proj[i][j] << "\t";
		std::cout << std::endl;
	}*/
#pragma endregion
}

float3 VertexProcessor::tr(const float3 &v)
{
	float4 r = mul(obj2proj, float4(v.x, v.y, v.z, 1));

	if (r.w != 0)
	{
		return float3(r.x / r.w, r.y / r.w, r.z / r.w);
	}
	else
	{
		return float3(r.x, r.y, r.z);
	}
}

Vertex VertexProcessor::tr(const Vertex & v)
{
	float4 r = mul(obj2proj, float4(v.position.x, v.position.y, v.position.z, 1));

	if (r.w != 0)
	{
		return Vertex(r.x / r.w, r.y / r.w, r.z / r.w, v.normal.x, v.normal.y, v.normal.z, v.texturePos.x, v.texturePos.y);
	}
	else
	{
		return Vertex(r.x, r.y, r.z, v.normal.x, v.normal.y, v.normal.z, v.texturePos.x, v.texturePos.y);
	}
}

float3 VertexProcessor::tr_obj2view(const float3 & v, float w, bool spotLight)
{
	float4 r;

	if (!spotLight)
		r = mul(obj2view, float4(v.x, v.y, v.z, w));
	else if (spotLight)
		r = mul(world2view, float4(v.x, v.y, v.z, w));

	if (w != 0)
	{
		return float3(r.x / r.w, r.y / r.w, r.z / r.w);
	}
	else
	{
		return float3(r.x, r.y, r.z);
	}
}