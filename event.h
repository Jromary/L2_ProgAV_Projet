/*********************************
*
*       GESTION DES EVENEMENTS
*            en-tête
**********************************/

#ifndef EVENT_H
#define EVENT_H

#include "globals.h"
#include "carre.h"

/* Fonction principale de gestion d'évenements */
extern void update_events(char *keys, int x, int y, Carre **plateau);

/* Fonction de gestion du depot de piece sur la grille */
extern void deposer_piece(int id, Carre **g, int posx, int posy);

/* Gestion des lignes entières et des colonnes entières */
extern void grille_LC(Carre **g, int larg, int haut);

/* Gestion du menu */
extern void eventact_menu(char *keys, int x, int y, SDL_Surface **background);

/* Tri des scores stockés dans scores.txt */
extern void trie_score();

/* Tri des scores stockés dans scores.txt */
extern void trie_score_aux(int *tab, int n);

/* Affiche les scores */
extern void printscore();

/* affiche un nombre */
extern void affiche_nombre(int x, int y, int nb);

#endif /* EVENT_H */
