/*cellule.h*/

//code source : http://morissardjerome.free.fr/langageC/graphe2.html

typedef int typage;

struct _cellule {
    typage element;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;