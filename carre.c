#include <SDL.h>

#include "carre.h"
#include "globals.h"

extern SDL_Surface *screen;



/* Constructeur */
void const_Carre(Carre *c, int couleur, int act){
    SDL_Surface *temp, *carreI;
    (*c).actif = act;
    (*c).couleur = couleur;
    if(couleur == 1)
    {
    	temp = SDL_LoadBMP("Sprites/frites.bmp");
    }
    else if (couleur == 0){
        temp = SDL_LoadBMP("Sprites/Transparent.bmp");
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


void free_Carre(Carre * c){
    //SDL_FreeSurface((*c).image);
}
