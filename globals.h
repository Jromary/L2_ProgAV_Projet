/*********************************
*
*       VARIABLES GLOBALES
*            en-tête
**********************************/

#ifndef GLOBALES_H
#define GLOBALES_H
#include "piece.h"

/* Taille de la fenetre */
#define screen_height 480
#define screen_length 720

/* Nombre de pieces propose */
#define NB_PIECE_MAX 3
#define MAX_INPUT 5000
#define MAX_INPUT_RAW 10000

/* Taille de la grille de jeu */
#define PLATEAU_X 10
#define PLATEAU_Y 10

/* Timer */
#define DELAI_MAX_PIECE 5

/* Allocation dynamique d'un tableau de piece de taille taille */
extern Piece* creation_tab_piece(int taille);


#endif /* GLOBALES_H */
