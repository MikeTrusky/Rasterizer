#include "Buffer.h"

Buffer::Buffer(int w, int h) : w(w), h(h)
{
	setSize(w * h);
	depth = new float[w*h];
}

void Buffer::setSize(int size)
{
	frame = new uint32_t[size];
}

void Buffer::clearColor(Color &color)
{
	for(int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			setPixelColor(i, j, color);
		}
}

void Buffer::clearDepth()
{
	for(int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			depth[i + j * w] = 1;
		}
}

void Buffer::setDepth(int x, int y, float _depth)
{
	depth[x + y * w] = _depth;
}

float Buffer::getDepth(int x, int y)
{
	return depth[x + y * w];
}

void Buffer::setPixelColor(int x, int y, const Color &color)
{
	frame[x + y * w] = color.ToUint32_t();
}
