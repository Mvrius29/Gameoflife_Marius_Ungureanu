#include <stdio.h>
#include <stdlib.h>

typedef struct lista1
{
    int linie;
    int coloana;
    struct lista1 *next;
} Lista1;

typedef struct stiva1
{
    Lista1 *head_list;
    struct stiva1 *next;
} Stiva1;

void verificare_alocare(const void  *p);
void eliberare_mem_matrice1(char ***matrice,int lini);
int verificare_indici(int linie, int coloana, int nr_linii, int nr_coloane);
void verificare_vecin(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void verificare_celule_vecine(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void alocare_memorie_matrice(char ***matrice,int lini,int coloane);
void eliberare_mem_lista1(Lista1 **lst);
void eliberare_memorie_stiva1(Stiva1 **top);
void adaugare_elem_lista1(Lista1 **lst, int linie, int coloana);
void push_stiva1(Stiva1 **top, Lista1 *lst);
Lista1* generare_lista_modificari(char **matrice,int lini,int coloane);
void scriere_stiva_in_fisier(Stiva1 *top, FILE *fisier_output, int generatie);
