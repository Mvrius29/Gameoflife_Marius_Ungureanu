#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Task2 functii si definti de tipuri de date necesare pentru cel de al doilea task
typedef struct lista
{
    int linie;
    int coloana;
    struct lista *next;
} Lista;

typedef struct stiva
{
    Lista *head_list;
    struct stiva *next;
} Stiva;

//Definitie nod arbore necesar pentru task-ul 3 
typedef struct arbore
{
    Lista *head_list;
    struct arbore *left, *right;
}Node;

/// Task2 functii necesare in plus oentru lista si stiva
//void creare_lista(Lista **lst, int linie, int coloana);
void adaugare_elem_lista(Lista **lst, int linie, int coloana);
void push_stiva(Stiva **top, Lista *lst);
void scriere_stiva_in_fisier(Stiva *top, FILE *fisier_output, int generatie);
void eliberare_mem_lista(Lista **lst);
void eliberare_memorie_stiva(Stiva **top);

//Task1
void verificare_alocare(const void  *p);
void alocare_memorie_matrice(char ***matrice,int lini,int coloane);
void citire_date(char ***matrice, int *nr_task, int *nr_generatii, int *lini, int *coloane, char **argv);
int verificare_indici(int linie, int coloana, int nr_linii, int nr_coloane);
void verificare_vecin(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void verificare_celule_vecine(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void scriere_matrice_in_fisier(char ***matrice,char **matrice_modificata,int lini,FILE *fisier_output);
void modificare_matrice(char ***matrice,char **matrice_modificata,int lini);


////Task 3 functii necesare in plus pentru lucurl cu arbori
Node* createNode(Lista *lst);
Node *create_Root(char **matrice, int lini, int coloane, FILE *fisier_output);
void scriere_matrice_nod_in_fisier1(char **matrice,int lini,FILE *fisier_output);
void eliberare_mem_matrice_char(char ***matrice,int lini);
void eliberare_mem_arbore(Node **root);
char **genereare_matrice_nod(char **matrice, int lini, int coloane, Node *root);

///Task 4 functii necesare + structurii de date necesare 
typedef struct pozitinoduri
{
    int linie;
    int coloana;
    int node;
    int componenta;
    int elem_componenta;

} PozitiNoduri;
void eliberare_mem_matrice_int(int ***matrice,int lini);
void alocare_memorie_matrice_int(int ***matrice, int lini, int coloane);
int determinare_nr_celule_vii(char **matrice, int lini, int coloane);
int **generare_matrice_noduri(char **matrice, int lini, int coloane, int nr_noduri, PozitiNoduri **vector);
void verificare_conexiune(int **matrice_noduri, int **matrice_adiacenta, int linie, int coloana, int linie_vecin, int coloana_vecin, int lini, int coloane);
void creare_muchii_graf(int **matrice, int **matrice_adiacenta, int linie, int coloana, int lini, int coloane);
int **creare_matrice_de_adiacenta(int **matrice_noduri, int lini, int coloane, int numar_noduri);
void determinare_componenta_conexa(int nod, int **matrice_adiacenta, int nr_noduri, int *dim, int *vizitat, int nr_componenta, PozitiNoduri *vector);
void determinare_drum_hamiltonian(int nod, int **matrice_adiacenta, int dim_Max, int *gasit, int nr_noduri, int *dim, int *drum, int *vizitat, PozitiNoduri *vector);
void cautare_drumuri(int **matrice_adiacenta, int **matrice_noduri, int lini, int coloane, int nr_noduri, int **vec_max, int *MAX, PozitiNoduri *vector);
void scriere_drum_hamiltonian_in_fisier(char **matrice, int lini, int coloane, FILE *fisier_output);