# Game of life

## What is this about?
This program implemets the gameoflife according to the base rule of the  game and , at the same time, according to a new rule.

With the help of tasks 1 and 2 the program generates the corresponding matrix for certain generations, according to the game rule, using both matrices and a stack of lists. 

In task 3, the new rule is introduced and a tree is created according to the following rule: the left child will have the matrix generated according to the new rule, and the right child according to the basic game rule.

The last task searches for each matrix in the tree the longest Hamiltonian path that can be found, which passes only through the live nodes, and then displays it, displaying for each element the row and column.

The whole documentation for this ideea canbe found [here](https://site-pa.netlify.app/proiecte/game_of_life/).

## How to run the project?
In the Makefile are all the commands that you need to  run the program. You just need install the file, and after just call in terminal the commands:
- First
```bash
make build
```
- After
```bash
make run
```
- Or you can run the comand mannualy following the next steps:
```bash
1 -> gcc gameoflife.c my_algoritms.c my_algoritms.h -o a.out
2 -> ./a.out file.in file.out
```
and after you will see the results in file.out. ( file.in needs to have the input that in the form that is specified in the site above)

## Data types used
- List
```bash
  typedef struct lista
{
    int linie;
    int coloana;
    struct lista *next;
} Lista;
  ```
- Stack
```bash
typedef struct stiva
{
    Lista *head_list;
    struct stiva *next;
} Stiva;
```
- Node from the tree
```bash
typedef struct arbore
{
    Lista *head_list;
    struct arbore *left, *right;
}Node;
```
- Struct for nodes position
```bash
typedef struct pozitinoduri
{
    int linie;
    int coloana;
    int node;
    int componenta;
    int elem_componenta;

} PozitiNoduri;
```

## Functions

```bash
citire_date                       #read the input from the file.in
alocare_memorie_matrice           #allocate memory for char matrix
alocare_memorie_matrice_int       #allocate memory for a int matrix
verificare_indici(int linie, int coloana, int nr_linii, int nr_coloane);
verificare_vecin                 |
verificare_celule_vecine         |  # thse 3 funtions are used to number the live neigbours of an element from matrix  
scriere_matrice_in_fisier        |
modificare_matrice                #copy a matrix in another matrix
adaugare_elem_lista               #add an element into a list
push_stiva                        #add a list into a stack
scriere_stiva_in_fisier           #write the stack in file.out
createNode                        #create a node for the tree
create_Root                       #create the root for the tree
genereare_matrice_nod             #generates the matrix for a nod of the tree using the list that is memorised in it
generare_arbore_recursiv          #generates the whole tree
preordine                         #write the tree in file.out
determinare_nr_celule_vii         #number the live neighbours of an element
generare_matrice_noduri           #generattes the nodes number matrix based on the matrix with 'X' and '+'
verificare_conexiune             |
creare_muchii_graf               | # these are used to generates the adjunct matrx based on the nodes number matrix
creare_matrice_de_adiacenta      |
determinare_componenta_conexa    #find and mark the related components of the graph ,that is composed by the live elements of every matrix
determinare_drum_hamiltonian     #find the hamiltonian path in an reaed component
cautare_drumuri                  #find the longest hamiltonian path from a nod
determinare_drumuri_hamiltoniene #find the longest hamiltonian path for every nod of the tree
```

## Bonuses
I make a bonus task for the task 2 ,which is described [here](https://site-pa.netlify.app/proiecte/game_of_life/) at Task2 .

The seccond bonus is an implementation that make the task2 without generating for every generation the matrix from the generation before, and just using the stack of lists to found for every generation the positions 
that are switching their status.

## Porblems
The probems appear at the task4 because it s not efficient, because the matrixe are and the number of nodes are bigger and the basic algoritm to find an hamiltonian path is not so efficient for a situation like this.
I still work on that i will come with updates.
