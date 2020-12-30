#pragma once
#include "../MathLibrary/Helper.h"
#include "../Vertex.h"

class VertexProcessor
{
public:
	VertexProcessor() = default;

	float4x4 obj2world, world2view, view2proj;
	float4x4 obj2proj, obj2view;

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(float3 eye, float3 center, float3 up);
	void setIdentityView();
	void setIdentity();
	void multByRotation(float a, float3 vec);
	void multByTranslation(float3 vec);
	void multByScale(float3 vec);
	void transform(void);

	float3 tr(const float3 &v);
	Vertex tr(const Vertex &v);
	float3 tr_obj2view(const float3 &v, float w);
};