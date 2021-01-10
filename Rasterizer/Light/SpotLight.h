#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(float3 position, float3 ambient, float3 diffuse, float3 specular, float shine, float cutoff, float3 direction) : Light(position, ambient, diffuse, specular, shine), Cutoff(cutoff), direction(direction) { normalize(direction); };

	float3 calculate(Vertex &f, VertexProcessor &vp) override;

	float3 direction;
	float Cutoff;
};