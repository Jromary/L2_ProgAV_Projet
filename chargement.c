/*********************************
*
*      CHARGEMENT DES PIECES
*
**********************************/

#include <SDL.h>
#include <stdlib.h>
#include <string.h>

#include "chargement.h"
#include "piece.h"
#include "globals.h"

//extern int tab_raw_input[MAX_INPUT_RAW];
extern int nb_max_input_raw;

extern Piece* tab_piece_all;
extern int nb_max_input;

int nb_lignes; // Utilisé dans compteur_ligne_input()
int compteur_piece; // Utilisé dans compteur_ligne_input()
char temp; // Utilisé dans compteur_ligne_input() - verification_input()


/* Charge les entrées stockées dans "input.txt" dans les tableaux de pièces et fais des verifications adéquates */
void load()
{
    /* Test de validité : Pieces rectangulaires et pas de caractères non conformes */
    FILE *fichier_verif = fopen("input.txt", "r+");
    int colonne, NaN ,pieceActive, colonne_piece, estUnZero, COL; // Flags d'erreurs
    if (fichier_verif != NULL){
        colonne = 0;
        colonne_piece = 0;
        pieceActive = 0;
        estUnZero = 0;
        COL = 0;
        NaN = 0;

        do{ // Parcours du fichier char par char
            temp = fgetc(fichier_verif);
            if (!isdigit(temp)){
                if(strcmp(&temp, "\n")){ // Test si le caractère lu est un nombre
                    if(temp != EOF){
                        NaN = 1;
                    }
                }
            }
            /* Test des colonnes identiques en taille */
            if(!strcmp(&temp,"0")){
                pieceActive = 0;
                estUnZero = 1;
            }
            if(!strcmp(&temp,"\n")){
                if(!pieceActive && !estUnZero){// Prend la reference de la piece
                    colonne_piece = colonne; // nombre de colonne pour cette piece
                    pieceActive = 1;
                }
                if(pieceActive && (colonne != colonne_piece)){ // La piece n'a pas le même nombre de colonne sur chaque lignes
                    COL = 1;
                }
                colonne = 0;
                estUnZero = 0;
            }
            else{colonne++;}
        }
        while (temp != EOF );
    }

    if(COL){
        printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
        printf("ERREUR:\n >>> Une pièce n'a pas le même nombre de colonne sur chaque ligne\n");
        SDL_Quit();
        exit(0);
    }
    if(NaN){
        printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
        printf("ERREUR:\n >>>Caractère non conforme\n");
        SDL_Quit();
        exit(0);
    }

    /* Test de validité : Fichier vide */
    compteur_ligne_input();
    if(nb_lignes == 0){
         printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
         printf("ERREUR:\n >>> Fichier vide\n");
         SDL_Quit();
         exit(0);
    }

    FILE *fichier = fopen("input.txt", "r+");
    int* tab_raw_input = creation_tab_int(nb_lignes);
    tab_piece_all = creation_tab_piece(compteur_piece);

    int i = 0;
    while (fscanf(fichier, "%d", &tab_raw_input[i++]) != EOF){
        nb_max_input_raw++;
    }
    for(i = 0; i < nb_max_input_raw; i++){
        printf("%d\n", tab_raw_input[i]);
    }

    i = 0;
    int temp1, temp2, j, nb, larg, haut, deb;

    while (i < nb_max_input_raw){
        haut = 0;
        temp2 = i;
        deb = i;
        while (tab_raw_input[i] != 0){
            i++;
            temp2++;
            haut++;
        }
        i++;
        temp1 = tab_raw_input[deb];
        larg = 0;
        while (temp1 >= 1){
            temp1 = temp1 / 10;
            larg++;
        }

        tab_piece_all[nb_max_input] = const_Piece(larg, haut, 0, 0);
        int alea = (rand() % 5) + 1;

        /* Test de validité : Piece vide */
        if(haut == 0){ //Test si une piece est vide est dans le fichier
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Chargement d'une pièce vide\n");
            for (int m = 0; m < nb_max_input; m++){
                free_piece(&tab_piece_all[i]);
            }
            fclose(fichier);
            free(tab_raw_input);
            exit(0);
        }

        /* Test de validité : Piece trop large */
        if(larg > LARGEUR_PIECE_MAX){ //Test si une piece est plus grande que le max
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Chargement d'une pièce d'une taille non conforme\n");
            for (int m = 0; m < nb_max_input; m++){
                free_piece(&tab_piece_all[i]);
            }
            fclose(fichier);
            free(tab_raw_input);
            exit(0);
        }

        for (j = 0; j < haut; j++){// Creation de piece
            temp1 = tab_raw_input[deb+j];
            int countcol = 0;
            while (temp1 >= 1){
                nb = temp1 % 10;
                temp1 = temp1 / 10;
                switch (nb){
                    case 1:
                        /* Cas ou la case doit etre de l'air*/
                        const_Carre(&tab_piece_all[nb_max_input].grille[larg - countcol - 1][j], 10, 0);
                        break;
                    case 8:
                        /* Cas ou la case est utilisé*/
                        const_Carre(&tab_piece_all[nb_max_input].grille[larg - countcol - 1][j], alea, 1);
                        break;
                    default:
                        printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
                        printf("ERREUR:\n >>> Caractere numerique non conforme\n");
                        exit(0);
                }
                countcol++;
            }
        }

        nb_max_input++;

        // Piece crée
        /* Test de validité : Ligne de vide */
        int test_vide_ligne, test_vide_col;
        for (int m=0; m<haut; m++){
            test_vide_ligne = 1;
            for(int p=0; p<larg; p++){
                if(tab_piece_all[nb_max_input-1].grille[p][m].couleur != 10){
                    // Ici, on n'a plus 8 et 1 mais un certain chiffre ou 10 pour le vide
                    test_vide_ligne = 0;
                }
            }
            if(test_vide_ligne){
                printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
                printf("ERREUR:\n >>> Presence d'une ligne de vide dans une pièce\n");
                for (int nb = 0; nb < nb_max_input; nb++)
                {
                    free_piece(&tab_piece_all[nb]);
                }
                fclose(fichier);
                free(tab_raw_input);
                exit(0);
            }
        }
        /* Test de validité : colonne de vide */
        for (int m=0; m<larg; m++){
            test_vide_col = 1;
            for(int p=0; p<haut; p++){
                if(tab_piece_all[nb_max_input-1].grille[m][p].couleur != 10){
                    // Ici, on n'a plus 8 et 1 mais un certain chiffre ou 10 pour le vide
                    test_vide_col = 0;
                }
            }
            if(test_vide_col){
                printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
                printf("ERREUR:\n >>> Presence d'une colonne de vide dans une pièce\n");
                for (int nb = 0; nb < nb_max_input; nb++){
                    free_piece(&tab_piece_all[nb]);
                }
                fclose(fichier);
                free(tab_raw_input);
                exit(0);
            }
        }
    }
    fclose(fichier);
    free(tab_raw_input);
}

/* Renvoie le nombre de motif dans le tableau de piece */
int compteMotif(int* tab_motif){
    int cnt;
    for(int k=0; k>nb_max_input_raw; k++){
        if(tab_motif[k]){
            // Test si la ligne vaut 0, auquel cas on change de motif
            cnt++;
        }
    }
    return cnt;
}

/* Compteur de lignes dans le fichier input */

void compteur_ligne_input()
{
    nb_lignes = 0;
    compteur_piece = 0;
    FILE *fichier_ctp = fopen("input.txt", "r+");
    int tmp;
    while (fscanf(fichier_ctp, "%d", &tmp) != EOF){
        nb_lignes++;
        if(strcmp(&temp,"0")){
            compteur_piece++;
        }
    }
    fclose(fichier_ctp);
    if(nb_lignes == 0){
         printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
         printf("ERREUR:\n >>> Fichier vide\n");
         exit(0);
    }
}
