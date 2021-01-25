#pragma once

#include "../Processors/VertexProcessor.h"
#include "../Vertex.h"
#include "../MathLibrary/Helper.h"
#include "../Buffer/TGABuffer.h"

class Light
{
public:
	Light(float3 position, float3 ambient, float3 diffuse, float3 specular, float shine) : position(position), ambient(ambient), diffuse(diffuse), specular(specular), shine(shine), texture(nullptr) { };

	virtual float3 calculate(Vertex &f, VertexProcessor &vp) { return NULL; };

	float3 position, ambient, diffuse, specular;
	float shine;
	TGABuffer *texture;
};