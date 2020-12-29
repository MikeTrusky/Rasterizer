#pragma once
#include "Mesh.h"

class Cylinder : public Mesh
{
public:
	Cylinder() = default;
	Cylinder(int v, int h);
};