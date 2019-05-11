#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/const.h"

#include "../include/monster.h"
#include "../include/wave.h"
#include "../include/tower.h"
#include "../include/tower_list.h"

#include "../include/itd.h"
#include "../include/node.h"
#include "../include/image.h"

#include "../include/map_draw.h"
#include "../include/window.h"
#include "../include/sprite.h"

#include "../include/text.h"
#include "../include/graphic.h"

#include "../include/args.h"

#include "../include/sdl_array.h"

//removing uninitialized values warning (functions setting values to pointers)
#pragma GCC diagnostic ignored "-Wuninitialized"


/***************
*   define : 
*   READTHIS 1 for PPM check & map debug + sprites
*   READTHIS 2 for tests on monsters path
*   READTHIS 3 for tests on monsters / towers / and lists
****************/
#define READTHIS1

#ifdef READTHIS1

void handleGameEvents(SDL_Event e, SDL_Surface** surface, int* mouse_x, int* mouse_y, int* help);

int main(int argc, char** argv) 
{

    //Checking arguments
    char itdPath[70]="data/";
    if(argc >= 2 && strcmp(checkITDFile(argv[1]), "itd") == 0){        
        strcat(itdPath,argv[1]);
    }else{
        fprintf(stderr, "Second argument must be an itd file.");
        exit(EXIT_FAILURE);
    }

    //Loading ITD File
    Image imgPPM;
    ItdColorInstruction itdInstructions[NUMBER_INSTRUCT] = {0};
    Node nodesArray[MAX_NODES] = {0};
    int nbOfNodes;

    readITD(itdPath, &imgPPM, itdInstructions, nodesArray, &nbOfNodes);

    //test valarc et init Dijkstra
    setValarc(nodesArray, 4);
   
    for(int i = 0; i < nbOfNodes; i++) {
        initializeDijkstra(&nodesArray[i]);
        printNodeInfo(nodesArray[i]);
        printf("Minvalarc du Node : %d \n", nodesArray[i].minValarc);
        //printf("\n");
    }

    /***********
    * TESTS ON DIJKSTRA FUNCTIONS
    ***********/

    printf("\n ****** TESTS UDPATES VALARCS ****** \n");
    initializeDijkstra(&nodesArray[0]);
    updateNodesMinValarc(&nodesArray[0]);
    printf("\n TEST MINVALARC NOEUD 0 : %d \n", nodesArray[0].minValarc);
    printf("\n TEST MINVALARC NOEUD 1 : %d \n", nodesArray[1].minValarc);


    /* Initializing SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /*Initializing TTF */
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
   
    /* Open a window and create the OpenGL context */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Title of the window */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    /* SPRITES: Loading surfaces and initializing textures */
    SDL_Surface* sprite_img[MAX_SPRITES];
    GLuint sprite_texture[MAX_SPRITES];

    initSurfacesArrayToNull(sprite_img, MAX_SPRITES);
    fillSprites(sprite_img, sprite_texture); // GO TO SPRITE.C TO MODIFY

  	/* TEXTS */
  		//Loading FONTS
    	TTF_Font* fonts[MAX_FONTS];
    	initFontsArrayToNull(fonts, MAX_FONTS);
    	initFontsArray(fonts); // GO TO TEXT.C TO MODIFY

    	//COLORS
    	SDL_Color colors[MAX_COLORS];
    	initColorsArray(colors); // GO TO TEXT.C TO MODIFY

    	//Loading SURFACES
		SDL_Surface* text_area[MAX_TEXTS];
    	initSurfacesArrayToNull(text_area, MAX_TEXTS);

    	//Initializing TEXTURES
	    GLuint text_texture[MAX_TEXTS];
	    GLuint help_window_texture[MAX_TEXTS];

	    //WRITING texts
	    fillTextsArrays(fonts, colors, text_area, text_texture); // GO TO TEXT.C TO MODIFY
  
    /* Global variables */
    int mouse_x = 0, mouse_y = 0;
    int help = 0;

    /* Global variables for GL Lists */
    GLuint debug_draw = createMapIDList(&imgPPM, itdInstructions, sprite_texture);
    GLuint help_window = createHelpList(help_window_texture);

    /* MAIN LOOP */
    int loop = 1;
    while(loop) 
    {
        /* Time at the beginning of the loop */
        Uint32 startTime = SDL_GetTicks();
        
        /* Drawing code */
	        glClear(GL_COLOR_BUFFER_BIT);

	        glMatrixMode(GL_MODELVIEW);
	        glLoadIdentity();

	        glCallList(debug_draw);
	        renderCenterText(&text_area[0], &text_texture[0], 610, 700);

	        if(help == 1) {
	        	glCallList(help_window);
	        }

	        //available area test
	        //constructionGuides(mouse_x, mouse_y, &imgPPM, itdInstructions, sprite_texture);

        /* Update window */
        SDL_GL_SwapBuffers();
        
        /* Event loop */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                loop = 0;
                break;
            }

            handleGameEvents(e, &surface, &mouse_x, &mouse_y, &help);
        }

        /* Passed time */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* If too few time, the program is paused */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Close fonts */
    closeAllFonts(fonts, MAX_FONTS);

    /* Free sprites */
    freeSurfacesArray(sprite_img, MAX_SPRITES);
    freeTexturesArray(sprite_texture, MAX_SPRITES);

    /* Free texts */
    freeSurfacesArray(text_area, MAX_TEXTS);
    freeTexturesArray(text_texture, MAX_TEXTS);
    freeTexturesArray(help_window_texture, MAX_TEXTS);

    /* Free links of all nodes and the PPM */
    for(int i = 0; i < nbOfNodes; i++) {
        freeAllLinks(nodesArray[i].link);
    }
    freeImage(&imgPPM);

    /* Free TTF */
    TTF_Quit();

    /* Free SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;
}


void handleGameEvents(SDL_Event e, SDL_Surface** surface, int* mouse_x, int* mouse_y, int* help) {
    switch(e.type) 
    {
        /* Redimensionnement fenetre */
        case SDL_VIDEORESIZE:
            reshape(surface, e.resize.w, e.resize.h);
            break;
        
        /* Touche clavier */
        case SDL_KEYDOWN:

			if(e.key.keysym.sym == SDLK_h) {
				*help = 1;
			} 
            break;

        case SDL_KEYUP:

			if(e.key.keysym.sym == SDLK_h) {
				*help = 0;
			}
			break;

        case SDL_MOUSEMOTION:
            *mouse_x = e.button.x * WINDOW_WIDTH / (*surface)->w;
            *mouse_y = e.button.y * WINDOW_HEIGHT / (*surface)->h;
            //printf("clic en : window(%d, %d)\n", mouse_x, mouse_y);
            break;               
            
        default:
            break;
    }
}



