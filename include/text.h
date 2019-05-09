#ifndef TEXT_H__
#define TEXT_H__

#define MAX_TEXTS 50 //Max number of texts


void loadText(const char* text, const char* fontName, SDL_Color color, int size, SDL_Surface** sFont, GLuint* texture);
void renderText(SDL_Surface** sFont, GLuint* texture, int x , int y);


#endif