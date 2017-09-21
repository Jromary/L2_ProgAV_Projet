#ifndef PIECE_H
#define PIECE_H

#include <SDL.h>
#include "grille.h"

struct s_piece
{
    int actif;
    int dimx;
    int dimy;
	SDL_Rect pos;
	SDL_Rect bd;
	Carre** grille;
};
typedef struct s_piece Piece;

extern Piece const_Piece(int taillex, int tailley, int x, int y);


#endif /* PIECE_H */
