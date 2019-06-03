#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/args.h"
#include "../include/game.h"
#include "../include/menu.h"
#include "../include/intro.h"

int main(int argc, char const *argv[])
{

	 //Checking arguments
    char itdPath[70]="data/";
    if(argc >= 2 && strcmp(checkITDFile(argv[1]), "itd") == 0){        
        strcat(itdPath,argv[1]);
    }else{
        fprintf(stderr, "Second argument must be an itd file.");
        exit(EXIT_FAILURE);
    }

    playIntro();

	return EXIT_SUCCESS;
}