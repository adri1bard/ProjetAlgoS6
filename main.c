#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
int main() {

    Regles *Liste= LireFichier("Prof.txt");
    printf("Contenu de la liste :\n");

    afficher_Regles(Liste);
    printf("_______________________________\n");
    el *faits = NULL;
    ajouter_element(&faits, "b");
    chainerAvant(Liste, &faits);
    printf("\n \nBase de faits apres chainerAvant :\n");
    afficher_liste(faits);

    return EXIT_SUCCESS;
}
