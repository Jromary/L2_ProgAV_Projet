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
    fclose(fichier);

}
