/*********************************
*
*         STRUCTURE CARRE
*
**********************************/

#include <SDL.h>

#include "carre.h"
#include "globals.h"

extern SDL_Surface *screen, *image_frites, *image_hotdog, *image_cannette, *image_vide, *image_grille;



/* Constructeur */
void const_Carre(Carre *c, int couleur, int act){
    SDL_Surface *temp, *carreI;
    (*c).actif = act;
    (*c).couleur = couleur;
    switch (couleur)
    {
        case 1:
            temp = image_frites;
            break;
        case 2:
            temp = image_cannette;
            break;
        case 3:
            temp = image_hotdog;
            break;
        case 10:
            temp = image_vide;
            break;
        case 0:
            temp = image_grille;
            break;
        default:
            temp = image_grille;
            break;
    }
    carreI = SDL_DisplayFormat(temp);
    (*c).image = carreI;
    //SDL_FreeSurface(temp);
    (*c).colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
}

/* Constructeur de copie */
Carre copie_carre(Carre reff)
{
    Carre nouveau_carre;
    const_Carre(&nouveau_carre, reff.couleur, reff.actif);
    return nouveau_carre;
}

/* Destructeur */
void free_Carre(Carre * c)
{
    SDL_FreeSurface((*c).image);
}
