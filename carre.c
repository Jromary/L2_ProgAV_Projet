#include <SDL.h>

#include "carre.h"

void const_Carre(Carre *c){
    SDL_Surface *temp, *carreI;
    (*c).actif = 0;
    (*c).couleur = 0;
    temp = SDL_LoadBMP("C_default.bmp");
    carreI = SDL_DisplayFormat(temp);
    (*c).image = carreI;
    SDL_FreeSurface(temp);
    (*c).colorkey = 0;
}
