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

void citire_date(char ***matrice, int *nr_task, int *nr_generatii, int *lini, int *coloane, char **argv)
{
    int contor_linie_matrice = 0;
    FILE *fisier_input = NULL;
    verificare_alocare(fisier_input = fopen(argv[1], "rt"));

    fscanf(fisier_input, "%d", nr_task);
    fscanf(fisier_input, "%d%d", lini, coloane);
    fscanf(fisier_input, "%d", nr_generatii);
    fgetc(fisier_input);

    alocare_memorie_matrice(matrice, *lini, *coloane);
    int cnt = *lini;
    while (cnt)
    {
        fscanf(fisier_input, "%150s", (*matrice)[contor_linie_matrice]);
        contor_linie_matrice++;
        cnt--;
    }
    fclose(fisier_input);
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

void adaugare_elem_lista(Lista **lst, int linie, int coloana)
{

    Lista *new = malloc(sizeof(Lista));
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
    Lista *aux = *lst;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new;
    }
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
                    adaugare_elem_lista(&lst, i, j);
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

void eliberare_mem_matrice_char(char ***matrice,int lini)
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

char **genereare_matrice_nod(char **matrice, int lini, int coloane, Node *root)
{
    char **matrice_modificata = NULL;
    alocare_memorie_matrice(&matrice_modificata, lini, coloane);
    Lista *lst = root->head_list;
    for (int i = 0; i < lini; i++)
        for (int j = 0; j < coloane; j++)
        {
            if (lst != NULL && lst->linie == i && lst->coloana == j)
            {
                if (matrice[i][j] == 'X')
                    matrice_modificata[lst->linie][lst->coloana] = '+';
                else
                    matrice_modificata[lst->linie][lst->coloana] = 'X';
                lst = lst->next;
            }
            else
                matrice_modificata[i][j] = matrice[i][j];
        }
    return matrice_modificata;
}

//Task 4 
void eliberare_mem_matrice_int(int ***matrice,int lini)
{
    for(int i=0;i<lini;i++)
      free((*matrice)[i]);
    free(*matrice);
}
void alocare_memorie_matrice_int(int ***matrice, int lini, int coloane)
{
    *matrice = (int **)malloc(lini * sizeof(int *));
    verificare_alocare(*matrice);
    for (int j = 0; j < (lini); j++)
    {
        (*matrice)[j] = malloc(coloane * sizeof(int));
        verificare_alocare((*matrice)[j]);
    }
}


int determinare_nr_celule_vii(char **matrice, int lini, int coloane)
{
    int nr = 0;
    for (int i = 0; i < lini; i++)
        for (int j = 0; j < coloane; j++)
            if (matrice[i][j] == 'X')
                nr++;
    return nr;
}

int **generare_matrice_noduri(char **matrice, int lini, int coloane, int nr_noduri, PozitiNoduri **vector)
{
    int **matrice_noduri = NULL;
    int cnt_noduri = 0;

    *vector = malloc(nr_noduri * sizeof(PozitiNoduri));
    alocare_memorie_matrice_int(&matrice_noduri, lini, coloane);

    for (int i = 0; i < lini; i++)
        for (int j = 0; j < coloane; j++)
        {
            if (matrice[i][j] == 'X')
            {
                matrice_noduri[i][j] = cnt_noduri;
                (*vector)[cnt_noduri].linie = i;
                (*vector)[cnt_noduri].coloana = j;
                (*vector)[cnt_noduri].node = cnt_noduri;

                cnt_noduri++;
            }
            else
                matrice_noduri[i][j] = -1;
        }
    return matrice_noduri;
}

void verificare_conexiune(int **matrice_noduri, int **matrice_adiacenta, int linie, int coloana, int linie_vecin, int coloana_vecin, int lini, int coloane)
{
    if (verificare_indici(linie_vecin, coloana_vecin, lini, coloane))
        if (matrice_noduri[linie_vecin][coloana_vecin] > -1)
        {
            matrice_adiacenta[matrice_noduri[linie][coloana]][matrice_noduri[linie_vecin][coloana_vecin]] = 1;
            matrice_adiacenta[matrice_noduri[linie_vecin][coloana_vecin]][matrice_noduri[linie][coloana]] = 1;
        }
}

void creare_muchii_graf(int **matrice, int **matrice_adiacenta, int linie, int coloana, int lini, int coloane)
{
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie - 1, coloana - 1, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie - 1, coloana, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie - 1, coloana + 1, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie, coloana - 1, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie, coloana + 1, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie + 1, coloana - 1, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie + 1, coloana, lini, coloane);
    verificare_conexiune(matrice, matrice_adiacenta, linie, coloana, linie + 1, coloana + 1, lini, coloane);
}

int **creare_matrice_de_adiacenta(int **matrice_noduri, int lini, int coloane, int numar_noduri)
{
    int **matrice_adiacenta = NULL;
    alocare_memorie_matrice_int(&matrice_adiacenta, numar_noduri, numar_noduri);

    for (int i = 0; i < lini; i++)
        for (int j = 0; j < coloane; j++)
        {
            if (matrice_noduri[i][j] > -1)
                creare_muchii_graf(matrice_noduri, matrice_adiacenta, i, j, lini, coloane);
        }
    return matrice_adiacenta;
}

