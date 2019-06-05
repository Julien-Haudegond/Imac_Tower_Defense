#ifndef IMAGE_H__
#define IMAGE_H__

#include "../structures/str_image.h"

void newImage(Image* I, unsigned int w, unsigned int h);
void freeImage(Image* I);
int loadImage(Image* I, const char* fichier);

#endif