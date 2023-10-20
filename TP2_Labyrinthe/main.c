
#include <limits.h>
#include "Graphe.h"
#include "fifo.h"

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{
    printf(" sommet %d :\n",num);

    pArc arc=sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("%d ",arc->sommet);
        arc=arc->arc_suivant;
    }
}

pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;


        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;

            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2;

    printf("%s \n", nomFichier);

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    fscanf(ifs,"%d",&taille);
    fscanf(ifs,"%d",&orientation);

    graphe->orientation=orientation;
    graphe->ordre=ordre;
    graphe->taille = taille;                                            //modif mais pas sur

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d",&s1,&s2);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, 0);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, 0);
    }

    return graphe;
}

Graphe * lire_graphe_TP3(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2, valeursommetactuel, poidsarc;

    printf("%s \n", nomFichier);

    if (!ifs)
    {
        printf("Erreur de lecture fichier \n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    for (int i = 0; i< ordre; ++i){
        fscanf(ifs, "%d", &valeursommetactuel);
        graphe->pSommet[i]->valeur = valeursommetactuel;

        graphe->pSommet[i]->tagged = 0;
        graphe->pSommet[i]->distance = INT_MAX - 1; //-1 dans le code équivaut a l'infini sur le papier
    }

    fscanf(ifs,"%d",&taille);

    graphe->orientation = 0;
    graphe->ordre=ordre;
    graphe->taille = taille;


    // créer les arêtes du graphe
    for (int i=0; i<taille; i++)
    {
        fscanf(ifs,"%d%d",&s1,&s2);
        fscanf(ifs,"%d",&poidsarc);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poidsarc);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, poidsarc);
    }

    return graphe;
}


/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    if(graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }
}

void BFS(Graphe *pGraphe, int sommetinit, File* F) {
    int etape = 0;
    int numsommetactuel = sommetinit;
    bool sommetdecouvert[pGraphe->ordre];

    if (pGraphe == NULL) {
        fprintf(stderr, "erreur - le graphe n'existe pas");
        exit(0);
    }
    else{
        for (int i = 0; i < pGraphe->ordre; i++) {  //on initialise la découverte a false pour tous les sommets
            sommetdecouvert[i] = false;
        }

            pSommet Sommet = pGraphe->pSommet[numsommetactuel];             //définit le premier sommet que l'on va utiliser

            enfiler(*F, numsommetactuel);                           //on ajoute la première valeur du sommet a la file
            printf("Etape %d du BFS \n", etape);
            ecrireFile(*F);
            defiler(*F);

            sommetdecouvert[numsommetactuel] = true;
            pGraphe->pSommet[numsommetactuel]->tagged = true;

            if(Sommet->arc == NULL){
                printf("le sommet n'a pas de descendant");
                return;
            }

            do {

                pArc Arccourant = Sommet->arc;

                while (Arccourant != NULL) {
                    if(sommetdecouvert[Arccourant->sommet] != true){
                        enfiler(*F, Arccourant->sommet);
                    }
                    sommetdecouvert[Arccourant->sommet] = true;
                    Arccourant = Arccourant->arc_suivant;
                }

                ++etape;

                printf("Etape %d du BFS \n", etape);
                ecrireFile(*F);                             // on ecrit la liste

                numsommetactuel = defilement(
                        *F);           // on enregistre la valeur du premier sommet dans la liste et on le retire

                Sommet = pGraphe->pSommet[numsommetactuel];

            } while (longueur(*F) != 0);
        printf("- \n fin du BFS");
    }
}

