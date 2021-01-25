#pragma once
#include "../Vertex.h"
#include "../Rasterizer.h"
#include "../Processors/VertexProcessor.h"
#include "../MathLibrary/Helper.h"
#include "../Light/Light.h"

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
	void draw(Rasterizer &rasterizer, VertexProcessor &vp, Light &l);
	void draw(Rasterizer &rasterizer, VertexProcessor &vp, Light &l, bool perPixel);
	void SetArrays(int verticesSize, int trianglesSize);
	void makeNormals();
	void makeUV();
};