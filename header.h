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

int detecteLettre(const char *chaine, char lettre);

void parcourirListe(Regles *liste, char lettre);

 

#endif /* HEADER_H */
