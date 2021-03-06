#pragma once
#include <cstdint>

class Color
{
public:
	float R, G, B, A;

	Color() = default;
	Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {};
	Color(float r, float g, float b) : R(r), G(g), B(b), A(0) {};

	uint32_t ToUint32_t() const;

	Color operator + (const Color &c) const;
	Color operator - (const Color &c) const;
	Color operator * (float f) const;
};