#pragma once
#include "../Vertex.h"
#include "../Rasterizer.h"
#include "../Processors/VertexProcessor.h"
#include "../MathLibrary/Helper.h"

class Mesh
{
private:

public:
	Mesh() = default;
	~Mesh();
	int verticesSize;
	int trianglesSize;
	Vertex *vertices;
	int3 *indices;

	void draw(Rasterizer &rasterizer, VertexProcessor &vp);
	void SetArrays(int verticesSize, int trianglesSize);
	void makeNormals();
};

