#include <SDL.h>

#include "piece.h"
#include "grille.h"
#include "carre.h"


void const_Piece(Piece* p, int taillex, int tailley, int x, int y)
{
	(*p).pos.x = x;
	(*p).pos.y = y;
	(*p).bd.x = 32 * taillex + x;
	(*p).bd.y = 32 * tailley + y;
	(*p).grille = aloc_one(taillex);
	(*p).actif = 0;
	(*p).dimx = taillex;
	(*p).dimy = tailley;

	for(int i = 0; i<taillex; i++)
	{
		(*p).grille[i] = aloc_two(tailley);
	}

	for (int i = 0; i < taillex; i++){
        for (int j = 0; j < tailley; j++){
            const_Carre(&p->grille[i][j], 1); // COuleur a mettre à 0 par defaut.
        }
    }
}
