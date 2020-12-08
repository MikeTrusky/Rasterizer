#include "Sphere.h"

Sphere::Sphere(int vert, int horiz)
{
	SetArrays(vert * (horiz + 2), 2 * vert * horiz);

	for (unsigned int i = 0; i <= horiz + 1; ++i)
	{
		float y = cos(i * PI / (horiz + 1.f));
		float r = sqrt(1 - y * y);
		for (unsigned int j = 0; j < vert; ++j)
		{
			float x = r * cos(2 * PI * j / vert);
			float z = r * sin(2 * PI * j / vert);
			vertices[j + i * vert].position = float3(x, y, z);
		}
	}

	for (unsigned int i = 0; i < horiz; ++i)
	{
		for (unsigned int j = 0; j < vert; ++j)
		{
			indices[j + 2 * i * vert] = int3((j + 1) % vert + i * vert, j + vert + i * vert, (j + 1) % vert + vert + i * vert);
			indices[j + vert + 2 * i * vert] = int3(j + vert + i * vert, j + 2 * vert + i * vert, (j + 1) % vert + vert + i * vert);
		}
	}
}