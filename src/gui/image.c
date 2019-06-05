#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gui/image.h"


void newImage(Image* I, unsigned int w, unsigned int h)
{
	//Memory allocation
	I->pixel = calloc(1, w*h*sizeof(Pixel));
	if (I->pixel == NULL){
		fprintf(stderr, "Error: not enough memory.\n");
		exit(EXIT_FAILURE);
	}
	//Width and heigth attribution
	I->w = w;
	I->h = h;
}

//Free the allocated memory
void freeImage(Image* I)
{
	if (I)
	{
		free(I->pixel);
	}
}

int loadImage(Image* I, const char* fichier)
{
	int w, h, maxDepth, reader;
	char magicNumber[2] = {0};

	//Open a file
	FILE* F = fopen(fichier,"r");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	//Read the PPM Magic Number
	if(fscanf(F,"%s\n", magicNumber) != 1){
		fprintf(stderr, "Error during the header reading.\n");
		exit(EXIT_FAILURE);
	}

	//Check if the file is a P3 PPM
	if(magicNumber[0] != 'P' || magicNumber[1] != '3'){
		fprintf(stderr, "The file is not a P3 PPM.\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments
	reader = getc(F);
	//If the first character is a #, it reads the whole line and go to the next one
	while (reader == '#'){
		while(getc(F) != '\n');
		reader = getc(F);
	}
	ungetc(reader, F);
	
	//Read the width, height and maximum color depth.
	if(fscanf(F,"%d %d %d\n",&w,&h,&maxDepth) != 3){
		fprintf(stderr, "Error during dimensions reading.\n");
		exit(EXIT_FAILURE);
	}

	//Create a new image (array) with the right dimensions ; read the values of the PPM and store them in the empty array
	newImage(I,w,h);
	int red, green, blue;

	for (int i = 0; i < w*h; i++) {
		if(fscanf(F,"%d %d %d", &red, &green, &blue) != 3) {
			fprintf(stderr, "Error during data reading.\n");
			exit(EXIT_FAILURE);
		}

		I->pixel[i].r = red;
		I->pixel[i].g = green;
		I->pixel[i].b = blue;
	}

	fclose(F);
	return EXIT_SUCCESS;
}