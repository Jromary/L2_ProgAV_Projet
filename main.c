#include <SDL.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "carre.h"
#include "piece.h"

int pick = 0;
int gameover = 0;
int screen_length = 720;
int screen_height = 480;

void update_events(char *keys)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
        case SDL_MOUSEBUTTONDOWN:
            if (pick == 1){
                pick = 0;
                break;
            }
            pick = 1;
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

int main(int argc, char *argv[]){
    /* Initialisation de SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("PentoTrice", "PentoTrice");
    SDL_EnableKeyRepeat(10, 100);

    SDL_Surface *screen;
    screen = SDL_SetVideoMode(screen_length, screen_height, 0, 0);
    SDL_Surface *background, *temp;

    temp = SDL_LoadBMP("bg.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    char key[SDLK_LAST] = {0};
    int x, y;
    int i, j;

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
    Piece p;
    const_Piece(&p, 5, 480, 200);

    /******* Boucle de jeu ******/
    while (!gameover){
        SDL_GetMouseState(&x, &y);
        printf("%d | %d | %d \n", x, y, pick);
        update_events(key);


        /****** Blit des surfaces ******/

        // Background
        SDL_BlitSurface(background, NULL, screen, NULL);

       // Grille de jeu
       for (i = 0; i < 10; i++){
            for (j = 0; j < 10; j++){
                SDL_Rect PI;
                PI.x = i*32;
                PI.y = j*32;
                SDL_BlitSurface((fenetre[i][j].image), NULL, screen, &PI);
            }
        }

        // Piece(s)
        for (i = 0; i < 5; i++){
            for (j = 0; j < 5; j++){
            	SDL_Rect PI;
            	if (1==pick){
            		PI.x = i*32+x;
            		PI.y = j*32+y;
            		if (i==0 && j==0){
            			p.pos=PI;
            		}
            	}else{
            		PI.x = i*32+p.pos.x;
            		PI.y = j*32+p.pos.y;
            	}
                SDL_BlitSurface((p.grille[i][j].image), NULL, screen, &PI);
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
