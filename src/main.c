#include <SDL/SDL.h>
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
    Image imgPPM;
    ItdColorInstruction itdInstructions[NUMBER_INSTRUCT] = {0};
    Node nodesArray[MAX_NODES] = {0};
    int nbOfNodes;
    //here
    //Node shortestPathArray[MAX_NODES] = shortestPath(nodesArray);

    readITD("data/Map_01.itd", &imgPPM, itdInstructions, nodesArray, &nbOfNodes);

    for(int i = 0; i < nbOfNodes; i++) {
        printNodeInfo(nodesArray[i]);
    }

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    Node NodeA = nodesArray[1];
    Node* NodeB = malloc(sizeof(Node*));
    NodeB = getFirstNextNode(NodeA);
    printf("Next node : %d \n",NodeB->value);

    Node* NodeC = malloc(sizeof(Node*));
    NodeC = getNextNode(NodeA);
    printf("Next node : %d \n", NodeC->value);
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    /* Chargement des images et initialisations des textures */
    SDL_Surface* sprite_img[MAX_SPRITES];
    GLuint sprite_text[MAX_SPRITES];

    for(int i =  0; i < MAX_SPRITES; i++) {
        sprite_img[i] = NULL;
    }

        //Texture 0 : Constructible area
        loadSpriteArea(&sprite_img[0], "construct_area_RGBA_TEST.png");
        initSpriteTexture(&sprite_img[0], &sprite_text[0]);

        //Texture 1 : Path area
        loadSpriteArea(&sprite_img[1], "path_area_RGBA_TEST.png");
        initSpriteTexture(&sprite_img[1], &sprite_text[1]);

        //Texture 2 : Available area
        loadSpriteArea(&sprite_img[2], "available_area_RGBA.png");
        initSpriteTexture(&sprite_img[2], &sprite_text[2]);

        //Texture 3 : Non available area
        loadSpriteArea(&sprite_img[3], "nonAvailable_area_RGBA.png");
        initSpriteTexture(&sprite_img[3], &sprite_text[3]);
  
  
    /* Variables globales */
    int mouse_x = 0, mouse_y = 0;
    int center_mouse_x = 0, center_mouse_y = 0;


    /* Variables globales de listes d'affichage */
        //GLuint debug_draw = debugDrawIDList(&imgPPM);
    GLuint debug_draw = createMapIDList(&imgPPM, itdInstructions, sprite_text);
        //GLuint debug_draw = debugDrawNodesIDList(nodesArray, &nbOfNodes);

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glCallList(debug_draw);

        //available area test
        nonAvailableArea(center_mouse_x, center_mouse_y, sprite_text);


        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
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
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    break;

                case SDL_MOUSEMOTION:
                    mouse_x = e.button.x * WINDOW_WIDTH / surface->w;
                    mouse_y = e.button.y * WINDOW_HEIGHT / surface->h;
                    center_mouse_x =  windowCoordToBlocCenter(mouse_x);
                    center_mouse_y =  windowCoordToBlocCenter(mouse_y);

                    printf("clic en : window(%d, %d)\n", mouse_x, mouse_y);
                    break;
                    
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Free les images */
    for(int i = 0; i < MAX_SPRITES; i++) {
        SDL_FreeSurface(sprite_img[i]);
    }
    
    /* Free l'espace des textures */
    for(int i = 0; i < MAX_SPRITES; i++) {
        glDeleteTextures(1, &sprite_text[i]);
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();

    //Faut free les linkkkksss et l'image
    for(int i = 0; i < nbOfNodes; i++) {
        freeAllLinks(nodesArray[i].link);
    }
    freeImage(&imgPPM);
    
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

void TestMonsters2(){
    Monster *m = createMonster(m, GIANT, 1);
    Monster *m2 = createMonster(m2, SWARMLING, 2);
    
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