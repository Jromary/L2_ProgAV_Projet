#include <SDL.h>
#include <unistd.h>
#include <stdlib.h>

#include "carre.h"
#include "grille.h"

Carre** alloc_grille(int taille_x, int taille_y)
{
    int i;
    Carre **tab;
    tab = (Carre**)malloc(taille_x * sizeof(Carre*));
    for (i = 0; i < taille_x; i++)
        tab[i] = (Carre*)malloc(taille_y * sizeof(Carre));

    return tab;
}



/* Fonction qui désalloue la mémoire d'une grille de carré. */
void free_grille(Carre** tab, int tailley, int taillex)
{

	for(int i = 0; i< taillex; i++)
	{
	    for (int j = 0; j < tailley; j++){
            free_Carre(&tab[i][j]);
	    }
		free(tab[i]);
	}
	free(tab);
	tab = NULL;

}
