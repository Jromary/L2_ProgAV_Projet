/*********************************
*
* PENTOTRICE
* Projet L2 Info Prog.av
* Julien ROMARY - Emmanuel PERRIN
*
**********************************/


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
#include "menu.h"


/* Import des variables globales */
extern SDL_Surface *screen;

extern int nb_piece;
extern Piece* tab_piece_all;
extern Piece* tab_piece_dispo;
extern int nb_max_input;
extern int nb_max_input_raw;

extern int finjeu;
extern int delai_piece;
extern int score;
extern int gameover;

int main(int argc, char *argv[]){

    /* Initialisation de SDL et du module Time */
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));

    /* Debut de la boucle du programme */
	while (!finjeu){
        /* Paramétrage de la fenetre  et des inputs */
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

        /* Lancement de la boucle de menu */
		accueil(argc, argv);
        /* Fin de la boucle menu, suite du programme */
        if(!gameover)
        {
            /* Chargement des pièces du fichier d'entrées */
            load();
            // Creation du tableau de piece disponible et du tableau de pieces global
            tab_piece_dispo = creation_tab_piece(NB_PIECE_MAX);

            nb_piece = 0;
            while (nb_piece < NB_PIECE_MAX)
            {
                tab_piece_dispo[nb_piece] = copie_Piece(tab_piece_all[rand() % nb_max_input]);
                nb_piece++;
            }
        }

		/* Creation de la grille de jeu */
		Carre** plateau = alloc_grille(PLATEAU_X, PLATEAU_Y);
		for (i = 0; i < PLATEAU_X; i++)
        {
			for (j = 0; j < PLATEAU_Y; j++)
            {
				const_Carre(&plateau[i][j], 0, 0);
			}
		}

        /* Initialisation des variables necessaires au jeu */
		delai_piece = time(0);
		int comp_delai_piece;
		score = 0;

		/* Boucle de jeu */
		while (!gameover)
        {

            /* Recuperation des évenements */
			SDL_GetMouseState(&mouse_x, &mouse_y);
			update_events(key, mouse_x, mouse_y, plateau);

			/* Timer des pieces, pouvant entrainer le gameover */
			comp_delai_piece = time(0);
			if (comp_delai_piece- delai_piece >= DELAI_MAX_PIECE)
			{
				gameover = 1;
			}

			/* Blit des surfaces */

			/* Background */
			SDL_BlitSurface(background, NULL, screen, NULL);

            /* Grille de jeu */
			for (i = 0; i < PLATEAU_X; i++)
            {
				for (j = 0; j < PLATEAU_Y; j++)
				{
					SDL_SetColorKey(plateau[i][j].image, SDL_SRCCOLORKEY | SDL_RLEACCEL, plateau[i][j].colorkey);
					SDL_Rect PI;
					PI.x = 32 + i*32;
					PI.y = 32 + j*32;
					SDL_BlitSurface((plateau[i][j].image), NULL, screen, &PI);
				}
			}

            /* Pieces disponibles */
			for (k = 0; k < nb_piece; k++)
            {
				tab_piece_dispo[k].pos.x = 500;
				tab_piece_dispo[k].pos.y = k * screen_height/nb_piece; // Adaptation en hauteur en fonction du nombre de pieces disponibles
				tab_piece_dispo[k].bd.x = tab_piece_dispo[k].pos.x+32*tab_piece_dispo[k].dimx;
				tab_piece_dispo[k].bd.y = tab_piece_dispo[k].pos.y+32*tab_piece_dispo[k].dimy;
				for (i = 0; i < tab_piece_dispo[k].dimx; i++)
				{
					for (j = 0; j < tab_piece_dispo[k].dimy; j++)
					{
						SDL_SetColorKey(tab_piece_dispo[k].grille[i][j].image, SDL_SRCCOLORKEY | SDL_RLEACCEL, tab_piece_dispo[k].grille[i][j].colorkey);
						SDL_Rect PI;
						if (tab_piece_dispo[k].actif == 1) // Si la piece doit suivre la souris...
						{
							PI.x = i*32+mouse_x-16;
							PI.y = j*32+mouse_y-16;
							if (i==0 && j==0)
							{
								tab_piece_dispo[k].pos=PI;
								tab_piece_dispo[k].bd.x = tab_piece_dispo[k].pos.x+32*tab_piece_dispo[k].dimx;
								tab_piece_dispo[k].bd.y = tab_piece_dispo[k].pos.y+32*tab_piece_dispo[k].dimy;
							}
						}
                        else
                        {
							PI.x = i*32+tab_piece_dispo[k].pos.x;
							PI.y = j*32+tab_piece_dispo[k].pos.y;
						}
						SDL_BlitSurface((tab_piece_dispo[k].grille[i][j].image), NULL, screen, &PI);
					}
				}
			}
			SDL_UpdateRect(screen, 0, 0, 0, 0);

		} // Fin while gamover
        if (gameover && !finjeu)
        {
            SDL_Surface *background, *temp;
            temp = SDL_LoadBMP("Sprites/bg.bmp");
            background = SDL_DisplayFormat(temp);
            SDL_BlitSurface(background, NULL, screen, NULL);
            affiche_nombre(screen_length/2, screen_height/2, score);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
            sleep(2);
        }

		/* Desallocation */
		SDL_FreeSurface(background);
		free_grille(plateau, 10, 10);
		for (i = 0; i < nb_piece; i++)
        {
			free_piece(&tab_piece_dispo[i]);
		}
		for (i = 0; i < nb_max_input; i++)
		{
			free_piece(&tab_piece_all[i]);
		}

		/* Remise à zéro des variables de jeu */
		nb_piece = 0;
		nb_max_input = 0;
		nb_max_input_raw = 0;
		gameover = 0;

        /* Enregistrement des scores */


		if (score != 0)
		{
			FILE *fichier = fopen("scores.txt", "a");
			if (fichier != NULL)
			{
				fprintf(fichier, "%d\n", score);
			}
			fclose(fichier);
		}


	} /* Fin du while finjeu */

	SDL_Quit();
	return 0;
}
