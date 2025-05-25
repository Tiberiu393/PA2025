#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef enum statut
{
    LORD,
    CAVALER,
    AVENTURIER
} statut;

typedef struct participant
{
    char *nume;
    int varsta;
    float experienta;
    statut statut;
} participant;

typedef struct nod
{
    participant *date;
    struct nod *next;
} nod;

typedef struct coada
{
    nod *front;
    nod *rear;
} coada;

typedef struct bst
{
    participant *date;
    struct bst *stanga;
    struct bst *dreapta;
} node;

typedef struct traseu
{
    char nume[10];
    int paduri[10];
    int nr_paduri;
} traseu;

typedef struct part_cu_traseu
{
    participant *p;
    traseu *t;
} part_cu_traseu;

typedef struct heap
{
    part_cu_traseu *date;
    int dim, capacitate;
} heap;

typedef struct lista_ad
{
    int varf_nr;
    struct lista_ad *next;
} nod_lista;

typedef struct
{
    int V, E;
    nod_lista **a;
    int *grade_intrare, *grade_iesire;
} graf;

extern int index1;
extern int index2;
extern participant vector_lorzi[18];
extern participant vector_cavaleri[33];
coada *creare_coada();
void enq(coada *q, participant *p);
participant *creare_participant(char *linie);
void citire_fisier(coada *q);
void scriere_fisier_test1(coada *q);
void eliberare_mem(coada *q);
node *creerenodbs(participant *p);
node *inserare_bst(node *root, participant *p);
void stergere_din_coada(coada *q);
// node *creereBST_Lorzi(node *root, coada *q);
// node *creereBST_Aventurieri_Cavaleri(node *root, coada *q);
void construire_bsturi(coada *q, node **root_lorzi, node **root_cav_av);
void eliberare_mem_bst(node *root);
void scriere_fis2_lorzi(node *root);
void parcurgere_cav_av(node *root, FILE *f);
void parcurgere_lord(node *root, FILE *f);
void scriere_fis2_cav_av(node *root);
void citire_fisier_3(coada *q);
void scriere_fisier_3(node *root);
node *minValueNode(node *nod);
node *sterg_nodbst(node *root, participant *p);
void sterg_part(node **root, coada *q);
heap *create(int capacitate);
void resize(heap *h);
void inserare_heap(heap *h, part_cu_traseu *p);
void citeste_traseu(traseu trasee[], int *nr_trasee);
node *max_din_bst(node *root);
void filtrare_part(participant vector_lorzi[], participant vector_cavaleri[], int index1, int index2, traseu trasee[], int nr_trasee, heap *h);
void scriere_fisier4(heap *h);
void bst_to_vector_simplu(node *root);
void parcurgerein(node *root);
void scriere_vect();
void scriere_vect_cav();
void parcurgerein_cav(node *root);
void bst_to_vector_cav(node *root);
void eliberare_heap(heap *h);
void eliberare_vectl(participant vector_lorzi[], int nr_lorzi);
void eliberare_mem_vector_cavaleri(participant vector_cavaleri[], int nr_cavaleri);
void scriere_fisier5(heap *h);
void recalc_experienta(heap *h);
void heapify_down(heap *h, int i);
int right_child(heap *h, int i);
int left_child(heap *h, int i);
void scriere_fisier6(heap *h);
void printGraph(graf *g);
graf *creare_graf();
void adaugare_lista(graf *g, int iesire, int intrare);
void DFS(graf *g, int curent, int *vizitat, int len, int *traseu, int *finale, int nr_finale, char **rez, int *k);
void sursa_dest(graf *g, int *surse, int *nr_surse, int *destinatii, int *nr_destinatii);
void generat_trasee(graf *g, int *surse, int nr_surse, int *destinatii, int nr_destinatii, char ***rez, int *k);
// int comparare(const void *a, const void *b);
int compare_routes(const char *a, const char *b);
void interclasare(char **rez, int st, int mij, int dr);
void mergeSort(char **rez, int st, int dr);
void scrie_trasee_cu_prefix(char **rez, int k, const char *nume_fisier);
void eliberare_graf(graf *g);