#endif



#ifdef READTHIS2

int main(int argc, char** argv) 
{
	Image imgPPM;
	ItdColorInstruction itdInstructions[NUMBER_INSTRUCT] = {0};
	Node nodesArray[MAX_NODES] = {0};
	int nbOfNodes;

    readITD("data/Map_01.itd", &imgPPM, itdInstructions, nodesArray, &nbOfNodes);
    
    

    //Printf the five instructions' values
	for(int i = 0; i < NUMBER_INSTRUCT; i++) {
		printf("%s : %d %d %d\n", itdInstructions[i].name, itdInstructions[i].r, itdInstructions[i].g, itdInstructions[i].b);
	}
    

    printf("Nombre de noeuds : %d\n", nbOfNodes);

    for(int i = 0; i < nbOfNodes; i++) {
    	printNodeInfo(nodesArray[i]);
    }

    //checkPathBetween2Nodes(nodesArray[1], nodesArray[2], &imgPPM, itdInstructions);

    //Faut free les linkkkksss et l'image
    for(int i = 0; i < nbOfNodes; i++) {
    	freeAllLinks(nodesArray[i].link);
    }
    freeImage(&imgPPM);

    /***************
    *   INITIALISATION SDL
    ***************/

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
  
    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
    /* Boucle principale */
    int loop = 1;

    while(loop){
        glClear(GL_COLOR_BUFFER_BIT);
        /*Refreshing*/
        SDL_GL_SwapBuffers();
        SDL_Event e;
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        /* Boucle traitant les evenements */
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
        
            if( e.type == SDL_KEYDOWN 
                && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                loop = 0; 
                break;
            }
        
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Redimensionnement fenetre */
                case SDL_VIDEORESIZE:
                    reshape(&surface, e.resize.w, e.resize.h);
                    break; 
            
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);        
                    break;                
                default:
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}


#endif

#ifdef READTHIS3

void TestMonsters2(){
    Monster *m;
    createMonster(m, GIANT, 1);
    Monster *m2;
    createMonster(m2, SWARMLING, 2);
    
    Wave* wave = addMonster(wave, *m);
    wave = addMonster(wave, *m2);
    
    wave->nextMonster->monster.health = 0;

    printWave(wave);
    wave = deleteMonster(wave);
    wave = deleteMonster(wave);
    printWave(wave);
    
}

void TestTower(){
    Tower* t = createTower(t, WATER);
    //printTower(t);
    Tower* t1 = createTower(t, ROCKET);
    //printTower(t1);
    TowerList* tl = addTower(tl, *t);
    tl = addTower(tl, *t1);
    printTowerList(tl);
    free(tl);
}
//Main pour tests
int main(){
    TestMonsters2();
    return 0;
}

#endif