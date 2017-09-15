#ifndef PIECE_H
#define PIECE_H

#include <SDL.h>
#include "grille.h"

struct s_piece 
{
	SDL_Rect pos;
	SDL_Rect bd;
	Carre** grille;
};
typedef struct s_piece Piece;

extern void const_Piece(Piece* p, int taille, int x, int y);


#endif /* PIECE_H */