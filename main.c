#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "fonctions.c"

int main() {

    Regles *Liste= LireFichier("Prof.txt");
    printf("Contenu de la liste :\n");

    afficher_Regles(Liste);
    printf("_______________________________\n");
    Regles *Faits= LireFichier("Faits.txt");
    el* faits=Faits->premier;
    chainerAvant(Liste, &faits);
    printf("\n \nBase de faits apres le chainage avant :\n");
    afficher_liste(faits);
    return EXIT_SUCCESS;
}
