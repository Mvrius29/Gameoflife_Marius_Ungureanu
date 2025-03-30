#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void generare_matrici(char ***matrice, int lini, int coloane, int *nr_generatii, char **argv)
{
    FILE *fisier_output=NULL;
    verificare_alocare(fisier_output = fopen(argv[2], "wt"));
    for (int i = 0; i < lini; i++)
    {
        fprintf(fisier_output, "%s", (*matrice)[i]);
        fprintf(fisier_output, "\n");
    }
    fprintf(fisier_output, "\n");

    int nr_vecini_vii = 0;
    int conditie1_vii = 2, conditie2_vii = 3, conditie1_dead = 3;
    char **matrice_modificata = NULL;

    alocare_memorie_matrice(&matrice_modificata, lini, coloane);

    while (*nr_generatii > 0)
    {
        for (int i = 0; i < lini; i++)
        {
            for (int j = 0; j < coloane; j++)
            {
                verificare_celule_vecine(*matrice, i, j, lini, coloane, &nr_vecini_vii);

                if ((*matrice)[i][j] == 'X')
                {
                    if (nr_vecini_vii < conditie1_vii)
                        matrice_modificata[i][j] = '+';
                    else if (nr_vecini_vii > conditie2_vii)
                        matrice_modificata[i][j] = '+';
                    else
                        matrice_modificata[i][j] = 'X';
                }
                else
                {
                    if (nr_vecini_vii == conditie1_dead)
                        matrice_modificata[i][j] = 'X';
                    else
                        matrice_modificata[i][j] = '+';
                }
            }
        }
        modificare_si_scriere_matrice(matrice,matrice_modificata,lini,fisier_output);
        (*nr_generatii)--;
        fprintf(fisier_output, "\n");
    }
    for (int i = 0; i < lini; i++)
        free((*matrice)[i]), free(matrice_modificata[i]);
    free(*matrice);
    free(matrice_modificata);
    fclose(fisier_output);
}
int main(int argc, char **argv)
{

    char **matrice = NULL;
    int nr_task = 0, lini = 0, coloane = 0, nr_generatii = 0;
    citire_date(&matrice, &nr_task, &nr_generatii, &lini, &coloane, argv);
    if (nr_task == 1)
        generare_matrici(&matrice, lini, coloane, &nr_generatii, argv);
}
