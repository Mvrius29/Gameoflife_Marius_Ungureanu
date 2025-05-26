#include "my_algoritms.h"

// Task 1 + 2
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
                            adaugare_elem_lista(&lst, i, j);
                            push_stiva(top, lst);
                        }
                        else
                            adaugare_elem_lista(&lst, i, j);
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

    eliberare_mem_matrice_char(matrice, lini);
    eliberare_mem_matrice_char(&matrice_modificata, lini);

    fclose(fisier_output);
}

/// Crearea arborerului pentru task 3 si task 4
void generare_arbore_recursiv(char **matrice, Node *root, int lini, int coloane, int nr_generatii, FILE *fisier_output)
{
    if (root != NULL && nr_generatii > 0)
    {
        char **matrice_regula_B = NULL, **matrice_regula_initiala = NULL;

        alocare_memorie_matrice(&matrice_regula_B, lini, coloane);
        alocare_memorie_matrice(&matrice_regula_initiala, lini, coloane);

        int nr_vecini_vii = 0;
        int conditie1_vii = 2, conditie2_vii = 3, conditie1_dead = 3;
        int conditie_B = 2;

        Lista *lst_initial = NULL, *lst_regula_B = NULL;

        for (int i = 0; i < lini; i++)
        {
            for (int j = 0; j < coloane; j++)
            {

                verificare_celule_vecine(matrice, i, j, lini, coloane, &nr_vecini_vii);
                if (matrice[i][j] == 'X')
                {
                    if (nr_vecini_vii < conditie1_vii || nr_vecini_vii > conditie2_vii)
                    {
                        matrice_regula_initiala[i][j] = '+';
                        adaugare_elem_lista(&lst_initial, i, j);
                    }
                    else
                        matrice_regula_initiala[i][j] = 'X';
                    matrice_regula_B[i][j] = 'X';
                }
                else
                {
                    if (nr_vecini_vii == conditie1_dead)
                        matrice_regula_initiala[i][j] = 'X', adaugare_elem_lista(&lst_initial, i, j);
                    else
                        matrice_regula_initiala[i][j] = '+';

                    if (nr_vecini_vii == conditie_B)
                        matrice_regula_B[i][j] = 'X', adaugare_elem_lista(&lst_regula_B, i, j);
                    else
                        matrice_regula_B[i][j] = '+';
                }
            }
        }
        nr_generatii--;

        root->left = createNode(lst_regula_B);
        generare_arbore_recursiv(matrice_regula_B, root->left, lini, coloane, nr_generatii, fisier_output);

        root->right = createNode(lst_initial);
        generare_arbore_recursiv(matrice_regula_initiala, root->right, lini, coloane, nr_generatii, fisier_output);

        eliberare_mem_matrice_char(&matrice_regula_B, lini);
        eliberare_mem_matrice_char(&matrice_regula_initiala, lini);
    }
}

/// task3 scriere in fisier
void preordine(Node *root, char **matrice, int lini, int coloane, FILE *fisier_output, int cnt)
{
    if (root == NULL)
        return;
    if (cnt == 0)
    {
        cnt++;
        preordine(root->left, matrice, lini, coloane, fisier_output, cnt);
        preordine(root->right, matrice, lini, coloane, fisier_output, cnt);
    }
    else
    {
        char **matrice_modificata = genereare_matrice_nod(matrice, lini, coloane, root);
        scriere_matrice_nod_in_fisier1(matrice_modificata, lini, fisier_output);

        preordine(root->left, matrice_modificata, lini, coloane, fisier_output, cnt);
        preordine(root->right, matrice_modificata, lini, coloane, fisier_output, cnt);

        eliberare_mem_matrice_char(&matrice_modificata, lini);
    }
}
/// task 4
void determinare_drumuri_hamiltoniene(Node *root, char **matrice, int lini, int coloane, FILE *fisier_output, int cnt)
{
    if (root == NULL)
        return;
    if (cnt == 0)
    {
        scriere_drum_hamiltonian_in_fisier(matrice, lini, coloane, fisier_output);
        cnt++;

        determinare_drumuri_hamiltoniene(root->left, matrice, lini, coloane, fisier_output, cnt);
        determinare_drumuri_hamiltoniene(root->right, matrice, lini, coloane, fisier_output, cnt);
    }
    else
    {
        char **matrice_modificata = genereare_matrice_nod(matrice, lini, coloane, root);
        scriere_drum_hamiltonian_in_fisier(matrice_modificata, lini, coloane, fisier_output);

        determinare_drumuri_hamiltoniene(root->left, matrice_modificata, lini, coloane, fisier_output, cnt);
        determinare_drumuri_hamiltoniene(root->right, matrice_modificata, lini, coloane, fisier_output, cnt);

        eliberare_mem_matrice_char(&matrice_modificata, lini);
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

    if (nr_task == 3 || nr_task == 4)
    {
        Node *root = NULL, *root1 = NULL;
        FILE *fisier_output = NULL;
        int cnt = 0;

        verificare_alocare(fisier_output = fopen(argv[2], "wt"));

        root = create_Root(matrice, lini, coloane, fisier_output);
        root1 = root;

        generare_arbore_recursiv(matrice, root1, lini, coloane, nr_generatii, fisier_output);
        if (nr_task == 3)
            preordine(root, matrice, lini, coloane, fisier_output, cnt);
        else
            determinare_drumuri_hamiltoniene(root1, matrice, lini, coloane, fisier_output, cnt);

        fclose(fisier_output);
        eliberare_mem_arbore(&root);
        eliberare_mem_matrice_char(&matrice, lini);
    }
}
