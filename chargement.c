#include <SDL.h>

#include "chargement.h"
#include "piece.h"
#include "globals.h"

extern int tab_piece_all_raw[MAX_INPUT_RAW];
extern int nb_max_input_raw;

extern Piece tab_piece_all[MAX_INPUT];
extern int nb_max_input;

void load(){
    FILE *fichier = fopen("input.txt", "r+");
    int i = 0;
    while (fscanf(fichier, "%d", &tab_piece_all_raw[i++]) != EOF){
        nb_max_input_raw++;
    };
    for(i = 0; i < nb_max_input_raw; i++){
        printf("%d\n", tab_piece_all_raw[i]);
    }

    i = 0;
    int temp1, temp2, j, nb, larg, haut, deb;

    while (i < nb_max_input_raw){
            haut = 0;
            temp2 = i;
            deb = i;
        while (tab_piece_all_raw[i] != 0){
            i++;
            temp2++;
            haut++;
        }
        i++;
        temp1 = tab_piece_all_raw[deb];
        larg = 0;
        while (temp1 >= 1){
            temp1 = temp1 / 10;
            larg++;
        }


        tab_piece_all[nb_max_input] = const_Piece(larg, haut, 0, 0);
        int alea = (rand() % 3) + 1;
        for (j = 0; j < haut; j++){
            temp1 = tab_piece_all_raw[deb+j];
            int countcol = 0;
            while (temp1 >= 1){
                nb = temp1 % 10;
                temp1 = temp1 / 10;
                switch (nb){
                    case 1:
                        /*cas ou la case doit etre de l'air*/
                        const_Carre(&tab_piece_all[nb_max_input].grille[larg - countcol - 1][j], 0, 0);
                        break;
                    case 8:
                        /*cas ou la case est utilisé*/
                        const_Carre(&tab_piece_all[nb_max_input].grille[larg - countcol - 1][j], alea, 1);
                        break;
                    default:
                        printf("ERREUR DANS LE CHARGEMENT DES PIECE DU FICHIER SOURCE\n");

                }
                countcol++;
            }
        }

        nb_max_input++;
    }
    fclose(fichier);

}

