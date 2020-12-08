#include "Mesh.h"
#include "Triangle.h"

Mesh::~Mesh()
{
	//this->verticesSize = this->trianglesSize = 0;
	//delete[]this->vertices;
	//delete[]this->indices;
	//this->vertices = NULL;
	//this->indices = NULL;
}

void Mesh::draw(Rasterizer & rasterizer, VertexProcessor & vp)
{
	for (unsigned int i = 0; i < trianglesSize; ++i)
	{
		rasterizer.DrawTriangle(vp.tr(vertices[indices[i].x].position), vp.tr(vertices[indices[i].y].position), vp.tr(vertices[indices[i].z].position),
			Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));
	}
}

void Mesh::SetArrays(int verticesSize, int trianglesSize)
{
	this->verticesSize = verticesSize;
	this->trianglesSize = trianglesSize;
	vertices = new Vertex[verticesSize];
	indices = new int3[trianglesSize];
}

void Mesh::makeNormals()
{
	for (unsigned int i = 0; i < verticesSize; ++i)
		vertices[i].normal = 0;
	for (unsigned int i = 0; i < trianglesSize; ++i)
	{
		float3 div1 = vertices[indices[i].z].position - vertices[indices[i].x].position;
		float3 div2 = vertices[indices[i].y].position - vertices[indices[i].x].position;
		float3 crossResult = cross(div1, div2);
		float3 n = normalize(crossResult);

		vertices[indices[i].x].normal = vertices[indices[i].x].normal + n;
		vertices[indices[i].y].normal = vertices[indices[i].y].normal + n;
		vertices[indices[i].z].normal = vertices[indices[i].z].normal + n;
	}
	
	for (unsigned int i = 0; i < verticesSize; ++i)
		normalize(vertices[i].normal);
}
