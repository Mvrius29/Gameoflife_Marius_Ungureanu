#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void verificare_alocare(const void *p);
void alocare_memorie_matrice(char ***matrice, int lini, int coloane);
void creare_lista(Lista **lst, int linie, int coloana);
void adaugare_elem_lista(Lista *lst, int linie, int coloana);
void push_stiva(Stiva **top, Lista *lst);
int isEmpty(const Stiva *top);
Lista* pop_stiva(Stiva **top);
void scriere_matrice_in_fisier(char **matrice,int lini,FILE *fisier_output);