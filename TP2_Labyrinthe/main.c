
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

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
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

// créer le graphe
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
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1);
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

/*void DFS(Graphe *pGraphe, int sommetinit, int etape, File* F){
    if(pGraphe == NULL){
        fprintf(stderr, "erreur - le graphe n'existe pas");
        return;
    }

    pGraphe->pSommet[sommetinit]->tagged = true;


    if(Sommet->arc != NULL){
        DFS(pGraphe, Sommet->arc->sommet, etape, F);
    }
    else{

    }
}
*/


int main()
{
    Graphe * g;

    int sommetdepart;

    int etape = 0;

    File fileattenteBFS = fileVide();     //vient créer une file pour le BFS
    File fileattenteDFS = fileVide();     //DFS
    char nom_fichier[50];

    printf("entrer le nom du fichier du labyrinthe:");
    gets(nom_fichier);

    g = lire_graphe(nom_fichier);

    for (int i=0; i<g->ordre; i++){       //on initalise la découverte des sommets pour le DFS (l'téta est stocké dans la structure des sommets
        g->pSommet[i]->tagged = false;
    }

    ///saisie du numéro du sommet initial pour lancer un BFS puis un DSF
    printf("quel est le sommet initial");
    scanf("%d",&sommetdepart);

    //BFS(g, sommetdepart,&fileattenteBFS);

    //DFS(g, sommetdepart, etape, &fileattenteDFS);

    /// afficher le graphe
    //graphe_afficher(g);

    return 0;
}
