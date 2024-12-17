/**
 * @file tests_circuit.c
 * @author Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Ensemble des tests unitaire concernant le fichier list_circuit.c
 * @version 1.0
 * @date 29/11/2023
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
*/

/*************************** FICHIERS D'ENTÊTE ***************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/csv.h"
#include "../src/list_circuit.h"



/*************************** MAIN ***************************/

/**
 * @brief Fonction main du programme de tests vérifiant les résultats des fonctions de list_circuit
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */


int main(int argc, char const *argv[])
{
    List *liste = extractCSVFile("./fichiers/ballots_va.csv");
    printf("le fichier a été extrait\n");
    mat_duel* matrice = genererMatDuel(liste);
    afficherMat(matrice);
    printf("\n");
    mat_duel *mat = resDuelsMatrice(matrice);
    afficherMat(mat);

    list_arc *graph = grapheTournoi(mat);
    printf("fabrication du graphe\n");

    affichageListArc(graph);


    return 0;
}
