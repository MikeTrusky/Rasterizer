#pragma once

struct float3
{
	float x, y, z;
	float3() = default;
	float3(float x, float y, float z) : x(x), y(y), z(z) {};
};
