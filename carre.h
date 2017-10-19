/*********************************
*
*         STRUCTURE CARRE
*             en-tête
**********************************/

#ifndef CARRE_H
#define CARRE_H

#include <SDL.h>

struct Carre{
    int actif;
    int couleur;
    SDL_Surface *image;
    int colorkey;
};
typedef struct Carre Carre;

/* Constructeur */
extern void const_Carre(Carre *c, int couleur, int actif);

/* Constructeur de copie */
extern Carre copie_carre(Carre reff);

/* Destructeur */
extern void free_Carre(Carre * c);


#endif /* CARRE_H */
