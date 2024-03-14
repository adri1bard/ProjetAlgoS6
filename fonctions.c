#include "header.h"

 void enlever_fleches(char *chaine) {
    int longueur = strlen(chaine);
    int j = 0;

    for (int i = 0; i < longueur; i++) {
        if (chaine[i] == '-' && chaine[i + 1] == '>') {
            // Saute les caractères "->"
            i += 2;
        }
        chaine[j++] = chaine[i];
    }
    chaine[j] = '\0'; // Ajoute le caractère de fin de chaîne
}

void enlever_point(char *chaine) {
    int longueur = strlen(chaine);
    int j = 0;

    for (int i = 0; i < longueur; i++) {
        if (chaine[i] == '.') {
            // Saute les caractères "->"
            i ++;
        }
        chaine[j++] = chaine[i];
    }
    chaine[j] = '\0'; // Ajoute le caractère de fin de chaîne
}




// Fonction pour ajouter un élément à la liste
void ajouter_element(el **liste, char *chaine) {
    el *nouvel_element = (el*)malloc(sizeof(el));
    if (nouvel_element == NULL) {
        printf("Erreur d'allocation de mémoire pour nouvel_element.\n");
        exit(EXIT_FAILURE);
    }
    nouvel_element->chaine = strdup(chaine); // strdup alloue de la mémoire pour la chaîne et copie la chaîne
    nouvel_element->suiv = *liste;
    nouvel_element->prec = NULL;

    if (*liste != NULL) {
        (*liste)->prec = nouvel_element;
    }

    *liste = nouvel_element;
}

void afficher_liste(el *liste) {
    while (liste != NULL) {
        printf("%s ", liste->chaine);
        liste = liste->suiv;
    }
    printf("\n");
}

// Fonction pour afficher les règles
void afficher_Regles(Regles *Liste) {
    while (Liste != NULL) {
        el *temp = Liste->premier;
        while (temp != NULL) {
            printf("%s ", temp->chaine);
            temp = temp->suiv;
        }
        printf("\n");
        Liste = Liste->suiv;
    }
}

// Fonction pour libérer la mémoire allouée pour une liste d'éléments
void liberer_liste(el *liste) {
    el *temp;
    while (liste != NULL) {
        temp = liste;
        liste = liste->suiv;
        free(temp->chaine);
        free(temp);
    }
}

// Fonction pour libérer la mémoire allouée pour une liste de règles
void liberer_Regles(Regles *Liste) {
    Regles *temp;
    while (Liste != NULL) {
        temp = Liste;
        Liste = Liste->suiv;
        liberer_liste(temp->premier);
        free(temp);
    }
}
Regles* LireFichier(char *nomFichier) {
    FILE *fichier = fopen(NomDuFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(EXIT_FAILURE);
    }

    Regles *Liste = NULL;
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        el *listeElements = NULL;
        char a[10], b[10], c[10], arrow[10], d[10];
        enlever_fleches(ligne);



        // Utilisation de sscanf pour séparer la ligne en parties
        if (sscanf(ligne, "%s %s %s %s", a, b, c, d) == 4) {
            // Ignorer la partie "->"
            // Maintenant, vous avez les parties de la ligne séparées
            // Ajoutez-les à votre liste ou faites ce que vous devez faire avec elles
            if(a[0]!='.'){

                    ajouter_element(&listeElements, a);
            }
            if(b[0]!='.'){

                    ajouter_element(&listeElements, b);
            }
            if(c[0]!='.'){

                    ajouter_element(&listeElements, c);
            }
            if(d[0]!='.'){

                    ajouter_element(&listeElements, d);
            }

        } else {
            printf("Erreur de lecture de la ligne.\n");
            // Gérer l'erreur ou passer à la prochaine itération selon vos besoins
            continue;
        }

        Regles *nouvelle_regles = (Regles*)malloc(sizeof(Regles));
        if (nouvelle_regles == NULL) {
            printf("Erreur d'allocation de mémoire pour nouvelle_regles.\n");
            fclose(fichier);
            liberer_Regles(Liste);
            exit(EXIT_FAILURE);
        }
        nouvelle_regles->premier = listeElements;
        nouvelle_regles->suiv = NULL;

        if (Liste == NULL) {
            Liste = nouvelle_regles;
        } else {
            Regles *temp = Liste;
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = nouvelle_regles;
        }
    }

    fclose(fichier);

    return Liste;
}







int detecteLettre(const char *chaine, char lettre) {
    char *token = malloc(strlen(chaine) + 1); // +1 pour le caractère de fin de chaîne
    strcpy(token, chaine);
    int i = 0;
    while (token[i] != '\0') {

        if (token[i] == lettre) {

            free(token); // Libérer la mémoire allouée avant de retourner
            return 1; // La lettre a été trouvée
        }
        i++;
    }
    free(token); // Libérer la mémoire allouée avant de retourner
    return 0;
}

// Fonction pour parcourir la liste chaînée et détecter la présence d'une lettre dans chaque chaîne
void parcourirListe(Regles *liste, char lettre) {
    Regles *courant = liste;

    while (courant != NULL) {
        el *temp = courant->premier;
        while (temp != NULL) {
            if (detecteLettre(temp->chaine, lettre)) {
                printf("La lettre '%c' est presente dans la chaîne :", lettre);
                afficher_liste(courant->premier);
                printf("\n");

            }
            temp = temp->suiv;
            /* else {

                //printf("La lettre '%c' n'est pas presente dans la chaîne :", lettre);
                //afficher_liste(courant->premier);
                //printf("\n");
            }*/
        }


        courant = courant->suiv;
    }
}
