#include "globals.h"
#include <SDL.h>
#include "piece.h"

SDL_Surface *screen;

Piece* tab_piece[NB_PIECE_MAX];

int tab_piece_all_raw[MAX_INPUT_RAW];


Piece tab_piece_all[MAX_INPUT];

int gameover = 0;

int nb_piece = 0;

int nb_max_input = 0;

int nb_max_input_raw = 0;
