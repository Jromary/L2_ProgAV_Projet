#INPUT/OUTPUT
game: main.c #ICI, nom des des fichiers du projets

# Commande de compilation
gcc -Wall -g -std=c99 main.c #ICI, nom des fichiers également
 `sdl-config --cflags --libs` -lm  -o game


# -lm => Bibliotheque math.h