void determinare_componenta_conexa(int nod, int **matrice_adiacenta, int nr_noduri, int *dim, int *vizitat, int nr_componenta, PozitiNoduri *vector)
{
    vizitat[vector[nod].node] = nr_componenta;
    vector[nod].componenta = nr_componenta;
    (*dim)++;
    for (int i = 0; i < nr_noduri; i++)
    {
        if (matrice_adiacenta[vector[nod].node][vector[i].node] == 1 && vizitat[vector[i].node] == 0)
            determinare_componenta_conexa(i, matrice_adiacenta, nr_noduri, dim, vizitat, nr_componenta, vector);
    }
}

void determinare_drum_hamiltonian(int nod, int **matrice_adiacenta, int dim_Max, int *gasit, int nr_noduri, int *dim, int *drum, int *vizitat, PozitiNoduri *vector)
{
    vizitat[vector[nod].node] = 1;

    drum[*dim] = vector[nod].node;
    (*dim)++;

    if ((*dim) == dim_Max)
    {
        (*gasit) = 1;
        return;
    }

    for (int i = 0; i < nr_noduri; i++)
    {
        if (matrice_adiacenta[drum[(*dim) - 1]][vector[i].node] == 1 && vizitat[vector[i].node] == 0)
        {
            determinare_drum_hamiltonian(i, matrice_adiacenta, dim_Max, gasit, nr_noduri, dim, drum, vizitat, vector);
        }
        if (*gasit == 1)
            return;
    }

    vizitat[vector[nod].node] = 0;
    (*dim)--;
}

void cautare_drumuri(int **matrice_adiacenta, int **matrice_noduri, int lini, int coloane, int nr_noduri, int **vec_max, int *MAX, PozitiNoduri *vector)
{

    int nr_componenta = 0;
    int *vizitat = malloc(nr_noduri * sizeof(int));
    verificare_alocare(vizitat);

    for (int i = 0; i < nr_noduri; i++)
        vizitat[vector[i].node] = 0;

    for (int i = 0; i < nr_noduri; i++)
    {
        if (vizitat[vector[i].node] == 0)
        {
            nr_componenta++;
            int dim_Max = 0;
            determinare_componenta_conexa(i, matrice_adiacenta, nr_noduri, &dim_Max, vizitat, nr_componenta, vector);

            for (int j = 0; j < nr_noduri; j++)
                if (vizitat[vector[j].node] == nr_componenta)
                    vector[j].elem_componenta = dim_Max;

            if ((*MAX) < dim_Max)
                 (*MAX) = dim_Max;
        }
    }

    (*vec_max) = malloc((*MAX) * sizeof(int));
    verificare_alocare(*vec_max);

    for (int i = 0; i < nr_noduri; i++)
    {
        if (vector[i].elem_componenta == (*MAX))
        {
            for (int j = 0; j < nr_noduri; j++)
                vizitat[vector[j].node] = 0;

            int size = 0, gasit = 0;
            int *drum = malloc((*MAX) * sizeof(int));
            verificare_alocare(drum);
            int ok = 0;

            determinare_drum_hamiltonian(vector[i].node, matrice_adiacenta, *MAX, &gasit, nr_noduri, &size, drum, vizitat, vector);
            if (gasit == 1 && ok == 0)
            {
                for (int j = 0; j < size;j++)
                    (*vec_max)[j] = drum[j];
                ok = 1;
            }
            free(drum);
        }
    }
    free(vizitat);
}

void scriere_drum_hamiltonian_in_fisier(char **matrice, int lini, int coloane, FILE *fisier_output)
{
    int *vec_max = NULL, MAX = -1;
    PozitiNoduri *vector = NULL;

    int nr_noduri = determinare_nr_celule_vii(matrice, lini, coloane);
    int **matrice_noduri = generare_matrice_noduri(matrice, lini, coloane, nr_noduri, &vector);
    int **matrice_adiacenta = creare_matrice_de_adiacenta(matrice_noduri, lini, coloane, nr_noduri);

    cautare_drumuri(matrice_adiacenta, matrice_noduri, lini, coloane, nr_noduri, &vec_max, &MAX, vector);

    if (MAX == -1)
        fprintf(fisier_output, "%d\n", MAX);
    else
    {
        fprintf(fisier_output, "%d\n", MAX - 1);
        for (int k = 0; k < MAX; k++)
        {
            int l = vector[vec_max[k]].linie;
            int c = vector[vec_max[k]].coloana;
            fprintf(fisier_output, "(%d,%d) ", l, c);
        }
        fprintf(fisier_output, "\n");
    }

    free(vector);
    free(vec_max);
    eliberare_mem_matrice_int(&matrice_noduri, lini);
    eliberare_mem_matrice_int(&matrice_adiacenta, nr_noduri);
}

