/*********************************
*
*       GESTION DE LA GRILLE
*            en-tête
**********************************/

#ifndef GRILLE_H
#define GRILLE_H

#include <SDL.h>
#include "carre.h"

/* Allocation dynamique d'un tableau de Carre de dimension */
extern Carre** alloc_grille(int taille_x, int taille_y);

/* Fonction qui désalloue la mémoire d'une grille de carré. */
extern void free_grille(Carre** tab, int tailley, int taillex);

#endif /* GRILLE_H */