void DFS(Graphe *pGraphe, int sommetinit, int etape, File* F){
    if (pGraphe == NULL) {
        fprintf(stderr, "erreur - le graphe n'existe pas");
        exit(0);
    }

    if(etape == 0){
        pGraphe->pSommet[sommetinit]->tagged = true;
    }

    if (pGraphe->pSommet[sommetinit]->tagged == false){
        enfiler(*F, sommetinit);
        pGraphe->pSommet[sommetinit]->tagged = true;
    }

    pArc Arccourant = pGraphe->pSommet[sommetinit]->arc;

    while (Arccourant != NULL){
        if(pGraphe->pSommet[Arccourant->sommet]->tagged == false){
            enfiler(*F, Arccourant->sommet);
            pGraphe->pSommet[Arccourant->sommet]->tagged = true;
        }
        Arccourant = Arccourant->arc_suivant;
    }

    etape++;

    if (longueur(*F) != 0){
        printf("Etape %d du DFS \n", etape);
        ecrireFile(*F);
        int sommetlast = defilerDernier(*F);        //on supprime le dernier sommet de la liste

        DFS(pGraphe,sommetlast, etape, F);
    }
    else{
        printf("Fin du DFS / pas de successeurs");
        return;
    }
}

void DFSconnexite(Graphe *pGraphe, int sommetinit, int etape, File* F, File* File){
    if (pGraphe == NULL) {
        fprintf(stderr, "erreur - le graphe n'existe pas");
        exit(0);
    }

    if(etape == 0){
        pGraphe->pSommet[sommetinit]->tagged = true;
    }

    if (pGraphe->pSommet[sommetinit]->tagged == false){
        enfiler(*F, sommetinit);
        pGraphe->pSommet[sommetinit]->tagged = true;
    }

    pArc Arccourant = pGraphe->pSommet[sommetinit]->arc;

    while (Arccourant != NULL){
        if(pGraphe->pSommet[Arccourant->sommet]->tagged == false){
            enfiler(*F, Arccourant->sommet);
            enfiler(*File, Arccourant->sommet);
            pGraphe->pSommet[Arccourant->sommet]->tagged = true;
        }
        Arccourant = Arccourant->arc_suivant;
        //ecrireFile(*F);
    }

    etape++;

    if (longueur(*F) != 0){
        //printf("Etape %d du DFS \n", etape);
        //ecrireFile(*F);
        int sommetlast = defilerDernier(*F);        //on supprime le dernier sommet de la liste

        DFSconnexite(pGraphe,sommetlast, etape, F, File);
    }
    else{
        ecrireFile(*F);
        //printf("Fin du DFS / pas de successeurs");
        return;
    }
}

void afficher_composantes_connexes(Graphe *pGraphe) {
    int etape = 0;
    File F = fileVide();
    File File = fileVide();

    for (int sommet = 0; sommet < pGraphe->ordre; sommet++) {
        if (!pGraphe->pSommet[sommet]->tagged) {
            printf("Composante connexe %d :\n", etape);
            DFSconnexite(pGraphe, sommet, etape, &F, &File);
            ecrireFile(File);
            File = fileVide();
            printf("\n");
            etape++;
            sommet = 0;
        }

        printf("%d",pGraphe->pSommet[7]->tagged);
    }
}

int cmpfunc (const void * a, const void * b) {      //fonction permettant de trier les sommets https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
    return ( *(int*)a - *(int*)b );
}

/*void Dijkstra(Graphe *pGraphe, int sommetdepart) {
    if (pGraphe == NULL) {
        fprintf(stderr, "erreur - le graphe n'existe pas");
        exit(0);
    }

    int pluspetitedistance = INT_MAX;
    int distanceadditioncalcul = 0;
    int etapedijkstra =0;

    pGraphe->pSommet[sommetdepart]->distance = 0;
    pGraphe->pSommet[sommetdepart]->tagged = 1;

    pArc Arcsuivant = pGraphe->pSommet[sommetdepart]->arc;

    while (1){

        while(Arcsuivant != NULL){
            if (pGraphe->pSommet[Arcsuivant->sommet]->distance > Arcsuivant->poids + distanceadditioncalcul){
                pGraphe->pSommet[Arcsuivant->sommet]->distance = Arcsuivant->poids + distanceadditioncalcul;
                printf("%d \n", pGraphe->pSommet[Arcsuivant->sommet]->distance);
            }

            Arcsuivant = Arcsuivant->arc_suivant;
        }

        for (int i = 0; i<pGraphe->ordre; i++){
            if (pGraphe->pSommet[i]->tagged == 0 && pGraphe->pSommet[i]->distance < pluspetitedistance){
                Arcsuivant = pGraphe->pSommet[i]->arc;
                pluspetitedistance = pGraphe->pSommet[i]->distance;

                printf("plus petite distance :%d \n", pluspetitedistance);
                printf("%d \n", i);

                distanceadditioncalcul = pluspetitedistance;
                pGraphe->pSommet[i]->tagged = 1;
            }
        }

        if(etapedijkstra == pGraphe->ordre){
            break;
        }

        etapedijkstra++;
    }

    for (int i=0; i<pGraphe->ordre; i++){
        printf("La distance du sommet %d vaut %d \n", i, pGraphe->pSommet[0]->distance);
    }


    printf("fin de Dijkstra");
}*/

