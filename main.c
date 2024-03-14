#include "header.h"
#include "fonctions.c"
#include <stdio.h>
#include <stdlib.h>

int main() {

    Regles *Liste= LireFichier("projet.txt");

    printf("Contenu de la liste :\n");

    afficher_Regles(Liste);

    printf("_______________________________\n");

    parcourirListe(Liste, 'a');

    liberer_Regles(Liste);

 

    return EXIT_SUCCESS;

}
