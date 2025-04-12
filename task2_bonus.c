#include "bonus_2.h"

void citire_date(char ***matrice, int *nr_task, int *nr_generatii, int *lini, int *coloane, char **argv,Stiva **top)
{
    int contor_linie_matrice = 0; // contor pentru a stii pe ce linie vom introduce sirul citit din fisier pentru matrice
    FILE *fisier_input = NULL;
    verificare_alocare(fisier_input = fopen(argv[1], "rt"));
    fscanf(fisier_input, "%d", nr_task);
    fscanf(fisier_input, "%d%d", lini, coloane);
    fgetc(fisier_input);

    alocare_memorie_matrice(matrice, *lini, *coloane);
    int cnt = *lini;
    while (cnt>0)
    {
        fscanf(fisier_input, "%150s", (*matrice)[contor_linie_matrice]);
        contor_linie_matrice++;
        cnt--;
    }
    int linie,coloana;
    char *sir;
    sir=malloc(150*sizeof(char));
    verificare_alocare(sir);
    fgets(sir,150,fisier_input);//aceata linie e petru a trece pe utmatorul rand dupa ce se finalizaza citirea matricei
    while( fgets(sir,150,fisier_input)!=NULL)
    {
        Lista *lst=NULL;
        int poz=0;
        while(poz<strlen(sir))
        {
            poz+=2;
            linie=sir[poz]-'0';
            poz+=2;
            coloana=sir[poz]-'0';
            if(lst==NULL)
            {
                creare_lista(&lst,linie,coloana);
                push_stiva(top,lst);
            }
            else
               adaugare_elem_lista(lst,linie,coloana);
        }
        (*nr_generatii)++;
    }
    free(sir);
    fclose(fisier_input);
}

void generare_matrice_initiala(char ***matrice, int lini, int coloane, int nr_generatii, char **argv, Stiva **top)
{

    FILE *fisier_output;
    verificare_alocare(fisier_output = fopen(argv[2], "wt"));
    char **matrice_modificata = NULL;
    alocare_memorie_matrice(&matrice_modificata, lini, coloane);
    while ( nr_generatii >0)
    {
        Lista *lst = pop_stiva(top);
        while(lst!=NULL)
        {  
            Lista *aux=lst;
           if((*matrice)[lst->linie][lst->coloana]=='X')
            (*matrice)[lst->linie][lst->coloana]='+';
            else
            (*matrice)[lst->linie][lst->coloana]='X';
            lst=lst->next;
            free(aux);
            aux=NULL;
        }
        nr_generatii--;
    }
    scriere_matrice_in_fisier(*matrice,lini,fisier_output);
    for (int i = 0; i < lini; i++)
        free((*matrice)[i]);
    free(*matrice);
    fclose(fisier_output);
}
int main(int argc, char **argv)
{
    Stiva *top = NULL;
    char **matrice = NULL;
    int nr_task = 0, lini = 0, coloane = 0, nr_generatii = 0;
    citire_date(&matrice, &nr_task, &nr_generatii, &lini, &coloane, argv,&top);
    if(nr_task==2)
    generare_matrice_initiala(&matrice,lini,coloane,nr_generatii,argv,&top);
}