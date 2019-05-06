#ifndef CONST_H__
#define CONST_H__


/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 20.;
static const float GL_VIEW_HEIGHT = 13.;

/* Taille d'un bloc */
static const float GL_SPRITE_SIZE = 61.;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1220; //GL_VIEW_WIDTH * GL_SPRITE
static const unsigned int WINDOW_HEIGHT = 793; //GL_VIEW_HEIGHT * GL_SPRITE
static const char WINDOW_TITLE[] = "Test_Draw";

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const unsigned int MAX_FILENAME =  70;


#endif