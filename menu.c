/*********************************
*
*       GESTION DU MENU
*
**********************************/
#include <SDL.h>
#include "globals.h"
#include "menu.h"
#include "event.h"

extern SDL_Surface *screen;
extern int gameover_menu;
extern int affichescore;


/* Boucle du menu */
void accueil(int argc, char *argv[])
{
	SDL_WM_SetCaption("PentoTrice", "PentoTrice");
	SDL_EnableKeyRepeat(10, 100);

	screen = SDL_SetVideoMode(screen_length, screen_height, 0, 0);
	SDL_Surface *background, *temp;

	temp = SDL_LoadBMP("Sprites/accueil_bg.bmp");
	background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	int mouse_x, mouse_y;
	char key[SDLK_LAST] = {0};

	while (!gameover_menu)
	{
		SDL_GetMouseState(&mouse_x, &mouse_y);
		eventact_menu(key, mouse_x, mouse_y, &background);
		SDL_BlitSurface(background, NULL, screen, NULL);
        if (affichescore){
            printscore();
        }

	    SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
	SDL_FreeSurface(background);
	gameover_menu = 0;

}
