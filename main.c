#include <SDL.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "carre.h"
#include "piece.h"
#include "globals.h"
#include "event.h"
#include "chargement.h"

extern SDL_Surface *screen;
extern int gameover;
extern Piece tab_piece[NB_PIECE_MAX];
extern int nb_piece;



int main(int argc, char *argv[]){
    /* Initialisation de SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("PentoTrice", "PentoTrice");
    SDL_EnableKeyRepeat(10, 100);

    screen = SDL_SetVideoMode(screen_length, screen_height, 0, 0);
    SDL_Surface *background, *temp;

    temp = SDL_LoadBMP("Sprites/bg.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);


    char key[SDLK_LAST] = {0};



    int mouse_x, mouse_y;
    mouse_x = 0;
    mouse_y = 0;
    int i, j, k;

    // Creation de la fenetre / grille de jeu
    Carre** plateau = alloc_grille(PLATEAU_X, PLATEAU_Y);

    for (i = 0; i < PLATEAU_X; i++){
        for (j = 0; j < PLATEAU_Y; j++){
            const_Carre(&plateau[i][j], 0, 0);
        }
    }

    // test piece
    while (nb_piece < NB_PIECE_MAX){
        tab_piece[nb_piece] = const_Piece(4, 2, 200+70*nb_piece, 200);
    }

    for (i = 0; i < nb_piece; i++){
        printf("%d | %d \n", tab_piece[i].dimx, tab_piece[i].dimy);
    }

    load();
    /******* Boucle de jeu ******/
    while (!gameover){

        SDL_GetMouseState(&mouse_x, &mouse_y);

        update_events(key, mouse_x, mouse_y);

        // Background
        SDL_BlitSurface(background, NULL, screen, NULL);


        // Grille de jeu
        for (i = 0; i < PLATEAU_X; i++){
            for (j = 0; j < PLATEAU_Y; j++){
                SDL_SetColorKey(plateau[i][j].image, SDL_SRCCOLORKEY | SDL_RLEACCEL, plateau[i][j].colorkey);
                //printf("I = %d | J = %d \n", i,j);
                SDL_Rect PI;
                PI.x = 20 + i*32;
                PI.y = 20 + j*32;
                SDL_BlitSurface((plateau[i][j].image), NULL, screen, &PI);
            }
        }

        /****** Blit des surfaces ******/
        for (k = 0; k < nb_piece; k++){
            for (i = 0; i < tab_piece[k].dimx; i++){
                for (j = 0; j < tab_piece[k].dimy; j++){
                    SDL_SetColorKey(tab_piece[k].grille[i][j].image, SDL_SRCCOLORKEY | SDL_RLEACCEL, tab_piece[k].grille[i][j].colorkey);
                    SDL_Rect PI;
                    if (tab_piece[k].actif == 1){
                        PI.x = i*32+mouse_x;
                        PI.y = j*32+mouse_y;
                        if (i==0 && j==0){
                            tab_piece[k].pos=PI;
                            tab_piece[k].bd.x = tab_piece[k].pos.x+32*tab_piece[k].dimx;
                            tab_piece[k].bd.y = tab_piece[k].pos.y+32*tab_piece[k].dimy;

                        }
                    }else{
                        PI.x = i*32+tab_piece[k].pos.x;
                        PI.y = j*32+tab_piece[k].pos.y;
                    }
                    SDL_BlitSurface((tab_piece[k].grille[i][j].image), NULL, screen, &PI);
                }
            }
        }



        SDL_UpdateRect(screen, 0, 0, 0, 0);

    } // Fin whhile gamover


    // Desallocation
    SDL_FreeSurface(background);
    //desalloc_grille(fenetre,10);
    SDL_Quit();
    return 0;
}
