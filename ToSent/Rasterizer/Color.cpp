#include "Color.h"

uint32_t Color::ToUint32_t() const
{
	return ((uint32_t)A << 24) | ((uint32_t)R << 16) | ((uint32_t)G << 8) | (uint32_t)B;
}

Color Color::operator+(const Color & c) const
{
	return Color(R + c.R, G + c.G, B + c.B, A + c.A);
}

Color Color::operator-(const Color & c) const
{
	return Color(R - c.R, G - c.G, B - c.B, A - c.A);
}

Color Color::operator*(float f) const
{
	return Color(R * f, G * f, B * f, A * f);
}
