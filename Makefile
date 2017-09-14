#INPUT/OUTPUT
game: main.c carre.c grille.c grille.h carre.h

# Commande de compilation
	gcc -Wall -g -std=c99 main.c carre.c grille.c carre.h grille.h `sdl-config --cflags --libs` -lm -o game


# -lm => Bibliotheque math.h
