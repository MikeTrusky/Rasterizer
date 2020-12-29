#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(float3 position, float3 ambient, float3 diffuse, float3 specular, float shine) : Light(position, ambient, diffuse, specular, shine) {};

	float3 calculate(Vertex &f, VertexProcessor &vp) override;
};