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

    eliberare_mem_matrice(matrice, lini);
    eliberare_mem_matrice(&matrice_modificata, lini);

    fclose(fisier_output);
}

void generare_arbore_recursiv(char **matrice, Node *root, int lini, int coloane, int nr_generatii, FILE *fisier_output)
{
    if (root != NULL && nr_generatii > 0)
    {
        char **matrice_regula_B = NULL, **matrice_regula_initiala = NULL;

        alocare_memorie_matrice(&matrice_regula_B, lini, coloane);
        alocare_memorie_matrice(&matrice_regula_initiala, lini, coloane);

        int nr_vecini_vii = 0, transformare_regula_initiala;
        int conditie1_vii = 2, conditie2_vii = 3, conditie1_dead = 3;
        int conditie_B = 2, transformare_regula_B;

        Lista *lst_initial = NULL, *lst_regula_B = NULL;

        for (int i = 0; i < lini; i++)
        {
            for (int j = 0; j < coloane; j++)
            {
                transformare_regula_initiala = 0;
                transformare_regula_B = 0;

                verificare_celule_vecine(matrice, i, j, lini, coloane, &nr_vecini_vii);
                if (matrice[i][j] == 'X')
                {
                    if (nr_vecini_vii < conditie1_vii)
                        matrice_regula_initiala[i][j] = '+', transformare_regula_initiala++;
                    else if (nr_vecini_vii > conditie2_vii)
                        matrice_regula_initiala[i][j] = '+', transformare_regula_initiala++;
                    else
                        matrice_regula_initiala[i][j] = 'X';
                    matrice_regula_B[i][j] = 'X';
                }
                else
                {
                    if (nr_vecini_vii == conditie1_dead)
                        matrice_regula_initiala[i][j] = 'X', transformare_regula_initiala++;
                    else
                        matrice_regula_initiala[i][j] = '+';

                    if (nr_vecini_vii == conditie_B)
                        matrice_regula_B[i][j] = 'X', transformare_regula_B++;
                    else
                        matrice_regula_B[i][j] = '+';
                }
                if (transformare_regula_B)
                {
                    if (lst_regula_B == NULL)
                        creare_lista(&lst_regula_B, i, j);
                    else
                        adaugare_elem_lista(lst_regula_B, i, j);
                }
                if (transformare_regula_initiala)
                {
                    if (lst_initial == NULL)
                        creare_lista(&lst_initial, i, j);
                    else
                        adaugare_elem_lista(lst_initial, i, j);
                }
            }
        }
        nr_generatii--;

        scriere_matrice_nod_in_fisier1(matrice_regula_B, lini, fisier_output);
        root->left = createNode(lst_regula_B);
        generare_arbore_recursiv(matrice_regula_B, root->left, lini, coloane, nr_generatii, fisier_output);

        scriere_matrice_nod_in_fisier1(matrice_regula_initiala, lini, fisier_output);
        root->right = createNode(lst_initial);
        generare_arbore_recursiv(matrice_regula_initiala, root->right, lini, coloane, nr_generatii, fisier_output);

        eliberare_mem_matrice(&matrice_regula_B, lini);
        eliberare_mem_matrice(&matrice_regula_initiala, lini);
    }
}

int main(int argc, char **argv)
{
    Stiva *top = NULL;
    char **matrice = NULL;
    int nr_task = 0, lini = 0, coloane = 0, nr_generatii = 0;
     
    citire_date(&matrice, &nr_task, &nr_generatii, &lini, &coloane, argv);

    if (nr_task == 1 || nr_task == 2)
    {
        generare_matrici(&matrice, lini, coloane, nr_generatii, argv, nr_task, &top);

        if (nr_task == 2)
            eliberare_memorie_stiva(&top);
    }

    if (nr_task == 3)
    {
        Node *root = NULL, *root1 = NULL;
        FILE *fisier_output = NULL;

        verificare_alocare(fisier_output = fopen(argv[2], "wt"));

        root = create_Root(matrice, lini, coloane, fisier_output);
        root1 = root;

        generare_arbore_recursiv(matrice, root1, lini, coloane, nr_generatii, fisier_output);

        fclose(fisier_output);
        eliberare_mem_arbore(&root);
        eliberare_mem_matrice(&matrice, lini);
    }
}
