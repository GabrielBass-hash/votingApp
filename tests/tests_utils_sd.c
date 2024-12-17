/**
 * @file tests_utils_sd.c
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * @brief Module de test des fonctions utilitaires
 * @version 1.0
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/*************************** FICHIERS D'ENTÊTE ***************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

#include "../src/utils_sd.h"
#include "../src/csv.h"

/*************************** DÉFINITONS DES FONCTIONS ***************************/

/**
 * @brief tests de fonctionnement de la fonction aleatoire
 * 
 */
void testAleatoire(){
	printf("Un nombre entre 0 et 2 : %d\n",aleatoire(2));
	printf("Un nombre entre 0 et 2 : %d\n",aleatoire(2));
	printf("Un nombre entre 0 et 2 : %d\n",aleatoire(2));
	printf("Un nombre entre 0 et 2 : %d\n",aleatoire(2));
}

/**
 * @brief tests de fonctionnement de la fonction min
 * 
 */
void testMin(){
    int tab[4] = {5,-1,9,6};
    printf("Le chiffre doit etre 5 : %d\n",min(tab,4));
    tab[1] = 1;
    printf("Le chiffre doit etre 1 : %d\n",min(tab,4));
}

/*************************** MAIN ***************************/

/**
 * @brief fonction principale du programme de tests vériiant le bon fonctionnement des méthodes 
 *         du module utilitaire.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char* argv[]){
    printf("TEST ALEATOIRE :\n");
    testAleatoire();
    printf("\nTEST MIN :\n");
    testMin();

    List* l = extractCSVFile("./fichiers/vote100.csv");
    mat_duel* matDuel = genererMatDuel(l);
    afficherMat(matDuel);
    printf("%d\n",vainqueurCondorcet(matDuel));

    return 0;
}