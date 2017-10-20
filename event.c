/*********************************
*
*       GESTION DES EVENEMENTS
*
**********************************/

#include <math.h>
#include <time.h>

#include <SDL.h>

#include "globals.h"
#include "piece.h"
#include "carre.h"
#include "event.h"

extern int gameover;
extern int gameover_menu;
extern int finjeu;

extern int fenetre_menu;

extern Piece* tab_piece_dispo;
extern int nb_piece;
extern Piece* tab_piece_all;
extern int nb_max_input;

extern int delai_piece;
extern int score;


/* Fonction principale de gestion d'évenements */
void update_events(char *keys, int x, int y, Carre **plateau)
{
    int test = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		/*
		* Test pour savoir sur quelle piece on se situe si on en aucune en deplacement
		*
		* sinon, essaye de poser la piece dans la grille de jeu
		*/
        case SDL_MOUSEBUTTONDOWN:
            for (int i = 0; i < nb_piece; i++)
            {
                if(tab_piece_dispo[i].actif == 1){
                    test=1;
                }
            }
            for (int i = 0; i < nb_piece; i++)
            {
                if ((x >= tab_piece_dispo[i].pos.x) &&
                    (x <= tab_piece_dispo[i].bd.x) &&
                    (y >= tab_piece_dispo[i].pos.y) &&
                    (y <= tab_piece_dispo[i].bd.y))
                {
                    if (tab_piece_dispo[i].actif == 1)
                    {
                        tab_piece_dispo[i].actif = 0;
                        deposer_piece(i, plateau, x, y);
                    }
                    else if(test == 0)
                    {
                        tab_piece_dispo[i].actif = 1;
                        break;
                    }
                }
            }
            break;
		case SDL_QUIT:
			gameover = 1;
			finjeu = 1;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			    finjeu = 1;
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

/* Fonction de gestion du depot de piece sur la grille */
void deposer_piece(int id, Carre **g, int posx, int posy ){
    int posable = 1;
    int x, y;
    int i, j;
    x = (int)(floor(posx/32));
    y = (int)(floor(posy/32));

    /* Test si la piece peut etre placée */
    for (i = 0; i < tab_piece_dispo[id].dimx; i++)
    {
        for (j = 0; j < tab_piece_dispo[id].dimy; j++)
        {

            if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0)
            {
                if (g[x+i-1][y+j-1].actif == 1 && tab_piece_dispo[id].grille[i][j].actif == 1) // Piece chevauchant une piece déjà dans la grille
                {
                    posable = 0;
                }
            }
            else // Piece sortante de la grille
            {
                posable = 0;
            }
        }
    }


    if (posable == 1) // La pièce peut être placée
    {
        for (i = 0; i < tab_piece_dispo[id].dimx; i++)
        {
            for (j = 0; j < tab_piece_dispo[id].dimy; j++)
            {
                if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0)
                {
                    if (tab_piece_dispo[id].grille[i][j].actif != 0)
                    {
                        g[x+i-1][y+j-1] = copie_carre(tab_piece_dispo[id].grille[i][j]); // On écrit la pièce dans la grille
                    }
                }
            }
        }
        tab_piece_dispo[id] = copie_Piece(tab_piece_all[rand() % nb_max_input]);
        delai_piece = time(0);
        /* Lancement de la verification des lignes / colonnes */
        grille_LC(g, PLATEAU_X, PLATEAU_Y);
    }
}

