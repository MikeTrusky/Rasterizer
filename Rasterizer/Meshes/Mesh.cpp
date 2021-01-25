#include "Mesh.h"
#include "Triangle.h"

Mesh::~Mesh()
{
	this->verticesSize = this->trianglesSize = 0;
	delete[]this->vertices;
	delete[]this->indices;
	this->vertices = NULL;
	this->indices = NULL;
}

void Mesh::draw(Rasterizer & rasterizer, VertexProcessor & vp)
{
	for (unsigned int i = 0; i < trianglesSize; ++i)
	{
		rasterizer.DrawTriangle(vp.tr(vertices[indices[i].x].position), vp.tr(vertices[indices[i].y].position), vp.tr(vertices[indices[i].z].position),
			Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));
	}
}

void Mesh::draw(Rasterizer & rasterizer, VertexProcessor & vp, Light &l)
{
	for (unsigned int i = 0; i < trianglesSize; ++i)
	{
		rasterizer.DrawTriangle(vp.tr(vertices[indices[i].x].position), vp.tr(vertices[indices[i].y].position), vp.tr(vertices[indices[i].z].position),
			Color(round(l.calculate(vertices[indices[i].x], vp).x * 255.0f), round(l.calculate(vertices[indices[i].x], vp).y * 255.0f), round(l.calculate(vertices[indices[i].x], vp).z * 255.0f)),
			Color(round(l.calculate(vertices[indices[i].y], vp).x * 255.0f), round(l.calculate(vertices[indices[i].y], vp).y * 255.0f), round(l.calculate(vertices[indices[i].y], vp).z * 255.0f)),
			Color(round(l.calculate(vertices[indices[i].z], vp).x * 255.0f), round(l.calculate(vertices[indices[i].z], vp).y * 255.0f), round(l.calculate(vertices[indices[i].z], vp).z * 255.0f)));
	}
}

void Mesh::draw(Rasterizer & rasterizer, VertexProcessor & vp, Light &l, bool perPixel)
{
	Vertex *processed = new Vertex[verticesSize];

	for (int i = 0; i < verticesSize; ++i)
		processed[i] = vp.tr(vertices[i]);

	for (int i = 0; i < trianglesSize; ++i)
	{
		rasterizer.DrawTriangle(processed[indices[i].x], processed[indices[i].y], processed[indices[i].z], l, vp);
	}
	delete[] processed;
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
		vertices[i].normal = float3(0, 0, 0);

	for (unsigned int i = 0; i < trianglesSize; ++i)
	{
		float3 div1 = vertices[indices[i].y].position - vertices[indices[i].x].position;
		float3 div2 = vertices[indices[i].z].position - vertices[indices[i].x].position;
		float3 crossResult = cross(div1, div2);
		float3 n = normalize(crossResult);

		vertices[indices[i].x].normal = vertices[indices[i].x].normal + n;
		vertices[indices[i].y].normal = vertices[indices[i].y].normal + n;
		vertices[indices[i].z].normal = vertices[indices[i].z].normal + n;
	}
	
	for (unsigned int i = 0; i < verticesSize; ++i)
		normalize(vertices[i].normal);
}

void Mesh::makeUV()
{
	//Spherical mapping: x - u, y - v
	for (unsigned int i = 0; i < verticesSize; ++i)
	{		
		//vertices[i].texturePos.x = (1 / (2 * PI)) * atan2(vertices[i].position.z, vertices[i].position.y);
		//vertices[i].texturePos.x = (((vertices[i].texturePos.x - (-1)) * (1 - 0)) / (1 - (-1)) + 0);

		vertices[i].texturePos.x = 0.5f + (atan2(vertices[i].position.x, vertices[i].position.z)) / (2 * PI);
		
		//vertices[i].texturePos.y = (1 / PI) * tan(vertices[i].position.y / (sqrt(vertices[i].position.x * vertices[i].position.x + vertices[i].position.y * vertices[i].position.y + vertices[i].position.z * vertices[i].position.z)));
		//vertices[i].texturePos.y = (((vertices[i].texturePos.y - (-1)) * (1 - 0)) / (1 - (-1)) + 0);

		vertices[i].texturePos.y = 0.5f + (asin(vertices[i].position.y)) / PI;

		vertices[i].texturePos.z = 0.0f;
	}
}