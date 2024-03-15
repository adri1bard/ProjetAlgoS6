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

void enlever_pointvirgule(char *chaine) {
    int longueur = strlen(chaine);
    int j = 0;

    for (int i = 0; i < longueur; i++) {
        if (chaine[i] == ';') {
            // Saute les caractères "->"
            i ++;
        }
        chaine[j++] = chaine[i];
    }
    chaine[j] = '\0'; // Ajoute le caractère de fin de chaîne
}


// Fonction pour ajouter un élément à la liste
void ajouter_element(el **liste, char *chaine) {
    // Vérification si l'élément est déjà présent dans la liste
    el *courant = *liste;
    while (courant != NULL) {
        if (strcmp(courant->chaine, chaine) == 0) {
            // L'élément est déjà présent, donc on ne l'ajoute pas de nouveau
            return;
        }
        courant = courant->suiv;
    }

    // L'élément n'est pas déjà présent, on l'ajoute à la liste
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
    if (liste == NULL) {
        printf("\n");
        return;
    }


    while (liste != NULL) {
        printf(" %s", liste->chaine);
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
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(EXIT_FAILURE);
    }

    Regles *Liste = NULL;
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Traitement des flèches et des points
        enlever_fleches(ligne);
        enlever_point(ligne);
        enlever_pointvirgule(ligne);
        ligne[strcspn(ligne, "\n")] = '\0';

        el *listeElements = NULL;

        char *token = strtok(ligne, " ");
        while (token != NULL) {
            ajouter_element(&listeElements, token);
            token = strtok(NULL, " ");
        }

        // Création d'une nouvelle règle
        Regles *nouvelle_regles = (Regles*)malloc(sizeof(Regles));
        if (nouvelle_regles == NULL) {
            printf("Erreur d'allocation de mémoire pour nouvelle_regles.\n");
            fclose(fichier);
            liberer_Regles(Liste);
            exit(EXIT_FAILURE);
        }
        nouvelle_regles->premier = listeElements;
        nouvelle_regles->suiv = NULL;

        // Ajout de la nouvelle règle à la liste
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




// Fonction pour détecter si un élément de la règle est un fait littéral
//retourne 1 si la chaine est dans la base de faits
int isLitteralFact(char *chaine, el* faits) {
    el *temp = faits;
    while (temp != NULL) {
        if (strcmp(chaine, temp->chaine) == 0) {
            return 1;
        }
        temp = temp->suiv;
    }
    return 0;
}


//Detecte si les elements de la regle sont tous dans la base de faits
//retourne 1 si tous les elements de la regle sont dans la base de faits
//Ajoute l'element en tete de liste de la regle à la base de faits
int detecteFaits(el *regle, el **faits) {
    el *temp = regle; // Pointeur temporaire pour parcourir la règle
    if (isLitteralFact(regle->chaine, *faits)) {
        printf("La tête de liste est dans les faits\n");
        return 0;
    }
    printf("La tête de liste n'est PAS dans les faits\n");
    temp = temp->suiv; // Évite la tête de liste
    // Parcours de la règle
    while (temp != NULL) {
        printf("temp->chaine : %s\n", temp->chaine);
        // Vérification si l'élément de la règle est présent dans les faits
        if (isLitteralFact(temp->chaine, *faits)) {
            temp = temp->suiv;
        } else {
            return 0;
        }
        // Passage à l'élément suivant de la règle
    }

    // Si tous les éléments de la règle sont trouvés dans les faits, la règle peut être appliquée
    // Ajout de l'élément en tête de liste de la règle à la base de faits
    printf("regle->chaine : %s\n", regle->chaine);
    ajouter_element(faits, regle->chaine);

    return 1; // Renvoie 1 pour indiquer que la règle peut être appliquée
}





void chainerAvant(Regles *listeRegles, el **baseFaits) {
    int reglesAppliquees = 1; // Indicateur pour savoir si des règles ont été appliquées dans une itération

    // Tant qu'au moins une règle a été appliquée dans une itération précédente
    while (reglesAppliquees) {
        reglesAppliquees = 0; // Réinitialise l'indicateur à chaque itération
        Regles *regleCourante = listeRegles;

        // Parcours de toutes les règles
        while (regleCourante != NULL) {
            // Si tous les éléments de la règle sont dans la base de faits, la conclusion peut etre ajoutée aux faits
            if (detecteFaits(regleCourante->premier, baseFaits)) {
                // Ajout de la tête de la conclusion à la base de faits
                ajouter_element(baseFaits, regleCourante->premier->chaine);
                reglesAppliquees = 1; // Indique qu'au moins une règle a été appliquée
            }
            regleCourante = regleCourante->suiv;
        }
    }
}




