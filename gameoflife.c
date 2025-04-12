#include "my_algoritms.h"

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
void generare_matrici(char ***matrice, int lini, int coloane, int nr_generatii, char **argv, int nr_task, Stiva **top)
{
    FILE *fisier_output = NULL;
    verificare_alocare(fisier_output = fopen(argv[2], "wt"));
    if (nr_task == 1)
    {
        for (int i = 0; i < lini; i++)
        {
            fprintf(fisier_output, "%s", (*matrice)[i]);
            fprintf(fisier_output, "\n");
        }
        fprintf(fisier_output, "\n");
    }

    int nr_vecini_vii = 0;
    int conditie1_vii = 2, conditie2_vii = 3, conditie1_dead = 3;
    char **matrice_modificata = NULL;
    int generatie_curenta = 0, transformare;
    alocare_memorie_matrice(&matrice_modificata, lini, coloane);

    while (generatie_curenta < nr_generatii)
    {
        Lista *lst = NULL;
        for (int i = 0; i < lini; i++)
        {
            for (int j = 0; j < coloane; j++)
            {
                verificare_celule_vecine(*matrice, i, j, lini, coloane, &nr_vecini_vii);
                transformare = 0;
                if ((*matrice)[i][j] == 'X')
                {
                    if (nr_vecini_vii < conditie1_vii)
                        matrice_modificata[i][j] = '+', transformare++;
                    else if (nr_vecini_vii > conditie2_vii)
                        matrice_modificata[i][j] = '+', transformare++;
                    else
                        matrice_modificata[i][j] = 'X';
                }
                else
                {
                    if (nr_vecini_vii == conditie1_dead)
                        matrice_modificata[i][j] = 'X', transformare++;
                    else
                        matrice_modificata[i][j] = '+';
                }
                if (nr_task == 2)
                {
                    if (transformare)
                    {
                        if (lst == NULL)
                        {
                            creare_lista(&lst, i, j);
                            push_stiva(top, lst);
                        }
                        else
                            adaugare_elem_lista(lst, i, j);
                    }
                }
            }
        }
        if (nr_task == 1)
        {
            scriere_matrice_in_fisier(matrice, matrice_modificata, lini, fisier_output);
            fprintf(fisier_output, "\n");
        }
        else if (nr_task == 2)
            scriere_stiva_in_fisier(*top, fisier_output, generatie_curenta + 1);

        modificare_matrice(matrice, matrice_modificata, lini);
        generatie_curenta++;
    }
    for (int i = 0; i < lini; i++)
        free((*matrice)[i]), free(matrice_modificata[i]);
    free(*matrice);
    free(matrice_modificata);
    fclose(fisier_output);
}
int main(int argc, char **argv)
{
    Stiva *top = NULL;
    char **matrice = NULL;
    int nr_task = 0, lini = 0, coloane = 0, nr_generatii = 0;
    citire_date(&matrice, &nr_task, &nr_generatii, &lini, &coloane, argv);
    generare_matrici(&matrice, lini, coloane, nr_generatii, argv, nr_task, &top);
    if (nr_task == 2)
       eliberare_memorie_stiva(&top);
}
