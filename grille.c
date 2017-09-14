#include <SDL.h>
#include <unistd.h>
#include <stdlib.h>

#include "carre.h"

Carre** aloc_one(int taille){
    return (Carre **)malloc(taille * sizeof(Carre*));
}
Carre* aloc_two(int taille){
    return (Carre *)malloc(taille * sizeof(Carre));
}

