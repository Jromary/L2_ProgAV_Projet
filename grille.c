#include <SDL.h>
#include <unistd.h>
#include <stdlib.h>


void Grille(Carre **a, int taille) {
    **a = (Carre **)malloc(sizeof(Carre*) * taille);
    for (int i = 0; i < taille; i++){
        a[i] = (Carre*)malloc(sizeof(Carre*) * taille);
    }
}
