#pragma once
#include "Mesh.h"
class Torus : public Mesh
{
public:
	Torus() = default;
	Torus(int sides, int c_sides);
};

