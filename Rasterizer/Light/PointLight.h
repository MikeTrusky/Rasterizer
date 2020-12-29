#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(float3 position, float3 ambient, float3 diffuse, float3 specular, float shine) : Light(position, ambient, diffuse, specular, shine) {};

	float3 calculate(Vertex &f, VertexProcessor &vp) override;
};