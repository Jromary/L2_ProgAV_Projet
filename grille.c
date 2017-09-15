#include <SDL.h>
#include <unistd.h>
#include <stdlib.h>

#include "carre.h"
#include "grille.h"




/****
Comme tableaux carrés, pourquoi pas utilise Carre tab[N][M] ?
=> manipulation de tableau en alloc automatic (?)
=> si oui => free automatiquement 

****/

Carre** aloc_one(int taille)
{
    Carre** tab = (Carre **)malloc(taille * sizeof(Carre*));
    if (tab == NULL) // Notification d'erreur
    {
    	exit(EXIT_FAILURE);
    }
    return tab;
}

Carre* aloc_two(int taille)
{
    Carre* tab = (Carre *)malloc(taille * sizeof(Carre));
    if (tab == NULL) // Notification d'erreur
    {
    	exit(EXIT_FAILURE);
    }
    return tab;
}


/* Fonction qui désalloue la mémoire d'une grille de carré. */
void desalloc_grille(Carre** tab, int taille)
{
	for(int i = 0; i< taille; i++)
	{	
		free(tab[i]);
	}
	free(tab);
	tab = NULL;
	return;
}