// fifo.c

//code source : http://morissardjerome.free.fr/langageC/graphe2.html


#include <stdio.h>
#include "fifo.h"
#include "stdlib.h"


File fileVide() {
    File F;
    F = (File)malloc(sizeof(struct _file));
    if (F == NULL) printf("erreur allocation fileVide");
    F->longueur = 0;
    F->tete = F->queue = NULL;
    return(F);
}   //Alloue et renvoie une file

int longueur(File F) {
    if (F == NULL)printf("file existe pas - longueur");
    return(F->longueur);
}   //indique la longueur d'une file

void enfiler(File F, typage element) {
    Cellule cellule;                                                    //définit chacun des sommets sous la forme d'une cellule
    if (F == NULL) printf ("file existe pas - enfiler");

    cellule = (Cellule)malloc(sizeof(struct _cellule));
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");
    cellule->element = element;
    cellule->suivant = NULL;
    if (longueur(F) == 0){
        F->tete = F->queue = cellule;
    }
    else {
        F->queue->suivant = cellule;
        F->queue = cellule;
    }
    ++(F->longueur);
}

typage tete(File F) {
    if (F == NULL || longueur(F) == 0) printf(" File existe pas - tete");
    return(F->tete->element);
}

typage dernierElement(File F) {
    if (F == NULL || longueur(F) == 0) {
        printf("File est vide ou n'existe pas - dernierElement\n");
        return 0; // Valeur par défaut (à adapter selon vos besoins)
    }

    return F->queue->element;
}

void defiler(File F) {
    Cellule cellule;

    if (F == NULL || longueur(F) == 0)printf("File existe pas - defiler");
    cellule = F->tete;
    if (longueur(F) == 1)
        F->tete = F->queue = NULL;
    else
        F->tete = F->tete->suivant;
    --(F->longueur);
    free(cellule);
}

typage defilerDernier(File F) {
    if (F == NULL || longueur(F) == 0) {
        printf("File est vide ou n'existe pas - defilerDernier\n");
        return 0;
    }

    if (longueur(F) == 1){
        typage element = F->tete->element;
        F->tete = F->queue = NULL;
        free(F->tete);
        F->longueur = 0;
        return element;
    }

    Cellule avantDernier = F->tete;
    while (avantDernier->suivant != F->queue) {
        avantDernier = avantDernier->suivant;
    }

    typage element = F->queue->element;
    free(F->queue);
    F->queue = avantDernier;
    avantDernier->suivant = NULL;
    F->longueur--;

    return element;
}


typage defilement(File F) {
    Cellule cellule;
    typage element;
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");
    cellule = F->tete;
    element = cellule->element;
    if (longueur(F) == 1){
        F->tete = F->queue = NULL;
    }
    else{
        F->tete = F->tete->suivant;
    }
    free(cellule);
    --(F->longueur);
    return(element);
}


void ecrireFile(File F) {
    Cellule cellule;

    if (F == NULL) printf("erreur ecrireFile");
    cellule = F->tete;
    while (cellule != NULL) {
        printf("%d ", cellule->element);
        cellule = cellule->suivant;
    }
    printf("\n");
}
