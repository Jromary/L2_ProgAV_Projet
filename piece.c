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

	for (int i = 0; i < taillex; i++){
        for (int j = 0; j < tailley; j++){
            const_Carre(&(nouvelle_piece.grille[i][j]), 999, 0); // COuleur a mettre à 0 par defaut.
        }
    }
    return nouvelle_piece;
}

Piece copie_Piece(Piece piece_ref)
{
    Piece nouvellePiece = const_Piece(piece_ref.dimx, piece_ref.dimy, piece_ref.pos.x, piece_ref.pos.y);

    int i,j;
    for(i=0; i<piece_ref.dimx; i++)
    {
        for(j=0; j<piece_ref.dimy; j++)
        {
           const_Carre(&nouvellePiece.grille[i][j], piece_ref.grille[i][j].couleur, piece_ref.grille[i][j].actif);
        }
    }
    return nouvellePiece;
}
