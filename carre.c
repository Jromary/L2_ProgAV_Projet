#include <SDL.h>

#include "carre.h"
#include "globals.h"

extern SDL_Surface *screen;



/* Constructeur */
void const_Carre(Carre *c, int couleur, int act){
    SDL_Surface *temp, *carreI;
    (*c).actif = act;
    (*c).couleur = couleur;
    switch (couleur){
    case 1:
        temp = SDL_LoadBMP("Sprites/frites.bmp");
        break;
    case 2:
        temp = SDL_LoadBMP("Sprites/canette.bmp");
        break;
    case 3:
        temp = SDL_LoadBMP("Sprites/hotdog.bmp");
        break;
    case 0:
        temp = SDL_LoadBMP("Sprites/Transparent.bmp");
        break;
    default:
        temp = SDL_LoadBMP("Sprites/D_Grille.bmp");
        break;
    }

    carreI = SDL_DisplayFormat(temp);
    (*c).image = carreI;
    SDL_FreeSurface(temp);
    (*c).colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
}


Carre copie_carre(Carre reff){
    Carre nouveau_carre;
    const_Carre(&nouveau_carre, reff.couleur, reff.actif);
    return nouveau_carre;
}


void free_Carre(Carre * c){
    //SDL_FreeSurface((*c).image);
}
