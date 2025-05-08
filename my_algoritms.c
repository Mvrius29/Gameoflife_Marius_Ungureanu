#include "my_algoritms.h"

//Task1 

void verificare_alocare(const void  *p)
{
    if(p==NULL)
     {
        puts("EROARE");
        exit(1);
     }
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

void scriere_matrice_in_fisier(char ***matrice,char **matrice_modificata,int lini,FILE *fisier_output)
{
    for (int i = 0; i < lini; i++)
    {
        fprintf(fisier_output, "%s", matrice_modificata[i]);
        strcpy((*matrice)[i], matrice_modificata[i]);
        fprintf(fisier_output, "\n");
    }
}

void modificare_matrice(char ***matrice,char **matrice_modificata,int lini)
{
    for (int i = 0; i < lini; i++)
        strcpy((*matrice)[i], matrice_modificata[i]);
}

//Task2 algoritimi necesari pentru liste si stiva

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

void scriere_stiva_in_fisier(Stiva *top, FILE *fisier_output, int generatie)
{
    Lista *iter = NULL;
    fprintf(fisier_output, "%d", generatie);
    iter = top->head_list;
    while (iter != NULL)
    {   
        fprintf(fisier_output, " %d %d", iter->linie, iter->coloana);
        iter = iter->next;
    }
    fprintf(fisier_output, "\n");
}


void eliberare_mem_lista(Lista **lst)
{
    Lista *aux = NULL;
    
    while((*lst) != NULL)
    {
        aux = (*lst);
        (*lst) = (*lst) ->next;
        free(aux);
        aux = NULL;
    }
}

void eliberare_memorie_stiva(Stiva **top)
{
    Stiva *iter=NULL;
    Lista *aux=NULL;
    while((*top)!=NULL)
    {
        iter=(*top);
        aux=iter->head_list;
        eliberare_mem_lista(&aux);
        (*top)=(*top)->next;
        free(iter);
        iter=NULL;
    }
}

///Task3 functii necesare

Node* createNode(Lista *lst)
{
    Node *new = malloc(sizeof(Node));
    verificare_alocare(new);
    
    new->head_list = lst;
    new->left = new->right=NULL;
    return new;
}

Node *create_Root(char **matrice, int lini, int coloane, FILE *fisier_output)
{
    Lista *lst = NULL;
    Node *root = NULL;
    for (int i = 0; i < lini; i++)
    {
        for (int j = 0; j < coloane; j++)
        {
            if (matrice[i][j] == 'X')
            {
                if (lst == NULL)
                   {
                    creare_lista(&lst,i,j);
                    root = createNode(lst);
                   }
                else
                    adaugare_elem_lista(root->head_list, i, j);
            }
        }
        fprintf(fisier_output, "%s\n", matrice[i]);
    }
    fprintf(fisier_output,"\n");
    return root;
}

void scriere_matrice_nod_in_fisier1(char **matrice,int lini,FILE *fisier_output)
{
    for (int i = 0; i < lini; i++)
        fprintf(fisier_output, "%s\n",matrice[i]);
    fprintf(fisier_output,"\n");
}

void eliberare_mem_matrice(char ***matrice,int lini)
{
    for(int i=0;i<lini;i++)
      free((*matrice)[i]);
    free(*matrice);
}


void eliberare_mem_arbore(Node **root)
{
    if((*root) != NULL)
    {
        eliberare_mem_arbore(&(*root)->left);
        eliberare_mem_arbore(&(*root)->right); 

        Lista *aux = (*root)->head_list;
        eliberare_mem_lista(&aux);
        free((*root));
        (*root) = NULL;      
    }
}

