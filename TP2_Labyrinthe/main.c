
#include <limits.h>
#include "Graphe.h"
#include "fifo.h"

int cmpfunc (const void * a, const void * b) {              //source : https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
    return ( *(int*)a - *(int*)b );
}

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
    graphe->taille = taille;

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d",&s1,&s2);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, 0);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, 0);
    }

    for (int i =0; i<ordre; i++){
        graphe->pSommet[i]->tagged = false;
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

    graphe->poidsKruskal = malloc(taille * sizeof (int));           //on fait une allocation de la mémoire qui va permettre de stocker les poids par ordre croissant
    graphe->tableaukruskal = malloc(taille*sizeof (Kruskal));


    // créer les arêtes du graphe
    for (int i=0; i<taille; i++)
    {
        fscanf(ifs,"%d%d",&s1,&s2);
        fscanf(ifs,"%d",&poidsarc);

        graphe->poidsKruskal[i] = poidsarc;

        graphe->tableaukruskal[i].sommet1 =s1;
        graphe->tableaukruskal[i].sommet2 =s2;
        graphe->tableaukruskal[i].poids = poidsarc;

        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poidsarc);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, poidsarc);
    }

    qsort(graphe->poidsKruskal, graphe->taille, sizeof(int), cmpfunc);      // on trie les poids dans l'ordre croissant

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
        //ecrireFile(*F);
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


void Kruskal_fct(Graphe* pGraphe){
    if (pGraphe == NULL) {
        fprintf(stderr, "Erreur - le graphe n'existe pas\n");
        exit(1);
    }

    int sommet1, sommet2;               //on définit les deux sommets de départ et d'arrivée de l'arc courant
    pSommet Sommet1, Sommet2;           // on définit les deux sommets équivalents a leurs numéros (strucutre)

    int pppoids;

    int i =0;
    int etape = 0;
    int currenttagged = 1;

    int sommepoids = 0;


    while (etape !=pGraphe->taille){

        pppoids = pGraphe->poidsKruskal[0];                   // on récupère le plus petit poids dans le tableau du graphe
        pGraphe->poidsKruskal[0] = INT_MAX-etape;             // on passe la plus petite distance à int max pour ne pas s'en resservir par la suite

        while (pGraphe->tableaukruskal[i].poids != pppoids){
            i++;
        }

        qsort(pGraphe->poidsKruskal, pGraphe->taille, sizeof(int), cmpfunc);      // on retrie les poids dans l'ordre croissant

        sommet1 = pGraphe->tableaukruskal[i].sommet1;
        sommet2 = pGraphe->tableaukruskal[i].sommet2;

        Sommet1 = pGraphe->pSommet[sommet1];
        Sommet2 = pGraphe->pSommet[sommet2];



        if (etape == 0){
            Sommet1->tagged = currenttagged;            // on tag les sommets à 0
            Sommet2->tagged = currenttagged;

            printf("on tag les sommets de depart \n");
            sommepoids += pppoids;

        }
        else{
            if(Sommet1->tagged != 0 && Sommet2->tagged == 0){
                Sommet2->tagged = 1;
                //printf("Sommet %d a ete tag \n", Sommet2->valeur);

                //printf("%d", Sommet2->distance);

                sommepoids += pppoids;
            }
            else if(Sommet2->tagged != 0 && Sommet1->tagged == 0){
                Sommet1->tagged = 1;
                //printf("Sommet %d a ete tag \n", Sommet1->valeur);

                sommepoids += pppoids;
            }
            else if(Sommet2->tagged == 0 && Sommet1->tagged == 0){
                Sommet1->tagged = Sommet1->valeur;
                Sommet2->tagged = Sommet1->valeur;
                //printf("Les sommets %d et %d ont ete tag \n", Sommet1->valeur, Sommet2->valeur);

                sommepoids += pppoids;
            }

            if (Sommet1->tagged == 1 && Sommet2->tagged != 1){
                for (int k =0; k<pGraphe->ordre; k++){
                    if (pGraphe->pSommet[k]->tagged == Sommet2->tagged){
                        pGraphe->pSommet[k]->tagged = 1;
                    }
                }
                sommepoids += pppoids;
            }
            else if (Sommet2->tagged == 1 && Sommet1->tagged != 1){
                for (int k =0; k<pGraphe->ordre; k++){
                    if (pGraphe->pSommet[k]->tagged == Sommet1->tagged){
                        pGraphe->pSommet[k]->tagged = 1;
                    }
                }
            }
        }

        etape++;
        i=0;
    }

    printf("\n \n la somme des poids vaut %d", sommepoids);
}

