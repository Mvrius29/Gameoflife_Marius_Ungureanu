#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//task1
void verificare_alocare(const void  *p);
void alocare_memorie_matrice(char ***matrice,int lini,int coloane);
int verificare_indici(int linie, int coloana, int nr_linii, int nr_coloane);
void verificare_vecin(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void verificare_celule_vecine(char **matrice, int linie, int coloana, int nr_linii, int nr_coloane, int *vii);
void modificare_si_scriere_matrice(char ***matrice,char **matrice_modificata,int lini,FILE *fisier_output);
