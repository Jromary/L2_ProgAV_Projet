#include <SDL.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "carre.h"
#include "piece.h"
#include "globals.h"
#include "event.h"

extern SDL_Surface *screen;
extern int gameover;
extern Piece *tab_piece[NB_PIECE];



int main(int argc, char *argv[]){
    /* Initialisation de SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("PentoTrice", "PentoTrice");
    SDL_EnableKeyRepeat(10, 100);

    screen = SDL_SetVideoMode(screen_length, screen_height, 0, 0);
    SDL_Surface *background, *temp;

    temp = SDL_LoadBMP("bg.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    char key[SDLK_LAST] = {0};
    int x, y;
    int i, j, k;

    // Creation de la fenetre / grille de jeu
    Carre** fenetre = aloc_one(10);
    for (i = 0; i < 10; i++){
        fenetre[i] = aloc_two(10);
    }

    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            const_Carre(&fenetre[i][j], 0);
        }
    }

    // test piece
    for (i = 0; i < NB_PIECE; i++){
        Piece p;
        const_Piece(&p, 3, 2, 200+64*i, 200);
        tab_piece[i] = &p;
    }


    for (i = 0; i < NB_PIECE; i++){
        printf("%d | %d \n", tab_piece[i]->dimx, tab_piece[i]->dimy);
    }
    /******* Boucle de jeu ******/
    while (!gameover){
        SDL_GetMouseState(&x, &y);
        //printf("%d | %d  \n", x, y);
        update_events(key, x, y);

        /****** Blit des surfaces ******/

        // Background
        SDL_BlitSurface(background, NULL, screen, NULL);

        for (i = 0; i < NB_PIECE; i++){
            printf("%d | %d \n", tab_piece[i]->dimx, tab_piece[i]->dimy);
        }

        printf("AFFICHAGE GRILLE\n");
        // Grille de jeu
        for (i = 0; i < 10; i++){
            for (j = 0; j < 10; j++){
                SDL_Rect PI;
                PI.x = i*32;
                PI.y = j*32;
              //  SDL_BlitSurface((fenetre[i][j].image), NULL, screen, &PI);
            }
        }

        printf("AFFICHAGE PIECES\n");
        // Piece(s)
        for (i = 0; i < NB_PIECE; i++){
            printf("%d | %d \n", tab_piece[i]->dimx, tab_piece[i]->dimy);
        }

        for (k = 0; k < NB_PIECE; k++){
            for (i = 0; i < tab_piece[k]->dimx; i++){
                printf("%d | %d \n", tab_piece[k]->dimx, tab_piece[k]->dimy);

                for (j = 0; j < tab_piece[k]->dimy; j++){
                    SDL_Rect PI;
                    if (tab_piece[k]->actif == 1){
                        PI.x = i*32+x;
                        PI.y = j*32+y;
                        if (i==0 && j==0){
                            tab_piece[k]->pos=PI;
                        }
                    }else{
                        PI.x = i*32+tab_piece[k]->pos.x;
                        PI.y = j*32+tab_piece[k]->pos.y;
                    }
                    printf(" I === %d\n", i);

                    SDL_BlitSurface((tab_piece[k]->grille[i][j].image), NULL, screen, &PI);
                }
            }

        }


        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }


    // Desallocation
    SDL_FreeSurface(background);
    desalloc_grille(fenetre,10);
    SDL_Quit();
    return 0;
}
