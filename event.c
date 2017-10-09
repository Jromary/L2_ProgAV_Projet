#include <math.h>
#include <SDL.h>

#include "globals.h"
#include "piece.h"
#include "carre.h"
#include "event.h"



extern int gameover;
extern Piece tab_piece[NB_PIECE_MAX];
extern int nb_piece;
extern Piece tab_piece_all[MAX_INPUT];
extern int nb_max_input;

void update_events(char *keys, int x, int y, Carre **plateau)
{
    int test = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
        case SDL_MOUSEBUTTONDOWN:
            /*tester sur quel piece on est et la faire follow*/
            for (int i = 0; i < nb_piece; i++)
            {
                if(tab_piece[i].actif == 1){
                    test=1;
                }

            }
            for (int i = 0; i < nb_piece; i++){
                if ((x >= tab_piece[i].pos.x) && (x <= tab_piece[i].bd.x) && (y >= tab_piece[i].pos.y) && (y <= tab_piece[i].bd.y)){
                    if (tab_piece[i].actif == 1){
                        tab_piece[i].actif = 0;
                        deposer_piece(i, plateau, x, y);
                    }else if(test == 0){
                        tab_piece[i].actif = 1;
                        break;
                    }
                }
            }
            break;
		case SDL_QUIT:
			gameover = 1;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				gameover = 1;
				break;
			default:
				break;
			}
			keys[event.key.keysym.sym] = 1;
			break;
		default:
			break;
		}
	}
}





void deposer_piece(int id, Carre **g, int posx, int posy){
    int posable = 1;
    int x, y;
    int i, j;
    x = (int)(floor(posx/32));
    y = (int)(floor(posy/32));

    /* test si la piece peut etre placer */
    for (i = 0; i < tab_piece[id].dimx; i++){
        for (j = 0; j < tab_piece[id].dimy; j++){

            if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0){
                if (g[x+i-1][y+j-1].actif == 1 && tab_piece[id].grille[i][j].actif == 1){
                    posable = 0;
                }
            }
            else{
                posable = 0;
            }
        }
    }

    /*Si la piece peut etre placer*/
    if (posable == 1){
        for (i = 0; i < tab_piece[id].dimx; i++){
            for (j = 0; j < tab_piece[id].dimy; j++){
                if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0){
                    if (tab_piece[id].grille[i][j].actif != 0){
                        g[x+i-1][y+j-1] = copie_carre(tab_piece[id].grille[i][j]);
                    }
                }
            }
        }
        tab_piece[id] = copie_Piece(tab_piece_all[rand() % nb_max_input]);
        grille_LC(g, PLATEAU_X, PLATEAU_Y);
    }

}


void grille_LC(Carre **g, int larg, int haut){
    int tab_a_changer[larg+haut];
    int i, j;
    int test = 1;
    /*Only god know how it work*/
    for (i = 0; i < haut; i++){
        test = 1;
        for (j = 0; j < larg; j++){
            if (g[j][i].actif == 0){
                test = 0;
            }
        }
        tab_a_changer[i] = test;
    }
    for (j = 0; j < larg; j++){
        test = 1;
        for (i = 0; i < haut; i++){
            if (g[j][i].actif == 0){
                test = 0;
            }
        }
        tab_a_changer[haut+j] = test;
    }
    for (i = 0; i < haut; i++){
        if (tab_a_changer[i] == 1){
            for (j = 0; j < larg; j++){
                const_Carre(&g[j][i], 999, 0);
            }
        }
    }
    for (j = 0; j < larg; j++){
        if (tab_a_changer[haut+j] == 1){
            for (i = 0; i < haut; i++){
                const_Carre(&g[j][i], 999, 0);
            }
        }
    }
}





