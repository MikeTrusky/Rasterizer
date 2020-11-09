#pragma once
#include "Helper.h"

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
	void multByRot(float, float3);
	void multByTrans(float3);
	void transform(void);

	float3 tr(const float3 &v);
	float3 lt(const float3 &, const float3 &, const float3 &);
};

