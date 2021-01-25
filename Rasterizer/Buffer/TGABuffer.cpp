#pragma warning(disable:4996)
#include "TGABuffer.h"

int TGABuffer::saveFile(const char * fileName)
{
	//32 bity na piksel
	unsigned short header[9] = {
	0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0100, 0x0100,   //width, height
	0x0820 };

	FILE* f = fopen(fileName, "wb+");
	if (NULL == f) return -1;

	header[6] = w;
	header[7] = h;

	fwrite(header, 2, 9, f);
	fwrite(frame, 4, w * h, f);
	fclose(f);
	return 0;
}

int TGABuffer::loadFile(const char* fileName)
{
	unsigned short header[9];
	FILE *f = fopen(fileName, "rb+");
	if (NULL == f) return -1;

	fread(header, 2, 9, f);
	if (w != header[6] || h != header[7]) return -2;

	fread(frame, 4, w*h, f);

	fclose(f);
	return 0;
}