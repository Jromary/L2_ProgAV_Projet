/*********************************
*
*       VARIABLES GLOBALES
*
**********************************/

#include "globals.h"
#include <SDL.h>
#include "piece.h"

SDL_Surface *screen;

//Piece tab_piece[NB_PIECE_MAX];

int tab_piece_all_raw[MAX_INPUT_RAW];

Piece tab_piece_all[MAX_INPUT];

int gameover = 0;

int finjeu = 0;

int nb_piece = 0;

int nb_max_input = 0;

int nb_max_input_raw = 0;

int gameover_menu = 0;

int fenetre_menu = 0;

int delai_piece;

int score;

/* Allocation dynamique d'un tableau de piece de taille taille */
Piece* creation_tab_piece(int taille)
{
    Piece* memoire = NULL;
    memoire = malloc(sizeof(Piece)*taille);
    if (memoire == NULL)
    {
        exit(0);
    }
    return memoire;
}


// Creation du tableau de piece

//Piece* tab_piece = creation_tab_piece(NB_PIECE_MAX);


