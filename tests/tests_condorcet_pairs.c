/**
 * @file tests_condorcet_pair.c
 * @author Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Module de test des fonctions en lien avec le scrutin condorcet pairs
 * @version 1.0
 * @date 2023-12-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/*************************** FICHIERS D'ENTÊTE ***************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../src/condorcet_pairs.h"
#include "../src/list_circuit.h"


/*************************** MAIN ***************************/

/**
 * @brief fonction principale de test, vérifiant étape par étape le bon
 *        fonctionnement de la méthode
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{   

    List *l2 = extractCSVMat("./fichiers/wiki_paires.csv");
    mat_duel *matD2 = copieMatDuel(l2);
    afficherMat(matD2);
    printf ("Test Vainqueur pour fichiers wiki_paires.csv : %d\n",vainqueurCondorcet(matD2));
    condorcetPair(matD2);

    printf("-------------------- \n");
     

    List *l3 = extractCSVMat("./fichiers/calcul1.csv");
    mat_duel *matD3 = copieMatDuel(l3);
    afficherMat(matD3);
    printf ("Test Vainqueur pour fichiers calcul1.csv : %d\n",vainqueurCondorcet(matD3));
    condorcetPair(matD3);
    list_delete(&l3);
    matrice_delete(&matD3);

    return 0;
}