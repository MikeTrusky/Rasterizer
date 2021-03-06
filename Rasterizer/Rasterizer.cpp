#include "Rasterizer.h"
#include "Meshes/Triangle.h"

inline int min(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

inline int max(int a, int b, int c)
{
	return a < b ? (b < c ? c : b) : (a < c ? c : a);
}

void Rasterizer::DrawTriangle(Triangle & triangle)
{
#pragma region Kanoniczna bry�a widzenia
	/*float x1 = CalculateCanonicalViewX(triangle.vertices[0].position.x);
	float x2 = CalculateCanonicalViewX(triangle.TriangleVertices[1].x);
	float x3 = CalculateCanonicalViewX(triangle.TriangleVertices[2].x);

	float y1 = CalculateCanonicalViewY(triangle.TriangleVertices[0].y);
	float y2 = CalculateCanonicalViewY(triangle.TriangleVertices[1].y);
	float y3 = CalculateCanonicalViewY(triangle.TriangleVertices[2].y);*/
	float x1 = CalculateCanonicalViewX(triangle.vertices[0].position.x);
	float x2 = CalculateCanonicalViewX(triangle.vertices[1].position.x);
	float x3 = CalculateCanonicalViewX(triangle.vertices[2].position.x);

	float y1 = CalculateCanonicalViewY(triangle.vertices[0].position.y);
	float y2 = CalculateCanonicalViewY(triangle.vertices[1].position.y);
	float y3 = CalculateCanonicalViewY(triangle.vertices[2].position.y);
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

#pragma region Sta�e
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

				//float depth = triangle.TriangleVertices[0].z * lambda1 + triangle.TriangleVertices[1].z * lambda2 + triangle.TriangleVertices[2].z * lambda3;
				float depth = triangle.vertices[0].position.z * lambda1 + triangle.vertices[1].position.z * lambda2 + triangle.vertices[2].position.z * lambda3;

				if (depth < buffer.getDepth(x, y))
				{
					float r = lambda1 * triangle.vertices[0].color.R + lambda2 * triangle.vertices[1].color.R + lambda3 * triangle.vertices[2].color.R;
					float g = lambda1 * triangle.vertices[0].color.G + lambda2 * triangle.vertices[1].color.G + lambda3 * triangle.vertices[2].color.G;
					float b = lambda1 * triangle.vertices[0].color.B + lambda2 * triangle.vertices[1].color.B + lambda3 * triangle.vertices[2].color.B;

					buffer.setDepth(x, y, depth);

					buffer.setPixelColor(x, y, Color(r, g, b, 0.0f));
				}
			}
		}
	}
}

void Rasterizer::DrawTriangle(float3 v1, float3 v2, float3 v3, Color c1, Color c2, Color c3)
{

#pragma region Kanoniczna bry�a widzenia
	float x1 = CalculateCanonicalViewX(v1.x);
	float x2 = CalculateCanonicalViewX(v2.x);
	float x3 = CalculateCanonicalViewX(v3.x);

	float y1 = CalculateCanonicalViewY(v1.y);
	float y2 = CalculateCanonicalViewY(v2.y);
	float y3 = CalculateCanonicalViewY(v3.y);
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

#pragma region Sta�e
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

	for (int x = buffer.minx; x <= buffer.maxx; x++)
	{
		for (int y = buffer.miny; y <= buffer.maxy; y++)
		{
			if ((x12 * (y - y1) - y12 * (x - x1) > 0 && !topleft1 || x12 * (y - y1) - y12 * (x - x1) >= 0 && topleft1) &&
				(x23 * (y - y2) - y23 * (x - x2) > 0 && !topleft2 || x23 * (y - y2) - y23 * (x - x2) >= 0 && topleft2) &&
				(x31 * (y - y3) - y31 * (x - x3) > 0 && !topleft3 || x31 * (y - y3) - y31 * (x - x3) >= 0 && topleft3))
			{
				float lambda1 = (y23 * (x - x3) - x23 * (y - y3)) * lambda1den;
				float lambda2 = (y31 * (x - x3) - x31 * (y - y3)) * lambda2den;
				float lambda3 = 1 - lambda1 - lambda2;

				float depth = v1.z * lambda1 + v2.z * lambda2 + v3.z * lambda3;

				if (depth < buffer.getDepth(x, y))
				{
					float r = lambda1 * c1.R + lambda2 * c2.R + lambda3 * c3.R;
					float g = lambda1 * c1.G + lambda2 * c2.G + lambda3 * c3.G;
					float b = lambda1 * c1.B + lambda2 * c2.B + lambda3 * c3.B;

					buffer.setDepth(x, y, depth);

					buffer.setPixelColor(x, y, Color(r, g, b, 0.0f));
				}
			}
		}
	}
}

