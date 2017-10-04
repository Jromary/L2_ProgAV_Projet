#ifndef GRILLE_H
#define GRILLE_H

#include <SDL.h>
#include "carre.h"

extern Carre** alloc_grille(int taille_x, int taille_y);

//extern Carre** aloc_one(int taille);
//extern Carre* aloc_two(int taille);
extern void free_grille(Carre** tab, int tailley, int taillex);


#endif /* GRILLE_H */
