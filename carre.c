#include <SDL.h>

#include "carre.h"
#include "globals.h"

extern SDL_Surface *screen;



/* Constructeur */
void const_Carre(Carre *c, int couleur, int actif){
    SDL_Surface *temp, *carreI;
    (*c).actif = actif;
    (*c).couleur = couleur;
    if(couleur==1)
    {
    	temp = SDL_LoadBMP("Sprites/frites.bmp");
    }
    else
    {
   		temp = SDL_LoadBMP("Sprites/D_Grille.bmp");
    }
    carreI = SDL_DisplayFormat(temp);
    (*c).image = carreI;
    SDL_FreeSurface(temp);
    (*c).colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
}