/* Gestion des lignes entières et des colonnes entières */
void grille_LC(Carre **g, int larg, int haut){
    int tab_a_changer[larg+haut];
    int i, j;
    int test = 1;
    int score_temp = 0;

    /* Enregistrement des lignes colonnes à enlever */
    for (i = 0; i < haut; i++)
    {
        test = 1;
        for (j = 0; j < larg; j++)
        {
            if (g[j][i].actif == 0)
            {
                test = 0;
            }
        }
        tab_a_changer[i] = test;
    }
    for (j = 0; j < larg; j++)
    {
        test = 1;
        for (i = 0; i < haut; i++)
        {
            if (g[j][i].actif == 0)
            {
                test = 0;
            }
        }
        tab_a_changer[haut+j] = test;
    }

    /* Debut du vidage de ligne et colonne */
    /* On compte le score rapporte par la ligne / colonne */
    for (i = 0; i < haut; i++)
    {
        if (tab_a_changer[i] == 1)
        {
            for (j = 0; j < larg; j++)
            {
                score_temp += ((g[j][i].couleur)*5);
                //printf("Le Carre rapporte %d\n",(g[j][i].couleur)*5);
                /* Remise à zéro des carrés de la ligne */
                const_Carre(&g[j][i], 0, 0);
            }
        }
    }

    for (j = 0; j < larg; j++)
    {
        if (tab_a_changer[haut+j] == 1)
        {
            for (i = 0; i < haut; i++)
            {
                score_temp += ((g[j][i].couleur)*5);
                //printf("Le Carre rapporte %d\n",(g[j][i].couleur)*5);
                /* Remise à zéro des carrés de la colonne */
                const_Carre(&g[j][i], 0, 0);
            }
        }
    }

    /* Appel au score global */
    score += (score_temp);
}


/* Gestion du menu */
void eventact_menu(char *keys, int x, int y, SDL_Surface **background)
{
    SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
        case SDL_MOUSEBUTTONDOWN:
            if (x > 270 && x < 471)
            {
                if (y > 92 && y < 153)
                {
                    if (fenetre_menu == 0) // Jouer
                    {
                        gameover_menu = 1;
                        //fenetre_menu = 1;
                    }
                    break;
                }
                if (y > 170 && y < 230)
                {
                    if (fenetre_menu == 0) // Scores
                    {
                        SDL_Surface *temp;
                        temp = SDL_LoadBMP("Sprites/scores.bmp");
                        (*background) = SDL_DisplayFormat(temp);
                        SDL_FreeSurface(temp);
                        trie_score();
                        fenetre_menu = 1;
                    }
                    break;
                }
                if (y > 248 && y < 310)
                {
                    if (fenetre_menu == 0) // Credits
                    {
                        SDL_Surface *temp;
                        temp = SDL_LoadBMP("Sprites/credits_bg.bmp");
                        (*background) = SDL_DisplayFormat(temp);
                        SDL_FreeSurface(temp);
                        fenetre_menu = 1;
                    }
                    break;
                }
                if (y > 326 && y < 388)
                {
                    if (fenetre_menu == 0) // Quitter
                    {
                        finjeu = 1;
                        gameover_menu = 1;
                        gameover = 1;
                    }
                    break;
                }
                if (y > 390 && y < 452)
                {
                    if (fenetre_menu == 1) // Retour
                    {
                        SDL_Surface *temp;
                        temp = SDL_LoadBMP("Sprites/accueil_bg.bmp");
                        (*background) = SDL_DisplayFormat(temp);
                        SDL_FreeSurface(temp);
                        fenetre_menu = 0;
                    }
                    break;
                }
            }
            break;
		case SDL_QUIT:
			gameover = 1;
			finjeu = 1;
			gameover_menu = 1;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				gameover = 1;
				gameover_menu = 1;
				finjeu = 1;
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

/* Tri des scores stockés dans scores.txt */
void trie_score_aux(int *tab, int n)
{
	int i, min, j, tmp;
	for (i = 0; i < n; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (tab[j] > tab[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			tmp = tab[i];
			tab[i] = tab[min];
			tab[min] = tmp;
		}
	}
}

/* Tri des scores stockés dans scores.txt */
void trie_score()
{
	FILE *fichier = fopen("scores.txt", "r+");
	int i, tmp;
	int nb_ligne = 0;
	while (fscanf(fichier, "%d", &tmp) != EOF)
	{
		nb_ligne++;
	}
	int score[nb_ligne];
	rewind(fichier);
	i = 0;
	while (fscanf(fichier, "%d", &score[i++]) != EOF);
	fclose(fichier);
	fichier = fopen("scores.txt", "w");
	trie_score_aux(score, nb_ligne);
	for (i = 0; i < nb_ligne && i < 10; i++)
	{
		fprintf(fichier, "%d\n", score[i]);
	}
	fclose(fichier);
}




























