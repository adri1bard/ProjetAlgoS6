#ifndef HEADER_H
#define HEADER_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct el {

    char* chaine;

    struct el *suiv;

    struct el *prec;

} el;

 

typedef struct Regles {

    el *premier;

    struct Regles *suiv;

    struct Regles *prec;

} Regles;

 

void enlever_fleches(char *chaine);

void enlever_point(char *chaine);

void ajouter_element(el **liste, char *chaine);

void afficher_liste(el *liste);

void afficher_Regles(Regles *Liste);

void liberer_liste(el *liste);

void liberer_Regles(Regles *Liste);

Regles* LireFichier(char *nomFichier);





// Fonction pour détecter si un élément de la règle est un fait littéral
//retourne 1 si la chaine est dans la base de faits
int isLitteralFact(char *chaine, el* faits);

//Detecte si les elements de la regle sont tous dans la base de faits
//retourne 1 si tous les elements de la regle sont dans la base de faits
//Ajoute l'element en tete de liste de la regle à la base de faits
int detecteFaits(el *regle, el **faits);

void chainerAvant(Regles *listeRegles, el **baseFaits);

 

#endif /* HEADER_H */
