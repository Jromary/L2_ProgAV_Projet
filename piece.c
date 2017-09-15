#include <SDL.h>

#include "piece.h"
#include "grille.h"
#include "carre.h"


void const_Piece(Piece* p, int taille, int x, int y)
{
	(*p).pos.x = x;
	(*p).pos.y = y;
	(*p).bd.x = 32 * taille + x;
	(*p).bd.y = 32 * taille + y;
	(*p).grille = aloc_one(taille);

	for(int i = 0; i<taille; i++)
	{
		(*p).grille[i] = aloc_two(taille);
	}

	for (int i = 0; i < taille; i++){
        for (int j = 0; j < taille; j++){
            const_Carre(&p->grille[i][j], 1); // COuleur a mettre à 0 par defaut.
        }
    }
}