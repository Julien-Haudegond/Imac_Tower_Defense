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
#include "../include/link.h"
#include "../include/image.h"

#include "../include/map_draw.h"
#include "../include/window.h"
#include "../include/sprite.h"

#include "../include/text.h"
#include "../include/graphic.h"

#include "../include/args.h"

#include "../include/sdl_array.h"


/***************
*   define : 
*   READTHIS 1 for PPM check & map debug + sprites
*   READTHIS 2 for tests on monsters path
*   READTHIS 3 for tests on monsters / towers / and lists
****************/
#define READTHIS1

#ifdef READTHIS1

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


    //Initialize a list of towers and buildings 
    TowerList* towerList = createEmptyTowerList();

    //addTower(towerList, LASER, 100, 250); //TEST POUR VALARCS
    //addTower(towerList, ELECTRIC, 100, 50); //TEST POUR VALARCS
    //addTower(towerList, WATER, 500, 40); //TEST POUR VALARCS
    //addTower(towerList, WATER, 900, 700); //TEST POUR VALARCS

    printTowerList(towerList);
    printf("Il y a %d tours.\n", countTowers(towerList));

    towerList = deleteTower(towerList, 800, 50);

    printf("\n\n\n");

    printTowerList(towerList);
    printf("Il y a %d tours.\n", countTowers(towerList));

    updateAllValarcLinks(nodesArray, nbOfNodes, towerList);


    //test valarc et init Dijkstra
      
    for(int i = 0; i < nbOfNodes; i++) {
        initializeDijkstra(&nodesArray[i]);
        printNodeInfo(nodesArray[i]);
    }

    //Setting minValarc values for shortest path
    shortestPath(nodesArray, nbOfNodes);

    printf("\n \n ******* Test résultats Dijkstra ***** \n \n");
    for (int j = 0; j < nbOfNodes; j++){
        printNodeInfo(nodesArray[j]);
    }
    
    printf("\n \n ********** NODES CHEMIN LE + COURT ********** \n \n");
    int nbShortest = countNodesShortestPath(nodesArray);
    printf("Nombre de nodes : %d \n", nbShortest);
    int *nodesPath = malloc(nbShortest*sizeof(int));
    //filling nodesPath array
    fillShortestPath(nodesPath, nbShortest, nodesArray);
    for(int k = 0; k < nbShortest; k++){
        printf("Noeud %d : %d \n", k, nodesPath[k]);
    }

    //Test on monsters - waves
    Wave* wave = createEmptyWave();

    addMonster(wave, GIANT, 0, nodesPath, nbShortest);

    //initializing monster position
    wave->monster->currentNode = wave->monster->path[0];
    Node* nodesearch = getNodeFromValue(nodesArray, nbOfNodes,  wave->monster->currentNode);
    setPosition(wave->monster, nodesearch->win_x, nodesearch->win_y);

    printWave(wave);
    
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
    int help = -1; //To print the 'help' popup
    int constructStatus = -1; //To construct something
    int towerConstruct = -1, buildingConstruct = -1; //For construction types and validate constructions

    /* Global variables for GL Lists */
    GLuint debug_draw = createMapIDList(&imgPPM, itdInstructions, sprite_texture);
    GLuint help_window = createHelpList(help_window_texture);
    int pathIndex = 0;

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
            
	        //Hold a specific key to build towers or buildings
	        if(constructStatus != -1) {
	        	constructionGuides(mouse_x, mouse_y, &imgPPM, itdInstructions, sprite_texture);
	        	if(towerConstruct != -1) drawTowerGuides(mouse_x, mouse_y, towerConstruct, sprite_texture);
	        	//else if(buildingConstruct != -1) drawBuildingSprites(mouse_x, mouse_y, buildingConstruct, sprite_texture);
	        }

	        //TOWERS
	        if(towerList->tower) {
	        	TowerList* tmp = towerList;
	        	drawTowerSprite(tmp->tower, sprite_texture);

	        	while(tmp->nextTower) {
	        		tmp = tmp->nextTower;
	        		if(tmp->tower) {
	        			drawTowerSprite(tmp->tower, sprite_texture);
	        		}
	        	}
	        }
            
            if(wave->monster){    
                //update on sprites and current node
                drawMonsterSprite(wave->monster, sprite_texture);
                nodesearch = getNodeFromValue(nodesArray, nbOfNodes,  wave->monster->currentNode);
                
                if(nodesearch->type == 2 && nodesearch->win_x == wave->monster->win_x && nodesearch->win_y == wave->monster->win_y){
                    //free monster, and give money to the player
                }else{
                    //updates current node if it's been reached
                    if(wave->monster->path[pathIndex+1] && (wave->monster->win_x == nodesearch-> win_x && wave->monster->win_y == nodesearch->win_y)){
                        wave->monster->prevNode = wave->monster->currentNode;
                        pathIndex++;
                        wave->monster->currentNode = wave->monster->path[pathIndex];
                        nodesearch = getNodeFromValue(nodesArray, nbOfNodes, wave->monster->currentNode);
                    }
                    //updates monster coords if the node has not been reached
                    if((wave->monster->win_x != nodesearch-> win_x || wave->monster->win_y != nodesearch->win_y)){
                        updateCoords(wave->monster,nodesArray,nbOfNodes);
                    }
                }
            }
            
			//Hold 'h' to make the menu appear
	        if(help == 1) {
	        	glCallList(help_window);
	        }

        /* Update window */
        SDL_GL_SwapBuffers();
        
        /* Event loop */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                loop = 0;
                break;
            }

		    switch(e.type) 
		    {
		        /* Resize window */
		        case SDL_VIDEORESIZE:
		            reshape(&surface, e.resize.w, e.resize.h);
		            break;
		        
		        /* Keyboard DOWN */
		        case SDL_KEYDOWN:

					if(e.key.keysym.sym == SDLK_h) {
						help = 1;
					}

					if(e.key.keysym.sym == SDLK_a) {
						constructStatus = 1;
						towerConstruct = LASER;
					}

					if(e.key.keysym.sym == SDLK_z) {
						constructStatus = 1;
						towerConstruct = ROCKET;
					}

					if(e.key.keysym.sym == SDLK_e) {
						constructStatus = 1;
						towerConstruct = ELECTRIC;
					}

					if(e.key.keysym.sym == SDLK_r) {
						constructStatus = 1;
						towerConstruct = WATER;
					}

		            break;

		        /* Keyboard UP */
		        case SDL_KEYUP:

					if(e.key.keysym.sym == SDLK_h) {
						help = -1;
					}

					if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_e || e.key.keysym.sym == SDLK_r) {
						constructStatus = -1;
						towerConstruct = -1;
					}

					break;


		        case SDL_MOUSEMOTION:
		            mouse_x = e.button.x * WINDOW_WIDTH / surface->w;
		            mouse_y = e.button.y * WINDOW_HEIGHT / surface->h;

		            break;

		        case SDL_MOUSEBUTTONUP:

		        	//If the player is holding a 'construct key'
		        	if(constructStatus == 1) {
		        		//if it is a 'tower key'
		        		if(towerConstruct != -1) {
		        			addTower(towerList, towerConstruct, mouse_x, mouse_y);
						}
		        		//else if it is a 'building key'
		        		else if(buildingConstruct != -1) {

		        		}
		        	}

		            break;          
		            
		        default:
		            break;
		    }
        }

        /* Passed time */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* If too few time, the program is paused */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    printTowerList(towerList);

    /* Free Tower List and Free buildings */
    freeTowerList(towerList);

    /*Free global shortest path*/
    free()

    /* Free wave */
    free(wave->monster->path);
    free(wave->monster);
    free(wave);

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

//Main pour tests
int main(int argc, char** argv){
  return 0;
}

#endif