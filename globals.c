/*********************************
*
*       VARIABLES GLOBALES
*
**********************************/

#include "globals.h"
#include <SDL.h>
#include "piece.h"

// Les images de chaque cases des pièces sont en globales
SDL_Surface *screen, *image_bombe, *image_blue, *image_orange, *image_green, *image_vide, *image_grille, *image_pink, *image_red;



Piece* tab_piece_dispo;

Piece* tab_piece_all;

int gameover = 0;

int finjeu = 0;

int nb_piece = 0;

int nb_max_input = 0;

int nb_max_input_raw = 0;

int gameover_menu = 0;

int fenetre_menu = 0;

int delai_piece;

int score;

int affichescore = 0;

int pressagain = 0;

/* Allocation dynamique d'un tableau de piece de taille 'taille' */
Piece* creation_tab_piece(int taille)
{
    Piece* memoire = NULL;
    memoire = malloc(sizeof(Piece)*(taille+1));
    if (memoire == NULL)
    {
        exit(0);
    }
    return memoire;
}

int* creation_tab_int(int taille)
{
    int* memoire = NULL;
    memoire = malloc(sizeof(int)*taille);
    if (memoire == NULL)
    {
        exit(0);
    }
    return memoire;
}