void prim (Graphe* pGraphe, int sommetdepart){

    int* parent = malloc(pGraphe->ordre * sizeof(int));
    int* liste_poids_arbre = malloc(pGraphe->ordre * sizeof(int));
    int* sommet_inclu = malloc(pGraphe->ordre * sizeof(int)); // équivalent à tagged
    int poidsTotal = 0;


    // Initialisation de tous les sommets
    for (int i = 0; i < pGraphe->ordre; i++) {
        liste_poids_arbre[i] = INT_MAX;
        sommet_inclu[i] = 0; // Non inclus dans MST
    }

    //Initialisation Sommet départ
    liste_poids_arbre[sommetdepart] = 0; // Le sommet de départ est toujours inclus
    parent[sommetdepart] = -1; // Le sommet de départ est la racine du MST

    for (int i = 0; i < pGraphe->ordre - 1; i++) {
        int min = INT_MAX, u;

        // Trouver le sommet adjacent avec le poids minimale sur l'arête liante, à partir
        // de l'ensemble des sommets non encore inclus dans sommet_inclu
        for (int v = 0; v < pGraphe->ordre; v++) {
            if (sommet_inclu[v] == 0 && liste_poids_arbre[v] < min)
                min = liste_poids_arbre[v], u = v;
        }
        sommet_inclu[u] = 1;

        pArc arc;
        for (arc = pGraphe->pSommet[u]->arc; arc != NULL; arc = arc->arc_suivant) {
            if (sommet_inclu[arc->sommet] == 0 && arc->poids < liste_poids_arbre[arc->sommet]) {
                parent[arc->sommet] = u;
                liste_poids_arbre[arc->sommet] = arc->poids;

            }
        }
    }

    printf("Arete   Poids\n");
    for (int i = 0; i < pGraphe->ordre; i++) {
        if(parent[i] != -1) {
            printf("%d - %d    %d \n", parent[i], i, liste_poids_arbre[i]);
            poidsTotal += liste_poids_arbre[i];
        }
    }

    printf("Poids total de l'arbre de recouvrement minimal : %d\n", poidsTotal);

    free(parent);
    free(liste_poids_arbre);
    free(sommet_inclu);

}

int main()
{
    Graphe * g;
    Graphe * dijkstra;

    int numTP;
    int choixTP;

    int sommetdepart;

    int etape = 0;

    File fileattenteBFS = fileVide();     //vient créer une file pour le BFS
    File fileattenteDFS = fileVide();     //DFS
    char nom_fichier[50];

    printf("entrer le nom du fichier du labyrinthe:\n");
    gets(nom_fichier);

    printf("Quel TP souhaitez vous utliser ? (2, 3 ou 5) \n");
    scanf("%d",&numTP);

    if (numTP == 2){

        g = lire_graphe(nom_fichier);

        printf("Souhaitez vous faire un BFS ou un DFS ? (1 / 2) \n");
        scanf("%d", &choixTP);

        printf("quel est le sommet initial ");
        scanf("%d",&sommetdepart);

        if (choixTP == 1){
            BFS(g, sommetdepart,&fileattenteBFS);
        }

        if (choixTP == 2) {


            DFS(g, sommetdepart,etape, &fileattenteDFS);

        }
    }

    if (numTP == 3){
        printf("quel est le sommet initial ");
        scanf("%d",&sommetdepart);

        dijkstra = lire_graphe_TP3(nom_fichier);
        Dijkstra(dijkstra, sommetdepart);
    }

    if (numTP == 5){
        printf("Souhaitez vous faire un Kruskal ou un Prim ? (1 / 2) \n");
        scanf("%d", &choixTP);

        if( choixTP == 1){
            dijkstra = lire_graphe_TP3(nom_fichier);
            Kruskal_fct(dijkstra);
        }
        else if ( choixTP == 2){
        printf("quel est le sommet initial\n ");
        scanf("%d",&sommetdepart);
        dijkstra = lire_graphe_TP3(nom_fichier);
        prim (dijkstra,sommetdepart);
        }

    }

    /// afficher le graphe
    ///graphe_afficher(g);

    return 0;
}
