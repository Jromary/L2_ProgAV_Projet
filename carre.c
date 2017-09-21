#include <SDL.h>

#include "carre.h"


/* Constructeur */
void const_Carre(Carre *c, int couleur){
    SDL_Surface *temp, *carreI;
    (*c).actif = 0;
    (*c).couleur = couleur;
    if(couleur==1)
    {
    	temp = SDL_LoadBMP("cube1.bmp");
    }
    else
    {
   		temp = SDL_LoadBMP("C_default.bmp");
    }
    carreI = SDL_DisplayFormat(temp);
    (*c).image = carreI;
    SDL_FreeSurface(temp);
    (*c).colorkey = 0;
}
