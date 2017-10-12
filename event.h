#ifndef EVENT_H
#define EVENT_H

#include "globals.h"
#include "carre.h"


extern void deposer_piece(int id, Carre **g, int posx, int posy);

extern void update_events(char *keys, int x, int y, Carre **plateau);

extern void grille_LC(Carre **g, int larg, int haut);

extern void eventact_menu(char *keys, int x, int y, SDL_Surface **background);


#endif /* EVENT_H */
