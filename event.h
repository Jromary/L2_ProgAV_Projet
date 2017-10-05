#ifndef EVENT_H
#define EVENT_H

#include "globals.h"
#include "carre.h"


extern void deposer_piece(int id, Carre **g, int posx, int posy);

extern void update_events(char *keys, int x, int y, Carre **plateau);



#endif /* EVENT_H */
