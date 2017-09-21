#INPUT/OUTPUT
game: main.c carre.c grille.c grille.h carre.h piece.h piece.c globals.h globals.c event.h event.c

# Commande de compilation
	gcc -Wall -g -std=c99 main.c carre.c grille.c piece.h piece.c carre.h grille.h globals.h globals.c event.h event.c `sdl-config --cflags --libs` -lm -o game


# -lm => Bibliotheque math.h
