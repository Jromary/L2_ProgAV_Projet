#include "globals.h"
#include "piece.h"
#include <SDL.h>


extern int gameover;
extern Piece *tab_piece[NB_PIECE];

void update_events(char *keys, int x, int y)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
        case SDL_MOUSEBUTTONDOWN:
            /*tester sur quel piece on est et la faire follow*/

            for (int i = 0; i < NB_PIECE; i++){
                if ((x >= tab_piece[i]->pos.x) && (x <= tab_piece[i]->bd.x) && (y >= tab_piece[i]->pos.y) && (y <= tab_piece[i]->bd.y)){
                    if (tab_piece[i]->actif == 1){
                        tab_piece[i]->actif = 0;
                    }else{
                        tab_piece[i]->actif = 1;
                    }
                    break;
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
