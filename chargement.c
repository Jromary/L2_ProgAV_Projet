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

int nb_lignes;
int compteur_piece;
int valide;
char temp;


/* Charge les entrées stockées dans "input.txt" dans les tableaux de pièces */
void load()
{
    /* Verification du fichier input */
    verification_input();
    /* Compteur de lignes dans le fichier input */
    compteur_ligne_input();

    FILE *fichier = fopen("input.txt", "r+");
    int* tab_raw_input = creation_tab_int(nb_lignes);
    tab_piece_all = creation_tab_piece(compteur_piece);

    int i = 0;
    while (fscanf(fichier, "%d", &tab_raw_input[i++]) != EOF)
    {
        nb_max_input_raw++;
    }
    for(i = 0; i < nb_max_input_raw; i++)
    {
        printf("%d\n", tab_raw_input[i]);
    }

    i = 0;
    int temp1, temp2, j, nb, larg, haut, deb;

    while (i < nb_max_input_raw)
    {
        haut = 0;
        temp2 = i;
        deb = i;
        while (tab_raw_input[i] != 0)
        {
            i++;
            temp2++;
            haut++;
        }
        i++;
        temp1 = tab_raw_input[deb];
        larg = 0;
        while (temp1 >= 1)
        {
            temp1 = temp1 / 10;
            larg++;
        }

        tab_piece_all[nb_max_input] = const_Piece(larg, haut, 0, 0);
        int alea = (rand() % 3) + 1;

        if(haut == 0) //Test si une piece est vide est dans le fichier
        {
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Chargement d'une pièce vide\n");
            exit(0);
        }

        for (j = 0; j < haut; j++)
        {
            temp1 = tab_raw_input[deb+j];
            int countcol = 0;
            while (temp1 >= 1)
            {
                nb = temp1 % 10;
                temp1 = temp1 / 10;
                switch (nb)
                {
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
                        printf("ERREUR:\n >>> Caractere numerique non conforme après verification\n");
                        exit(0);
                }
                countcol++;
            }
        }
        nb_max_input++;
    }
    fclose(fichier);
    free(tab_raw_input);
}

/* Renvoie le nombre de motif dans le tableau de piece */
int compteMotif(int* tab_motif)
{
    int cnt;
    for(int k=0; k>nb_max_input_raw; k++)
    {
        if(tab_motif[k]) // Test si la ligne vaut 0, auquel cas on change de motif
        {
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
    while (fscanf(fichier_ctp, "%d", &tmp) != EOF)
    {
        nb_lignes++;
        if(strcmp(&temp,"0"))
        {
            compteur_piece++;
        }
    }
    fclose(fichier_ctp);
    if(nb_lignes == 0)
    {
         printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
         printf("ERREUR:\n >>> Fichier vide\n");
         exit(0);
    }
}

/* Verification du fichier input */
void verification_input()
{
    FILE *fichier_verif = fopen("input.txt", "r+");
    int colonne,compteurVide, NaN, OF,F1, NaVN; // Flags d'erreurs




    if (fichier_verif != NULL)
    {
        colonne = 0;
        compteurVide = 0;
        F1 = 0;
        OF = 0;
        NaN = 0;
        NaVN = 0;// a faire
        do // Parcours du fichier char par char
        {
            temp = fgetc(fichier_verif);
            if (isdigit(temp) || !strcmp(&temp, "\n")) // Test si le caractère lu est un nombre
            {
                if(!strcmp(&temp,"1")) // Compteur de case représentant le vide
                {
                    compteurVide++;
                }
            }
            else
            {
                if(temp != EOF)
                {
                    NaN = 1;
                }
            }
            if(colonne > LARGEUR_PIECE_MAX) // Test si la ligne de la piece est d'une taille conforme
            {
                OF = 1;
            }
            if(!strcmp(&temp,"\n"))
            {
                //printf("col : %d - cv : %d\n",colonne,compteurVide);
                if(compteurVide == colonne)
                {
                    valide = 0;
                    F1 = 1;
                }
                colonne = 0;
                compteurVide = 0;
            }
            else{colonne++;}
        }
        while (temp != EOF );//&& valide);
    }

        // Verification et fermeture anticipée si besoin
        if(OF)
        {
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Chargement d'une pièce d'une taille non conforme\n");
        }
        if(NaN)
        {
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Caractere non numerique\n");
        }
        if(F1)
        {
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Ligne uniquement composée de carrés vides\n");
        }
        if(NaVN)
        {
            printf("\nERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
            printf("ERREUR:\n >>> Caractère numérique non conforme (non 8 ou non 1)\n");
        }
        if(OF || NaN || F1 || NaVN)
        {
            exit(0);
        }

    fclose(fichier_verif);
}

