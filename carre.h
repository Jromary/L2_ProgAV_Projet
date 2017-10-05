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

extern void free_Carre(Carre * c);

extern Carre copie_carre(Carre reff);

extern void const_Carre(Carre *c, int couleur, int actif);
#endif /* CARRE_H */
