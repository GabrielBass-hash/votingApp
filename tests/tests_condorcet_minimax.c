/**
 * @file tests_condorcet_minimax.c
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * @brief Module de test des fonctions en lien avec le scrutin condorcet minimax
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/condorcet_minimax.h"

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

/**
 * @brief Fonciton de tests sur miniVote
 * 
 */
void testMiniVote(){
    int tab[4]={20,3,15,30};
    printf("Le mini est 3 : %d\n",miniVote(tab,0,4));
    printf("Le mini est 15 : %d\n",miniVote(tab,1,4));
}

/**
 * @brief Fonction de test sur votesMaximum
 * 
 */
void testVotesMaximun(){
    int tab[4]={20,3,15,30};
    printf("Le maximun est 30 : %d\n",votesMaximun(tab,4));
    tab[3] = 0;
    printf("Le maximun est 20 : %d\n",votesMaximun(tab,4));
    tab[1] = 40;
    printf("Le maximun est 40 : %d\n",votesMaximun(tab,4));
}

/**
 * @brief Fonnction de test sur condorcet minimax
 * 
 */
void testCondorcetMinimax(){
    List *l = extractCSVMat("./fichiers/calcul1.csv");
    mat_duel *matD = copieMatDuel(l);
    condorcetMinimax(matD);
}

/*************************** MAIN ***************************/

/**
 * @brief Fonction principale du programme de test vérifiant le fonctionnant des sous-fonctions
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char* argv[]){
    testMiniVote();
    testVotesMaximun();
    testCondorcetMinimax();
    return 0;
}