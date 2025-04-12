#include "bonus_2.h"

void verificare_alocare(const void *p)
{
    if (p == NULL)
    {
        puts("EROARE");
        exit(1);
    }
}
void alocare_memorie_matrice(char ***matrice, int lini, int coloane)
{
    *matrice = (char **)malloc(lini * sizeof(char *));
    if (*matrice == NULL)
    {
        puts("Nu s a putut aloca spatiu");
        exit(1);
    }
    for (int j = 0; j < (lini); j++)
    {
        (*matrice)[j] = malloc(coloane * sizeof(char));
        if ((*matrice)[j] == NULL)
        {
            puts("Nu s a putut aloca spatiu");
            exit(1);
        }
    }
}

void creare_lista(Lista **lst, int linie, int coloana)
{
    (*lst) = malloc(sizeof(Lista));
    verificare_alocare(*lst);
    (*lst)->linie = linie;
    (*lst)->coloana = coloana;
    (*lst)->next = NULL;
}

void adaugare_elem_lista(Lista *lst, int linie, int coloana)
{

    Lista *new = malloc(sizeof(Lista));
    verificare_alocare(new);
    new->linie = linie;
    new->coloana = coloana;
    new->next = NULL;
    Lista *aux = lst;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new;
}

void push_stiva(Stiva **top, Lista *lst)
{
        Stiva *nod = malloc(sizeof(Stiva));
        verificare_alocare(nod);
        nod->head_list = lst;
        (nod)->next = (*top);
        (*top) = nod;
}

int isEmpty(Stiva const *top)
{
    return top==NULL;
}
Lista* pop_stiva(Stiva **top)
{      
      if(isEmpty(*top))
         return NULL;
      Stiva *iter=NULL;
      Lista *aux=NULL;
      aux=(*top)->head_list;
      iter=(*top);
      (*top)=(*top)->next;
      free(iter);
      return aux;

}
void scriere_matrice_in_fisier(char **matrice,int lini,FILE *fisier_output)
{
    for (int i = 0; i < lini; i++)
    {
        fprintf(fisier_output, "%s", matrice[i]);
        fprintf(fisier_output, "\n");
    }
}