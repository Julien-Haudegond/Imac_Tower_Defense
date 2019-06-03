#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FMOD/fmod.h>

#include "../include/const.h"
#include "../include/game.h"

#include "../include/monster.h"
#include "../include/wave.h"
#include "../include/tower.h"
#include "../include/tower_list.h"
#include "../include/building.h"
#include "../include/building_list.h"

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
#include "../include/explosion.h"


/***************
*   define : 
*   READTHIS 1 for PPM check & map debug + sprites
*   READTHIS 2 for tests on monsters path
*   READTHIS 3 for tests on monsters / towers / and lists
****************/
#define READTHIS1

#ifdef READTHIS1


int playGame(SDL_Surface* surface, const char* itdPath)
{
    int global_money = 10000;

    //Loading ITD File
    Image imgPPM;
    ItdColorInstruction itdInstructions[NUMBER_INSTRUCT] = {0};
    Node nodesArray[MAX_NODES] = {0};
    int nbOfNodes;

    readITD(itdPath, &imgPPM, itdInstructions, nodesArray, &nbOfNodes);


    //Initialize a list of towers and buildings 
    TowerList* towerList = createEmptyTowerList();
    BuildingList* buildingList = createEmptyBuildingList();


    updateAllValarcLinks(nodesArray, nbOfNodes, towerList); 

    //filling nodesPath array
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
    Node* nodesearch = malloc(sizeof(Node));

    //Monster* ptrMonster = malloc(sizeof(Monster));
    Wave* ptrWave = malloc(sizeof(Wave));   
    ExplosionList* explosionList = createEmptyExplosionList();
   

    /* Initializing FMOD */
    FMOD_SYSTEM* system;
    FMOD_SOUND* music;
    FMOD_RESULT result;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

        //Opening the music
        result = FMOD_System_CreateSound(system, "sounds/game.mp3", FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &music);

        //Check if it well opened
        if(result != FMOD_OK) {
            fprintf(stderr, "Error: impossible to read the music file\n");
            exit(EXIT_FAILURE);
        }

        //Loop the music
        FMOD_Sound_SetLoopCount(music, -1);

        //Play the music
        FMOD_System_PlaySound(system, music, NULL, 0, NULL);

    /* SPRITES: Loading surfaces and initializing textures */
    Sprite sprites[MAX_SPRITES];

    initSpritesToNull(sprites);
    fillSprites(sprites); // GO TO SPRITE.C TO MODIFY

    /* TEXTS */
        //Text styles
        TextStyle textCSS[MAX_CSS];

        initTextCSSToNull(textCSS);
        initTextCSS(textCSS); // GO TO TEXT.C TO MODIFY

        //Loading TEXTS
        Text generalTexts[MAX_TEXTS]; //General Texts
        Text propTowerTexts[MAX_TEXTS]; //Properties Tower Texts

        initTextsToNull(generalTexts);
        initTextsToNull(propTowerTexts);

        //WRITING General texts
        fillTextsArrays(textCSS, generalTexts); // GO TO TEXT.C TO MODIFY
  

    /* Global variables */
    int mouse_x = 0, mouse_y = 0, button_x = 0, button_y = 0;
    int help = -1; //To print the 'help' popup
    int constructStatus = -1, availableStatus = 0; //To construct something and if it is an available area
    int towerConstructType = -1, buildingConstructType = -1; //For construction types and validate constructions
    int deleteStatus = -1; //For deleting constructions
    int towerPropStatus = -1; //To show the tower properties

    /*Global variables monsters*/
    int pathIndex = 0;
    int getMonsterDirection = 0;
    int monsterRotation = 0;
    
    //variables for waves
    
    int monsterCounter = 0;

    Uint32 currentTimeMonster = 0, previousTimeMonster = 0;
    
   

    /* Global variables for GL Lists */
    GLuint map = createMapIDList(&imgPPM, itdInstructions, sprites);
    GLuint properties_window = createPropertiesWindowList(towerList, mouse_x, mouse_y, textCSS, propTowerTexts);
    
     
            //int mstrCounter = 0;

    /* MAIN LOOP */
    int loop = 1;
    while(loop) 
    {
        /* Time at the beginning of the loop */
        Uint32 startTime = SDL_GetTicks();
        
        /* DRAWING CODE */

            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            //MAP
            glCallList(map);
            
            //Hold a specific key to build towers or buildings
            if(constructStatus != -1) {
                availableStatus = constructionGuides(mouse_x, mouse_y, &imgPPM, itdInstructions, sprites, towerList, buildingList);
                if(towerConstructType != -1 && availableStatus == 1) drawTowerGuides(mouse_x, mouse_y, towerConstructType, sprites);
                else if(buildingConstructType != -1 && availableStatus == 1) drawBuildingGuides(mouse_x, mouse_y, buildingConstructType, sprites);
            }

            //EXPLOSIONS
            globalDrawExplosions(explosionList, sprites);
            explosionList = deleteExplosion(explosionList); //Update the explosions each frame

            //TOWERS
            globalDrawTowers(towerList, sprites);

            //BUILDINGS
            globalDrawBuildings(buildingList, sprites);
            
            //MONSTERS

            //adding monsters to the wave
            if(monsterCounter < WAVESIZE){
                currentTimeMonster = SDL_GetTicks();
                if(currentTimeMonster - previousTimeMonster >= 1000){
                    addMonster(wave, SWARMLING, 0, nodesPath, nbShortest);
                    ptrWave = getLastMonster(wave);
                    ptrWave->monster->currentNode = ptrWave->monster->path[0];
                    nodesearch = getNodeFromValue(nodesArray, nbOfNodes, ptrWave->monster->currentNode);
                    setPosition(ptrWave->monster, nodesearch->win_x, nodesearch->win_y);
                    
                     previousTimeMonster = currentTimeMonster;
                     monsterCounter++;
                }

            }
            if(wave !=NULL)
                ptrWave = wave;
            while(ptrWave && wave->monster!=NULL && ptrWave->monster !=NULL){    
                
                //Getting current node stats
                nodesearch = getNodeFromValue(nodesArray, nbOfNodes, ptrWave->monster->currentNode);
          
                //clips monster position if it has trespassed the current destination node
                if(nodesearch->value != 0){
                    getMonsterDirection = getDirection(ptrWave->monster, nodesArray, nbOfNodes);
                    monsterRotation = getMonsterRotation(getMonsterDirection);

                    //getMonsterDirection = getDirection(ptrWave->monster, nodesArray, nbOfNodes);
                    clipMonsterPosition(ptrWave->monster, getMonsterDirection, nodesearch);
                }

                if(nodesearch->type == 2 && nodesearch->win_x == ptrWave->monster->win_x && nodesearch->win_y == ptrWave->monster->win_y){
                    //free monster, and give money to the player
                }else{
                    pathIndex = ptrWave->monster->currentIndex;
                    //updates current node if it's been reached
                    if(ptrWave->monster->path[pathIndex+1] && (ptrWave->monster->win_x == nodesearch-> win_x && ptrWave->monster->win_y == nodesearch->win_y)){
                        ptrWave->monster->prevNode = ptrWave->monster->currentNode;
                        ptrWave->monster->currentIndex++;
                        ptrWave->monster->currentNode = ptrWave->monster->path[pathIndex+1];
                        //updating nodesearch if needed
                        nodesearch = getNodeFromValue(nodesArray, nbOfNodes, ptrWave->monster->currentNode);

                    }
                    //updates monster coords if the node has not been reached
                    if((ptrWave->monster->win_x != nodesearch-> win_x || ptrWave->monster->win_y != nodesearch->win_y)){
                        updateCoords(ptrWave->monster,nodesArray,nbOfNodes);
                    }

                    if(ptrWave->monster->health > 0){
                        ptrWave->monster->health -= 0.1;
                        drawMonsterSprite(ptrWave->monster, sprites, monsterRotation);
                        drawHealthBar(ptrWave->monster, sprites);
                    }else{
                        global_money += ptrWave->monster->reward;
                        addExplosion(explosionList, ptrWave->monster->win_x, ptrWave->monster->win_y); //Create an explosion at the position of the death
                        wave = deleteMonster(wave);
                    }  
                }
                ptrWave = ptrWave->nextMonster;
            }

            if(wave->monster == NULL && monsterCounter >= WAVESIZE){
                //Passer a la wave suivante ou gagner le jeu si y'a pas de wave suivante
                printf("GG WP!! \n");
            }

            //Hold 'delete key'
            if(deleteStatus != -1) {
                drawSpriteHere(&(sprites[10].texture), mouse_x, mouse_y);
            }

            //Draw the tower properties
            if(towerPropStatus != -1) {
                properties_window = createPropertiesWindowList(towerList, button_x, button_y, textCSS, propTowerTexts);
                glCallList(properties_window);
            }

            //MONEY
            loadIntegerText(global_money, &textCSS[0], &generalTexts[1]); //Reload each time the money text
            renderRightText(&generalTexts[1], 1170, 30); //Money text
            glPushMatrix();
                glTranslatef(1190, 30, 0);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();

            //HELP
            renderCenterText(&generalTexts[0], 610, 700); //Press 'h' to get some help
            //Hold 'h' to make the menu appear
            if(help == 1) {
                drawFullScreenImg(&(sprites[15].texture));
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
                        towerConstructType = LASER;
                    }

                    if(e.key.keysym.sym == SDLK_z) {
                        constructStatus = 1;
                        towerConstructType = ROCKET;
                    }

                    if(e.key.keysym.sym == SDLK_e) {
                        constructStatus = 1;
                        towerConstructType = ELECTRIC;
                    }

                    if(e.key.keysym.sym == SDLK_r) {
                        constructStatus = 1;
                        towerConstructType = WATER;
                    }

                    if(e.key.keysym.sym == SDLK_q) {
                        constructStatus = 1;
                        buildingConstructType = RADAR;
                    }

                    if(e.key.keysym.sym == SDLK_s) {
                        constructStatus = 1;
                        buildingConstructType = FACTORY;
                    }

                    if(e.key.keysym.sym == SDLK_d) {
                        constructStatus = 1;
                        buildingConstructType = AMMO;
                    }

                    if(e.key.keysym.sym == SDLK_DELETE) {
                        deleteStatus = 1;
                    }

                    break;

                /* Keyboard UP */
                case SDL_KEYUP:

                    if(e.key.keysym.sym == SDLK_h) {
                        help = -1;
                    }

                    if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_e || e.key.keysym.sym == SDLK_r) {
                        constructStatus = -1;
                        towerConstructType = -1;
                    }

                    if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_d) {
                        constructStatus = -1;
                        buildingConstructType = -1;
                    }

                    if(e.key.keysym.sym == SDLK_DELETE) {
                        deleteStatus = -1;
                    }

                    break;


                case SDL_MOUSEMOTION:
                    mouse_x = e.button.x * WINDOW_WIDTH / surface->w;
                    mouse_y = e.button.y * WINDOW_HEIGHT / surface->h;

                    break;


                case SDL_MOUSEBUTTONDOWN:

                    button_x = e.button.x * WINDOW_WIDTH / surface->w;
                    button_y = e.button.y * WINDOW_HEIGHT / surface->h;

                    //If mouse left button is down
                    if(e.button.button == SDL_BUTTON_LEFT) {

                        //If the player is holding a 'construct key' and if the area is available
                        if(constructStatus == 1 && availableStatus == 1) {
                            //if it is a 'tower key'
                            if(towerConstructType != -1) {
                                int price = checkTowerMoney(towerConstructType, global_money);
                                if(price != 0) {
                                    addTower(towerList, towerConstructType, mouse_x, mouse_y);
                                    updateTowersBuildings(towerList, buildingList);
                                    global_money -= price;

                                    //update Dijkstra links
                                    updateAllValarcLinks(nodesArray, nbOfNodes, towerList);
                                    for(int i = 0; i < nbOfNodes; i++) {
                                        initializeDijkstra(&nodesArray[i]);
                                    }
                                    shortestPath(nodesArray, nbOfNodes);
                                    nbShortest = countNodesShortestPath(nodesArray);
                                    nodesPath = malloc(nbShortest*sizeof(int));
                                    fillShortestPath(nodesPath, nbShortest, nodesArray);
                                }
                            }
                            //else if it is a 'building key'
                            else if(buildingConstructType != -1) {
                                int price = checkBuildingMoney(buildingConstructType, global_money);
                                if(price != 0) {
                                    addBuilding(buildingList, buildingConstructType, mouse_x, mouse_y);
                                    updateTowersBuildings(towerList, buildingList);
                                    global_money -= price;

                                    //update Dijkstra links
                                    updateAllValarcLinks(nodesArray, nbOfNodes, towerList);
                                    for(int i = 0; i < nbOfNodes; i++) {
                                        initializeDijkstra(&nodesArray[i]);
                                    }
                                    shortestPath(nodesArray, nbOfNodes);
                                    nbShortest = countNodesShortestPath(nodesArray);
                                    nodesPath = malloc(nbShortest*sizeof(int));
                                    fillShortestPath(nodesPath, nbShortest, nodesArray);                              
                                }
                            }
                        }

                        //If the player is holding the 'delete key'
                        if(deleteStatus == 1) {
                            towerList = deleteTower(towerList, mouse_x, mouse_y, &global_money);
                            buildingList = deleteBuilding(buildingList, mouse_x, mouse_y, &global_money);
                            updateTowersBuildings(towerList, buildingList);

                            //update Dijkstra links
                            updateAllValarcLinks(nodesArray, nbOfNodes, towerList);
                            for(int i = 0; i < nbOfNodes; i++) {
                                initializeDijkstra(&nodesArray[i]);
                            }
                            shortestPath(nodesArray, nbOfNodes);
                            nbShortest = countNodesShortestPath(nodesArray);
                            nodesPath = malloc(nbShortest*sizeof(int));
                            fillShortestPath(nodesPath, nbShortest, nodesArray);
                        }
                    }

                    //If mouse right button is down
                    if(e.button.button == SDL_BUTTON_RIGHT) {

                        //Change the tower properties status
                        if(isThereTowerHere(towerList, button_x, button_y) == 1) {
                            towerPropStatus = 1;
                        }                  
                    }

                    break;


                case SDL_MOUSEBUTTONUP:

                    //If mouse right button is up
                    if(e.button.button == SDL_BUTTON_RIGHT) {

                        //Change the tower properties status
                        if(towerPropStatus != -1) {
                            towerPropStatus = -1;
                        }
                    }   
                    
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

    printWave(wave);
    printTowerList(towerList);
    printBuildingList(buildingList);
    printExplosionList(explosionList);

    /* Free Tower List and Free buildings */
    freeTowerList(towerList);
    freeBuildingList(buildingList);

    /*Free global shortest path*/
    free(nodesPath);

    /* Free wave */
    //free(wave->monster->path);
    //free(wave->monster);
    free(wave);

    freeExplosionList(explosionList);

    /* Free sprites */
    freeSprites(sprites);

    /* Close fonts */
    freeTextCSS(textCSS);

    /* Free texts */
    freeTexts(generalTexts);
    freeTexts(propTowerTexts);

    /* Free links of all nodes and the PPM */
    for(int i = 0; i < nbOfNodes; i++) {
        freeAllLinks(nodesArray[i].link);
    }
    freeImage(&imgPPM);

    /* Free FMOD */
    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    
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