#include "bonus2_liste.h"

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

void creare_stiva(char ***matrice,int lini,int coloane,int nr_generatii,char **argv,Stiva1 **top)
{
     Lista1 *head = generare_lista_modificari(*matrice,lini,coloane);
     FILE *fisier_output = NULL;
     verificare_alocare(fisier_output = fopen(argv[2],"wt"));

     int nr_generatie = 1;
     push_stiva1(top,head);
     scriere_stiva_in_fisier(*top,fisier_output,nr_generatie);

     while(nr_generatie < nr_generatii)
     {
        nr_generatie++;
        Lista1 *lst = (*top)->head_list;
        while(lst != NULL)
        {
            if((*matrice)[lst -> linie][lst -> coloana] == 'X')
                (*matrice)[lst -> linie][lst -> coloana] = '+';
            else 
                (*matrice)[lst -> linie][lst ->coloana] = 'X';
            lst = lst -> next;
        }
        head = generare_lista_modificari(*matrice,lini,coloane);
        push_stiva1(top,head);
        scriere_stiva_in_fisier(*top,fisier_output,nr_generatie);
     }
     eliberare_mem_matrice1(matrice,lini);
     fclose(fisier_output);
}

int main(int argc,char **argv)
{
    Stiva1 *top = NULL;
    char **matrice = NULL;
    int nr_generatii, lini, coloane, nr_task;
    citire_date(&matrice,&nr_task,&nr_generatii,&lini,&coloane,argv);
    //if(nr_task == 2)
    creare_stiva(&matrice,lini,coloane,nr_generatii,argv,&top);
    eliberare_memorie_stiva1(&top);
}