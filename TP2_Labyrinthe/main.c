
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
        graphe->pSommet[i]->distance = -1; //-1 dans le code équivaut a l'infini sur le papier
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

    pArc Arccourant = graphe->pSommet[8]->arc;

    while (Arccourant != NULL){
        printf("%d \n", Arccourant->poids);
        Arccourant = Arccourant->arc_suivant;
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

void Dijkstra(Graphe * pGraphe, int sommetinit){
    if (pGraphe == NULL) {
        fprintf(stderr, "erreur - le graphe n'existe pas");
        exit(0);
    }

    int sommetactuel;
    int pppoids = 0;
    int sommetpppoids;
    int etapedijkstra = 0;
    int etapearc = 0;

    sommetactuel = sommetinit;

    pArc Arcsuivant = pGraphe->pSommet[sommetactuel]->arc;      // définit arcsuivant comme étant le premier arc sortant d'un sommet

    if (etapearc == 0){
        pGraphe->pSommet[sommetinit]->tagged = 1;
        pGraphe->pSommet[sommetinit]->distance = 0;
    }                                                           // on initialise pour le premier sommet

    while (Arcsuivant != NULL){
        printf("%d \n", Arcsuivant->valeur);
        Arcsuivant = Arcsuivant->arc_suivant;
    }


    while (etapedijkstra != pGraphe->ordre){

        while (Arcsuivant != NULL){

            if (pGraphe->pSommet[Arcsuivant->sommet]->distance == -1){
                pGraphe->pSommet[Arcsuivant->sommet]->distance = Arcsuivant->poids + pppoids;
            }
            else if (pGraphe->pSommet[Arcsuivant->sommet]->distance > Arcsuivant->poids + pppoids){      //on vérifie que la nouvelle distance est plus courte
                pGraphe->pSommet[Arcsuivant->sommet]->distance = Arcsuivant->poids + pppoids;
            }

            if (etapearc == 0){
                pppoids = Arcsuivant->poids;

                etapearc++;                                      //etapearc correspond a l'arc sortant sur lequel on se trouve
            }
            else if(Arcsuivant->poids < pppoids){
                pppoids = Arcsuivant->poids;
                sommetpppoids = Arcsuivant->sommet;
                printf("%d sommet de plus petit poids \n", sommetpppoids);
                printf("%d plus petit poids \n", pppoids);
                etapearc++;
            }

            Arcsuivant = Arcsuivant->arc_suivant;                  // on se place sur l'arrête suivante
        }

        Arcsuivant = pGraphe->pSommet[sommetpppoids]->arc;        // on prend comme nouvel arc l'arc sortant du sommet de plus petite distance
        pGraphe->pSommet[sommetpppoids]->tagged = 1;
        etapedijkstra++;

        //printf("%d \n", pppoids);
    }

    /*for (int j = 0; j < pGraphe->ordre; j++){
        printf("La distance au sommet %d vaut : \n", j);
        printf("%d", pGraphe->pSommet[j]->distance);
    }*/
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

    printf("entrer le nom du fichier du labyrinthe:");
    gets(nom_fichier);

    //g = lire_graphe(nom_fichier);


    /*for (int i=0; i<g->ordre; i++){       //on initalise la découverte des sommets pour le DFS (l'téta est stocké dans la structure des sommets
        g->pSommet[i]->tagged = false;
    }*/

    dijkstra = lire_graphe_TP3(nom_fichier);

    ///saisie du numéro du sommet initial pour lancer un BFS puis un DSF
    printf("quel est le sommet initial");
    scanf("%d",&sommetdepart);

    printf("%d \n", sommetdepart);

    //Dijkstra(dijkstra, sommetdepart);


    //BFS(g, sommetdepart,&fileattenteBFS);

    //DFS(g, sommetdepart, etape, &fileattenteDFS);

    //afficher_composantes_connexes(g);

    /// afficher le graphe
    //graphe_afficher(g);

    return 0;
}
