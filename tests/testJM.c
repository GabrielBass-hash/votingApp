/**
 * @file testJM.c
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief Module de test du jugement majoritaire
 * @version 1.0
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/JugementMajoritaire.h"


/*************************** DÉFINITIONS DES FONCTIONS ***************************/

void testTrieTableau(){
    int tab[7] = {0,50,4,7,9,5,1};
    printf("tableau avant trie \n");
    for(int i = 0;i<7;i++){
        printf(" %d :: %d \n",i,tab[i]);
    }
    printf("tableau aprés trie \n");
    trierTableau(tab,7);
    for(int i = 0;i<7;i++){
        printf("%d :: %d \n",i,tab[i]);
    }
}

void testTrieTableau2(){
    int tab[8] = {0,50,4,7,9,5,1,50};
    printf("tableau avant trie \n");
    for(int i = 0;i<8;i++){
        printf(" %d :: %d \n",i,tab[i]);
    }
    printf("tableau aprés trie \n");
    trierTableau(tab,8);
    for(int i = 0;i<8;i++){
        printf("%d :: %d \n",i,tab[i]);
    }
}

/*************************** MAIN ***************************/

int main(int argc,char* argv[]){
    printf("Test 1 \n");
	testTrieTableau();
    printf("Test 2 \n");
	testTrieTableau2();
    //printf("Test 3 \n");
}  