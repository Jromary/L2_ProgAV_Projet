/*********************************
*
*      CHARGEMENT DES PIECES
*            en-tête
**********************************/

#ifndef CHARGEMENT_H
#define CHARGEMENT_H

/* Charge les entrées stockées dans "input.txt" dans les tableaux de pièces */
extern void load();

/* Renvoie le nombre de motif dans le tableau de piece */
extern int compteMotif(int* tab_motif);

extern void compteur_ligne_input();
extern void verification_input();


#endif /* CHARGEMENT_H */
