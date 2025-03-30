#include "my_algoritms.h"

//task1 

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

void modificare_si_scriere_matrice(char ***matrice,char **matrice_modificata,int lini,FILE *fisier_output)
{
    for (int i = 0; i < lini; i++)
    {
        fprintf(fisier_output, "%s", matrice_modificata[i]);
        strcpy((*matrice)[i], matrice_modificata[i]);
        fprintf(fisier_output, "\n");
    }
}

