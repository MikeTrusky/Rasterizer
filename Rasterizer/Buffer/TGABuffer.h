#pragma once
#include "Buffer.h"
#include <iostream>

class TGABuffer : public Buffer
{
public:
	TGABuffer(int w, int h) : Buffer(w, h) {};
	int saveFile(const char* fileName);
	int loadFile(const char* fileName);
};