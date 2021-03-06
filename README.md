# L2_ProgAV_Projet
Projet de programmation Avancé dans le cadre de la licence informatique 3ème semestre

## Le Jeu
### Execution
Pour lancer le programme, il faut télécharger l'archive contenant le projet et lancer la commande "make" pour compiler. L'executable s'appelera "game". On peut ensuite le lancer avec la commande "./game".

### Règles du jeu
Notre jeu est un tetris sur la hauteur et la largeur. Le but est de faire le score le plus élevé.
On dispose d'un triplet de pièces à droite de l'écran qu'on peut déposer sur la grille de jeu si toutes les cases colorées ne superposent pas de cases déjà dans la grille. On peut également utiliser la barre espace pour pivoter la pièce. Une fois posée, une autre pièce la remplace dans le triplet et le jeu continue. Pour chaque dépot, on dispose de 10 secondes (matérialisées par la barre décroissante en bas de l'écran).

Si on complète une ligne ou une colonne, on marque des points (en fonction des couleurs des carrés). De plus, une bombe peut apparaitre suite à celà dans le triplet (probabilité de 0.5). La bombe supprime (et fais gagner des points) les carrés de son voisinage une fois posée.

Le jeu s'arrête automatiquement si par malchance, aucune des pièces du triplet ne peut être posée. Le score est enregistré et est visible dans le menu "scores". Il est automatiquement trié et seul les cinq meilleurs sont visibles.

### Règles du fichier d'entrée
Le fichier d'entrée "input.txt" permet de définir soi-même les pièces pouvant apparaître dans le jeu.
Cependant il faut respecter une syntaxe :
- le 8 représente un carré de couleur
- le 1 représente du vide
- le 0 sépare les pièces
- pas de lignes vides
- pas d'autre caractères (2,a,*,/,...)

Le fichier commence directement par une pièce et pas un "0". La dernière ligne du fichier, elle, doit contenir un "0" et rien d'autre (pas de retour à la ligne). La forme des pièces doit être rectangulaire et minimale.

#### Exemple :
888 : une barre de 3x1 carrés

818<br>
818 : une pièce en "U"<br>
888<br>

811 : pièce non minimale <br>

88<br>
888 : pièce non rectangulaire **erreur**<br>
888<br>

881<br>
888 : pièce correcte<br>
888<br>

888<br>
9a8 : caractère non conforme **erreur**<br>
888<br>

## Contributeur
- Julien Romary [ julienromary@yahoo.fr ]
- Emmanuel Perrin 
