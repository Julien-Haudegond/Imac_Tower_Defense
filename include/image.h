#ifndef IMAGE_H__
#define IMAGE_H__

#include "pixel.h"

typedef struct Image
{
	unsigned int w,h;
	Pixel* pixel;
} Image;


void newImage(Image* I, unsigned int w, unsigned int h);
void freeImage(Image* I);
int loadImage(Image* I, const char* fichier);

#endif