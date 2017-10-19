/*********************************
*
*         STRUCTURE PIECES
*              en-tête
**********************************/

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

/* Constructeur */
extern Piece const_Piece(int taillex, int tailley, int x, int y);

/* Constructeur de copie */
extern Piece copie_Piece(Piece piece_ref);

/* Destructeur */
extern void free_piece(Piece *p);

#endif /* PIECE_H */
