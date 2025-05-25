#include "bonus2_liste.h"

void verificare_alocare(const void  *p)
{
    if(p==NULL)
     {
        puts("EROARE");
        exit(1);
     }
}

void eliberare_mem_matrice1(char ***matrice,int lini)
{
    for(int i=0;i<lini;i++)
      free((*matrice)[i]);
    free(*matrice);
}

int verificare_indici(int linie, int coloana, int nr_linii, int nr_coloane)
{
    int prima_coloana = 0, prima_linie = 0;
    return linie >= prima_linie && linie < nr_linii && coloana >= prima_coloana && coloana < nr_coloane;
}

void verificare_vecin(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii)
{
    if (verificare_indici(linie, coloana, nr_linii, nr_coloane))
        if (matrice[linie][coloana] == 'X')
            (*vii)++;
}

void verificare_celule_vecine(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii)
{
    (*vii) = 0;
    verificare_vecin(matrice, linie - 1, coloana - 1, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie - 1, coloana, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie - 1, coloana + 1, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie, coloana - 1, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie, coloana + 1, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie + 1, coloana - 1, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie + 1, coloana, nr_linii, nr_coloane, vii);
    verificare_vecin(matrice, linie + 1, coloana + 1, nr_linii, nr_coloane, vii);
}

void alocare_memorie_matrice(char ***matrice,int lini,int coloane)
{
    *matrice = (char **)malloc(lini * sizeof(char *));
   verificare_alocare(*matrice);
    for (int j = 0; j < (lini); j++)
    {
        (*matrice)[j] = malloc(coloane * sizeof(char));
        verificare_alocare((*matrice)[j]);
    }
}

void eliberare_mem_lista1(Lista1 **lst)
{
    Lista1 *aux = NULL;
    
    while((*lst) != NULL)
    {
        aux = (*lst);
        (*lst) = (*lst) ->next;
        free(aux);
        aux = NULL;
    }
}

void eliberare_memorie_stiva1(Stiva1 **top)
{
    Stiva1 *iter=NULL;
    Lista1 *aux=NULL;
    while((*top)!=NULL)
    {
        iter=(*top);
        aux=iter->head_list;
        eliberare_mem_lista1(&aux);
        (*top)=(*top)->next;
        free(iter);
        iter=NULL;
    }
}

void adaugare_elem_lista1(Lista1 **lst, int linie, int coloana)
{

    Lista1 *new = malloc(sizeof(Lista1));
    verificare_alocare(new);
    new->linie = linie;
    new->coloana = coloana;
    new->next = NULL;
     
    if((*lst) == NULL)
       {
        (*lst) = new;
       return;
       }
    else
    {
    Lista1 *aux = *lst;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new;
    }
}

void push_stiva1(Stiva1 **top, Lista1 *lst)
{
        Stiva1 *nod = malloc(sizeof(Stiva1));
        verificare_alocare(nod);
        nod->head_list = lst;
        (nod)->next = (*top);
        (*top) = nod;
}

Lista1* generare_lista_modificari(char **matrice,int lini,int coloane)
{
    Lista1 *new = NULL;
    int conditie1_vii = 2, conditie2_vii = 3, conditie1_dead = 3;
    int nr_vecini_vii;
    int stare_viu = 1, stare_dead = 0;
        for (int i = 0; i < lini; i++)
        {
            for (int j = 0; j < coloane; j++)
            {
                verificare_celule_vecine(matrice, i, j, lini, coloane, &nr_vecini_vii);
    
                if (matrice[i][j] == 'X')
                {
                    if (nr_vecini_vii < conditie1_vii || nr_vecini_vii > conditie2_vii)
                                 adaugare_elem_lista1(&new,i,j);
                }
                else if (nr_vecini_vii == conditie1_dead)
                        adaugare_elem_lista1(&new,i,j);
                 
          }
     }
     return new;
}

void scriere_stiva_in_fisier(Stiva1 *top, FILE *fisier_output, int generatie)
{
    Lista1 *iter = NULL;
    fprintf(fisier_output, "%d", generatie);
    iter = top->head_list;
    while (iter != NULL)
    {   
        fprintf(fisier_output, " %d %d", iter->linie, iter->coloana);
        iter = iter->next;
    }
    fprintf(fisier_output, "\n");
}
