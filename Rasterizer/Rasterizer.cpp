#include "Rasterizer.h"

inline int min(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

inline int max(int a, int b, int c)
{
	return a < b ? (b < c ? c : b) : (a < c ? c : a);
}

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a < b ? b : a;
}

void Rasterizer::DrawTriangle(Triangle & triangle)
{
#pragma region Kanoniczna bry³a widzenia
	float x1 = CalculateCanonicalViewX(triangle.vertices[0].x);
	float x2 = CalculateCanonicalViewX(triangle.vertices[1].x);
	float x3 = CalculateCanonicalViewX(triangle.vertices[2].x);

	float y1 = CalculateCanonicalViewY(triangle.vertices[0].y);
	float y2 = CalculateCanonicalViewY(triangle.vertices[1].y);
	float y3 = CalculateCanonicalViewY(triangle.vertices[2].y);
#pragma endregion

#pragma region Przeszukiwanie
	buffer.minx = min(static_cast<int>(x1), static_cast<int>(x2), static_cast<int>(x3));
	buffer.maxx = max(static_cast<int>(x1), static_cast<int>(x2), static_cast<int>(x3));
	buffer.miny = min(static_cast<int>(y1), static_cast<int>(y2), static_cast<int>(y3));
	buffer.maxy = max(static_cast<int>(y1), static_cast<int>(y2), static_cast<int>(y3));
#pragma endregion

#pragma region Obcinanie
	buffer.minx = (int)max(buffer.minx, 0);
	buffer.maxx = (int)min(buffer.maxx, buffer.w - 1);
	buffer.miny = (int)max(buffer.miny, 0);
	buffer.maxy = (int)min(buffer.maxy, buffer.h - 1);
#pragma endregion

#pragma region Sta³e
	float x12 = x1 - x2;
	float x13 = x1 - x3;
	float x23 = x2 - x3;
	float x32 = x3 - x2;
	float x31 = x3 - x1;

	float y12 = y1 - y2;
	float y13 = y1 - y3;
	float y23 = y2 - y3;
	float y31 = y3 - y1;

	float lambda1den = 1.0f / (-y23 * x31 + x23 * y31);
	float lambda2den = 1.0f / (y31 * x23 - x31 * y23);
#pragma endregion

#pragma region "Top-left"
	bool topleft1 = (y12 < 0 || (y12 == 0 && x12 > 0));
	bool topleft2 = (y23 < 0 || (y23 == 0 && x23 > 0));
	bool topleft3 = (y31 < 0 || (y31 == 0 && x31 > 0));
#pragma endregion

	for (int x = buffer.minx; x < buffer.maxx; x++)
	{
		for (int y = buffer.miny; y < buffer.maxy; y++)
		{
			if ((x12 * (y - y1) - y12 * (x - x1) > 0 && !topleft1 || x12 * (y - y1) - y12 * (x - x1) >= 0 && topleft1) &&
				(x23 * (y - y2) - y23 * (x - x2) > 0 && !topleft2 || x23 * (y - y2) - y23 * (x - x2) >= 0 && topleft2) &&
				(x31 * (y - y3) - y31 * (x - x3) > 0 && !topleft3 || x31 * (y - y3) - y31 * (x - x3) >= 0 && topleft3))
			{
				float lambda1 = (y23 * (x - x3) - x23 * (y - y3)) * lambda1den;
				float lambda2 = (y31 * (x - x3) - x31 * (y - y3)) * lambda2den;
				float lambda3 = 1 - lambda1 - lambda2;

				float depth = triangle.vertices[0].z * lambda1 + triangle.vertices[1].z * lambda2 + triangle.vertices[2].z * lambda3;

				if (depth < buffer.getDepth(x, y))
				{
					float r = lambda1 * triangle.colors[0].R + lambda2 * triangle.colors[1].R + lambda3 * triangle.colors[2].R;
					float g = lambda1 * triangle.colors[0].G + lambda2 * triangle.colors[1].G + lambda3 * triangle.colors[2].G;
					float b = lambda1 * triangle.colors[0].B + lambda2 * triangle.colors[1].B + lambda3 * triangle.colors[2].B;

					buffer.setDepth(x, y, depth);

					buffer.setPixelColor(x, y, Color(r, g, b, 0.0f));
				}
			}
		}
	}
}

float Rasterizer::CalculateCanonicalViewX(float x)
{
	return (x + 1) * buffer.w * 0.5f;
}

float Rasterizer::CalculateCanonicalViewY(float y)
{
	return (y + 1) * buffer.h * 0.5f;
}