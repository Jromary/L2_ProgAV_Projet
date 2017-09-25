#include <SDL.h>

#include "piece.h"
#include "grille.h"
#include "carre.h"
#include "globals.h"

extern Piece tab_piece[NB_PIECE_MAX];
extern int nb_piece;

Piece const_Piece(int taillex, int tailley, int x, int y)
{
    Piece nouvelle_piece;
	nouvelle_piece.pos.x = x;
	nouvelle_piece.pos.y = y;
	nouvelle_piece.bd.x = 32 * taillex + x;
	nouvelle_piece.bd.y = 32 * tailley + y;
	nouvelle_piece.grille = alloc_grille(taillex,tailley);
	nouvelle_piece.actif = 0;
	nouvelle_piece.dimx = taillex;
	nouvelle_piece.dimy = tailley;
    printf("TAILLE X = %d\n",nouvelle_piece.dimx);


	for (int i = 0; i < taillex; i++){
        for (int j = 0; j < tailley; j++){
            const_Carre(&(nouvelle_piece.grille[i][j]), 1, 1); // COuleur a mettre à 0 par defaut.
        }
    }
    nb_piece++;

    return nouvelle_piece;
}