void Dijkstra(Graphe *pGraphe, int sommetdepart) {
    if (pGraphe == NULL) {
        fprintf(stderr, "Erreur - le graphe n'existe pas\n");
        exit(1);
    }

    int etapedijkstra = 0;

    for (int i = 0; i < pGraphe->ordre; i++) {
        pGraphe->pSommet[i]->distance = INT_MAX;
        pGraphe->pSommet[i]->tagged = 0;
    }

    pGraphe->pSommet[sommetdepart]->distance = 0;

    while (etapedijkstra < pGraphe->ordre) {
        int sommetcourant = -1;
        int distance_minimale = INT_MAX;

        for (int i = 0; i < pGraphe->ordre; i++) {
            if (!pGraphe->pSommet[i]->tagged && pGraphe->pSommet[i]->distance < distance_minimale) {
                sommetcourant = i;
                distance_minimale = pGraphe->pSommet[i]->distance;
            }
        }

        if (sommetcourant == -1) {
            break; // Tous les sommets inaccessibles ont été visités
        }

        pGraphe->pSommet[sommetcourant]->tagged = 1;

        pArc Arcsuivant = pGraphe->pSommet[sommetcourant]->arc;

        while (Arcsuivant != NULL) {
            int next = Arcsuivant->sommet;
            int poids = Arcsuivant->poids;

            if (!pGraphe->pSommet[next]->tagged && pGraphe->pSommet[sommetcourant]->distance + poids < pGraphe->pSommet[next]->distance) {
                pGraphe->pSommet[next]->distance = pGraphe->pSommet[sommetcourant]->distance + poids;
            }

            Arcsuivant = Arcsuivant->arc_suivant;
        }

        etapedijkstra++;
    }

    printf("pGraphe->pSommet minimales depuis le sommet %d :\n", sommetdepart);
    for (int i = 0; i < pGraphe->ordre; i++) {
        printf("Sommet %d : Distance = %d\n", i, pGraphe->pSommet[i]->distance);
    }
}



int main()
{
    Graphe * g;
    Graphe * dijkstra;

    int sommetdepart;

    int etape = 0;

    File fileattenteBFS = fileVide();     //vient créer une file pour le BFS
    File fileattenteDFS = fileVide();     //DFS
    char nom_fichier[50];

    printf("entrer le nom du fichier du labyrinthe: ");
    gets(nom_fichier);

    //g = lire_graphe(nom_fichier);


    /*for (int i=0; i<g->ordre; i++){       //on initalise la découverte des sommets pour le DFS (l'téta est stocké dans la structure des sommets
        g->pSommet[i]->tagged = false;
    }*/

    dijkstra = lire_graphe_TP3(nom_fichier);

    ///saisie du numéro du sommet initial pour lancer un BFS puis un DSF
    printf("quel est le sommet initial ");
    scanf("%d",&sommetdepart);

    //printf("%d \n", sommetdepart);

    Dijkstra(dijkstra, sommetdepart);


    //BFS(g, sommetdepart,&fileattenteBFS);

    //DFS(g, sommetdepart, etape, &fileattenteDFS);

    //afficher_composantes_connexes(g);

    /// afficher le graphe
    //graphe_afficher(g);

    return 0;
}
