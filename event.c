/***********************************
*                                  *
*      GESTION DES EVENEMENTS      *
*                                  *
***********************************/

#include <math.h>
#include <time.h>

#include <SDL.h>

#include "globals.h"
#include "piece.h"
#include "carre.h"
#include "event.h"

#define maximum(a,b) ((a > b) ? (a) : (b))
#define minimum(a,b) ((a < b) ? (a) : (b))

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

extern int affichescore;

extern int pressagain;

extern SDL_Surface *screen;


int plusbombe = 0;
int credits_ouverts = 0;



/* Fonction principale de gestion d'évenements */
void update_events(char *keys, int x, int y, Carre **plateau)
{
    int test = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        /*
        * Test pour savoir sur quelle piece on se situe si on en aucune en deplacement
        *
        * sinon, essaye de poser la piece dans la grille de jeu
        */
        case SDL_MOUSEBUTTONDOWN:
            for (int i = 0; i < nb_piece; i++) {
                if(tab_piece_dispo[i].actif == 1) {
                    test=1;
                }
            }
            for (int i = 0; i < nb_piece; i++) {
                // Test pour voir si la position de la souris match une case libre (ie non active)
                if ((x >= tab_piece_dispo[i].pos.x) &&
                        (x <= tab_piece_dispo[i].bd.x) &&
                        (y >= tab_piece_dispo[i].pos.y) &&
                        (y <= tab_piece_dispo[i].bd.y)) {
                    if (tab_piece_dispo[i].actif == 1) {
                        tab_piece_dispo[i].actif = 0;
                        deposer_piece(i, plateau, x, y);
                    } else if(test == 0) {
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
            switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                if (pressagain) {
                    pressagain = 0;
                }
                break;
            default:
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                finjeu = 1;
                gameover = 1;
                break;
            case SDLK_SPACE:
                if (!pressagain) {
                    for (int i = 0; i < nb_piece; i++) {
                        if(tab_piece_dispo[i].actif == 1) {
                            rota_piece(&tab_piece_dispo[i]);
                            break;
                        }
                    }
                    pressagain = 1;
                }
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

/* Gestion de la bombe 3x3 sur l'interface de jeu */
void bombas(int id, Carre **g, int posx, int posy)
{
    int x, y;
    int i, j, k, l;
    x = (int)(floor(posx/32)); // Conversion de la position de la souris en position sur la grille
    y = (int)(floor(posy/32));
    int score_temp = 0;

    /* On verifie que la bombe est bien dans le plateau */
    if (x <= PLATEAU_X && y <= PLATEAU_Y && x > 0 && y > 0) {
        k = minimum(PLATEAU_X-1, x);
        l = minimum(PLATEAU_Y-1, y);
        i = maximum(0, x-2);
        while (i <= k) {
            j = maximum(0, y-2);
            while (j <= l) {
                if (g[i][j].actif == 1) {
                    score_temp += ((g[j][i].couleur)*5); // On ajoute aux scores des points pour chaque carre detruit
                }
                const_Carre(&g[i][j], 0, 0); // Remplissage dans la grille de vide
                j++;
            }
            i++;
        }
    }
    score += score_temp;
    tab_piece_dispo[id] = copie_Piece(tab_piece_all[rand() % nb_max_input]); // On ajoute une piece dans le jeu de 3 pieces disponibles
    delai_piece = time(0);
}

/* Fonction testant si un piece est posable à une position donnee */
int piece_posable(int id, Carre **g, int posx, int posy )
{
    int posable = 1;
    int x, y;
    int i, j;
    x = (int)(floor(posx/32));
    y = (int)(floor(posy/32));
    i = 0;
    j = 0;

    while (i < tab_piece_dispo[id].dimx && posable) {
        while (j < tab_piece_dispo[id].dimy && posable) {
            if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0) { // On est dans la grille
                if (g[x+i-1][y+j-1].actif == 1 && tab_piece_dispo[id].grille[i][j].actif == 1) {
                    // Piece chevauchant une piece déjà dans la grille
                    posable = 0;
                }
            } else {// Piece sortante de la grille
                posable = 0;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return posable;
}

/* Fonction de gestion du depot de piece sur la grille */
void deposer_piece(int id, Carre **g, int posx, int posy )
{
    if (tab_piece_dispo[id].grille[0][0].couleur == 999) { // Si la piece qu'on pose sur la grille est une bombe,
            // appel de la fonction adaptée
        bombas(id, g, posx, posy);
    } else {

        int posable;
        int x, y;
        int i, j, k, l;
        x = (int)(floor(posx/32));
        y = (int)(floor(posy/32));

        /* Test si la piece peut etre placée */
        posable = piece_posable(id, g, posx, posy);

        if (posable == 1) {// La pièce peut être placée
            for (i = 0; i < tab_piece_dispo[id].dimx; i++) {
                for (j = 0; j < tab_piece_dispo[id].dimy; j++) {
                    if (x+i <= PLATEAU_X && y+j <= PLATEAU_Y && x+i > 0 && y+j > 0) {
                        if (tab_piece_dispo[id].grille[i][j].actif != 0) {
                            g[x+i-1][y+j-1] = copie_carre(tab_piece_dispo[id].grille[i][j]); // On écrit la pièce dans la grille
                        }
                    }
                }
            }

            /* Lancement de la verification des lignes / colonnes */
            grille_LC(g, PLATEAU_X, PLATEAU_Y);

            if (plusbombe == 1) {
                tab_piece_dispo[id] = tab_piece_all[nb_max_input];
                plusbombe = 0;
            } else {
                tab_piece_dispo[id] = copie_Piece(tab_piece_all[rand() % nb_max_input]);
            }

            posable = 0;
            x = 0;
            y = 0;
            k = 0;
            l = 0;
            /* Verification si une des 3 pieces dispo (et ses rotations) est posable
            * si non, gameover
            */
            while (l < 4) {
                while (x < PLATEAU_X && !posable) {
                    while (y < PLATEAU_Y && !posable) {
                        while (k < NB_PIECE_MAX && !posable) {
                            if (piece_posable(k, g, 32 + x*32, 32 + y*32)) {
                                posable = 1;
                            }
                            k++;
                        }
                        k = 0;
                        y++;
                    }
                    y = 0;
                    x++;
                }
                rota_piece(&tab_piece_dispo[k]);
                l++;
            }
            if(!posable) {
                gameover = 1;
            }
            delai_piece = time(0);
        }
    }
}

/* Gestion des lignes entières et des colonnes entières */
void grille_LC(Carre **g, int larg, int haut)
{
    int tab_a_changer[larg+haut];
    int i, j;
    int test = 1;
    int score_temp = 0;

    /* Enregistrement des lignes colonnes à enlever */
    for (i = 0; i < haut; i++) {
        test = 1;
        for (j = 0; j < larg; j++) {
            if (g[j][i].actif == 0) {
                test = 0;
            }
        }
        tab_a_changer[i] = test;
    }
    for (j = 0; j < larg; j++) {
        test = 1;
        for (i = 0; i < haut; i++) {
            if (g[j][i].actif == 0) {
                test = 0;
            }
        }
        tab_a_changer[haut+j] = test;
    }

    /* Debut du vidage de ligne et colonne */
    /* On compte le score rapporte par la ligne / colonne */
    for (i = 0; i < haut; i++) {
        if (tab_a_changer[i] == 1) {
            for (j = 0; j < larg; j++) {
                score_temp += ((g[j][i].couleur)*5);
                /* Remise à zéro des carrés de la ligne */
                const_Carre(&g[j][i], 0, 0);
            }
        }
    }

    for (j = 0; j < larg; j++) {
        if (tab_a_changer[haut+j] == 1) {
            for (i = 0; i < haut; i++) {
                score_temp += ((g[j][i].couleur)*5);
                /* Remise à zéro des carrés de la colonne */
                const_Carre(&g[j][i], 0, 0);
            }
        }
    }
    /* Appel au score global */
    if (score_temp > 0) {
        plusbombe = 1;
    } else {
        plusbombe = 0;
    }
    score += (score_temp);
}


/* Gestion du menu */
void eventact_menu(char *keys, int x, int y, SDL_Surface **background)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if(!credits_ouverts) {
                if (x > 270 && x < 471) {
                    if (y > 92 && y < 153) {
                        if (fenetre_menu == 0) {// Jouer
                            gameover_menu = 1;
                        }
                        break;
                    }
                    if (y > 170 && y < 230) {
                        if (fenetre_menu == 0) { // Scores
                            SDL_Surface *temp;
                            temp = SDL_LoadBMP("Sprites/scores.bmp");
                            (*background) = SDL_DisplayFormat(temp);
                            SDL_FreeSurface(temp);
                            trie_score();
                            fenetre_menu = 1;
                            affichescore = 1;
                        }
                        break;
                    }
                    if (y > 248 && y < 310) {
                        if (fenetre_menu == 0) { // Credits
                            SDL_Surface *temp;
                            temp = SDL_LoadBMP("Sprites/credits_bg.bmp");
                            (*background) = SDL_DisplayFormat(temp);
                            SDL_FreeSurface(temp);
                            fenetre_menu = 1;
                            credits_ouverts = 1;
                        }
                        break;
                    }
                    if (y > 326 && y < 388) {
                        if (fenetre_menu == 0) { // Quitter
                            finjeu = 1;
                            gameover_menu = 1;
                            gameover = 1;
                        }
                        break;
                    }
                    if (y > 390 && y < 452) {
                        if (fenetre_menu == 1) { // Retour
                            SDL_Surface *temp;
                            temp = SDL_LoadBMP("Sprites/accueil_bg.bmp");
                            (*background) = SDL_DisplayFormat(temp);
                            SDL_FreeSurface(temp);
                            fenetre_menu = 0;
                            affichescore = 0;
                            credits_ouverts = 0;
                        }
                        break;
                    }
                }


            } else { // Credits déja ouverts, test pour lien cliquable
                if(x>168 && x<585) {
                    if(y>224 && y<327) { // cas 1
                        system("xdg-open https://github.com/Jromary/L2_ProgAV_Projet");
                        break;
                    }
                    if (y > 390 && y < 452) { // Cas 2
                        if (fenetre_menu == 1) { // Retour
                            SDL_Surface *temp;
                            temp = SDL_LoadBMP("Sprites/accueil_bg.bmp");
                            (*background) = SDL_DisplayFormat(temp);
                            SDL_FreeSurface(temp);
                            fenetre_menu = 0;
                            affichescore = 0;
                            credits_ouverts = 0;
                        }
                        break;
                    }
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
            switch (event.key.keysym.sym) {
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
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (tab[j] > tab[min]) {
                min = j;
            }
        }
        if (min != i) {
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
    if (fichier == NULL) { // Creation du fichier si il est inexistant
        fichier = fopen("scores.txt", "w");
    }
    int i, tmp;
    int nb_ligne = 0;
    /* compteur de ligne */
    while (fscanf(fichier, "%d", &tmp) != EOF) {
        nb_ligne++;
    }
    int score[nb_ligne];
    rewind(fichier);
    i = 0;
    /* Parcours du fichier et enregistrement des scores */
    while (fscanf(fichier, "%d", &score[i++]) != EOF);
    fclose(fichier);
    fichier = fopen("scores.txt", "w");
    /* Tri des scores dans le fichier */
    trie_score_aux(score, nb_ligne);
    /* réecriture dans le fichier */
    for (i = 0; i < nb_ligne && i < 5; i++) {
        fprintf(fichier, "%d\n", score[i]);
    }
    fclose(fichier);
}

void printscore()
{
    FILE *fichier = fopen("scores.txt", "r");
    int nb_ligne = 0;
    int i, tmp;
    while (fscanf(fichier, "%d", &tmp) != EOF) {
        nb_ligne++;
    }
    int score[nb_ligne];
    rewind(fichier);
    while (fscanf(fichier, "%d", &score[i++]) != EOF);
    for (i = 0; i < nb_ligne; i++) {
        affiche_nombre((screen_length / 2) - 64, i * (screen_height / (nb_ligne + 5)), score[i]);
    }
    fclose(fichier);
}


void affiche_nombre(int x, int y, int nb)
{
    SDL_Surface *temp, *nombre;
    temp = SDL_LoadBMP("Sprites/nombre_v2.bmp");
    nombre = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    int colorkey_nb = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(nombre, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_nb);

    SDL_Rect pi;
    pi.x = x;
    pi.y = y;
    int nb_chifre = 0;
    int nb_aux = nb;
    while (nb_aux > 9) {
        nb_aux = nb_aux / 10;
        nb_chifre++;
    }

    int nb_split[nb_chifre];
    for (int i = 0; i <= nb_chifre; i++) {
        nb_split[i] = nb % 10;
        nb = nb / 10;
    }
    SDL_Rect nombreImage;
    for (int i = 0; i <= nb_chifre; i++) {
        nombreImage.x = nb_split[nb_chifre - i] * 32;
        nombreImage.y = 0;
        nombreImage.w = 32;
        nombreImage.h = 34;
        SDL_BlitSurface(nombre, &nombreImage, screen, &pi);
        pi.x += 32;
    }
}























