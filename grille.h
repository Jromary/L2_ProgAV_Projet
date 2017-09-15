#ifndef GRILLE_H
#define GRILLE_H

#include <SDL.h>
#include "carre.h"

extern Carre** aloc_one(int taille);
extern Carre* aloc_two(int taille);
extern void desalloc_grille(Carre** tab, int taille);


#endif /* GRILLE_H */
