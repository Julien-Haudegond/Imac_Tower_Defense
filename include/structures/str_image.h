#ifndef STR_IMAGE_H__
#define STR_IMAGE_H__

#include "str_pixel.h"

typedef struct Image
{
	unsigned int w,h;
	Pixel* pixel;
} Image;

#endif