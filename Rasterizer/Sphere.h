#pragma once
#include "Mesh.h"
class Sphere : public Mesh
{
public:
	Sphere() = default;
	Sphere(int vert, int horiz);
};