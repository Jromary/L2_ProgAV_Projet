#INPUT/OUTPUT
game: main.c carre.c grille.c grille.h carre.h piece.h piece.c globals.h globals.c event.h event.c chargement.h chargement.c menu.c menu.h

# Commande de compilation
	gcc -Wall -g -std=c99 main.c carre.c grille.c piece.h piece.c carre.h grille.h globals.h globals.c event.h event.c chargement.h chargement.c menu.c menu.h `sdl-config --cflags --libs` -lm -o game


# -lm => Bibliotheque math.h
