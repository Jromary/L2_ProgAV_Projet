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

/* Charge les entrées stockées dans "input.txt" dans les tableaux de pièces */
void load()
{
    /* Verification du fichier input */
    FILE *fichier_verif = fopen("input.txt", "r+");
    char temp;
    int valide;
    if (fichier_verif != NULL)
    {
        do
        {

            valide = 0;
            temp = fgetc(fichier_verif);
            for(int i = 0; i < 10; i++){
                if (isdigit(temp) || !strcmp(&temp, "\n")){
                    valide = 1;
                };
            }
        }while (temp != EOF && valide);
    }
    fclose(fichier_verif);

    if (!valide && temp != EOF){
        printf("\n ERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");
        printf("ERREUR:\n >>> Caractere non numerique\n");
        exit(0);
    }



    /* Compteur de lignes dans le fichier input */
    int nb_lignes = 0;
    int compteur_piece = 0;
    FILE *fichier_ctp = fopen("input.txt", "r+");
    int tmp;
    while (fscanf(fichier_ctp, "%d", &tmp) != EOF)
    {
        nb_lignes++;
        if(tmp == 0)
        {
            compteur_piece++;
        }
    }
    fclose(fichier_ctp);

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
                        printf("ERREUR:\n >>> Caractere numerique non conforme\n");
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

