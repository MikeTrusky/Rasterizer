#pragma once
#include <cstdint>
#include "../Color.h"

class Buffer
{
public:
	uint32_t *frame;
	float *depth;
	int w, h, minx, maxx, miny, maxy, len;

	Buffer(int w, int h);
	void setSize(int size);
	void clearColor(Color &color);
	void clearDepth();
	
	void setDepth(int x, int y, float depth);
	float getDepth(int x, int y);

	void setPixelColor(int x, int y, const Color &color);
};