void Rasterizer::DrawTriangle(Vertex &v1, Vertex &v2, Vertex &v3, Light &light, VertexProcessor &vp)
{

#pragma region Kanoniczna bry�a widzenia
	float x1 = CalculateCanonicalViewX(v1.position.x);
	float x2 = CalculateCanonicalViewX(v2.position.x);
	float x3 = CalculateCanonicalViewX(v3.position.x);

	float y1 = CalculateCanonicalViewY(v1.position.y);
	float y2 = CalculateCanonicalViewY(v2.position.y);
	float y3 = CalculateCanonicalViewY(v3.position.y);
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

#pragma region Sta�e
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

	for (int x = buffer.minx; x <= buffer.maxx; x++)
	{
		for (int y = buffer.miny; y <= buffer.maxy; y++)
		{
			if ((x12 * (y - y1) - y12 * (x - x1) > 0 && !topleft1 || x12 * (y - y1) - y12 * (x - x1) >= 0 && topleft1) &&
				(x23 * (y - y2) - y23 * (x - x2) > 0 && !topleft2 || x23 * (y - y2) - y23 * (x - x2) >= 0 && topleft2) &&
				(x31 * (y - y3) - y31 * (x - x3) > 0 && !topleft3 || x31 * (y - y3) - y31 * (x - x3) >= 0 && topleft3))
			{
				float lambda1 = (y23 * (x - x3) - x23 * (y - y3)) * lambda1den;
				float lambda2 = (y31 * (x - x3) - x31 * (y - y3)) * lambda2den;
				float lambda3 = 1 - lambda1 - lambda2;

				Vertex f(
					float3((v1.position.x * lambda1 + v2.position.x * lambda2 + v3.position.x * lambda3), (v1.position.y * lambda1 + v2.position.y * lambda2 + v3.position.y * lambda3), (v1.position.z * lambda1 + v2.position.z * lambda2 + v3.position.z * lambda3)),
					float3((v1.normal.x * lambda1 + v2.normal.x * lambda2 + v3.normal.x * lambda3), (v1.normal.y * lambda1 + v2.normal.y * lambda2 + v3.normal.y * lambda3), (v1.normal.z * lambda1 + v2.normal.z * lambda2 + v3.normal.z * lambda3)),
					v1.color, 
					float3((v1.texturePos.x * lambda1 + v2.texturePos.x * lambda2 + v3.texturePos.x * lambda3), (v1.texturePos.y * lambda1 + v2.texturePos.y * lambda2 + v3.texturePos.y * lambda3), 0)
				);

				float3 colorCalculated = light.calculate(f, vp);
				Color color = Color(round(colorCalculated.x * 255.0f), round(colorCalculated.y * 255.0f), round(colorCalculated.z * 255.0f), 0.0f);

				float depth = v1.position.z * lambda1 + v2.position.z * lambda2 + v3.position.z * lambda3;

				if (depth < buffer.getDepth(x, y))
				{
					buffer.setDepth(x, y, depth);

					buffer.setPixelColor(x, y, color);
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