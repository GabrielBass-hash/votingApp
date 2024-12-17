/**
 * @file tests_uninominale.c
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief Module de test des fonctions en lien avec le scrutin uninominale
 * @version 0.1
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/uninominale.h"

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

void testVote1(){
	int tab[10] = {0,0,0,0,0,0,0,0,0,0};
	int res[10] = {0,0,0,0,0,0,0,0,0,0};
	vote1(tab,res,10);
	printf("Le tableau n'a pas changer : ");
	affTab(res,10);
	tab[0] = 1;
    vote1(tab,res,10);
	printf("Le tableau a incrementer l'indice 0 de 1 : ");
	affTab(res,10);
	tab[1] = 9;
    vote1(tab,res,10);
	printf("Le tableau a incrementer l'indice 0 de 1 : ");
	affTab(res,10);
	tab[2] = 1;
    vote1(tab,res,10);
	printf("Le tableau a incrementer l'indice 0 ou l'indice 2 de 1 : ");
	affTab(res,10);
}

void testIdRes1(){
	int tab[10] = {0,0,0,0,0,0,0,0,0,0};
	int res[2] = {0,0};
    indiceRes1(tab,res,10);
	printf("Le premier et le deuxieme sont aleatoire :");
	affTab(res,2);
	tab[0] = 10;
	tab[8] = 7;
	tab[5] = 6;
    indiceRes1(tab,res,10);
	printf("Le premier est le 0 et le deuxieme est 8 :");
	affTab(res,2);
}

void testVote2(){
	int tab[10] = {10,10,10,10,10,10,10,10,10,10};
	int indiceVotant[2] = {0,1};
	int nbVote[2] = {0,0};
	printf("Les votes sont a 0 : ");
	affTab(nbVote,2);
	tab[0] = 1;
	vote2(tab,indiceVotant,nbVote);
	printf("L'indice 0 est incrementer de 1 : ");
	affTab(nbVote,2);
	tab[0] = -1;
	tab[1] = -1;
    vote2(tab,indiceVotant,nbVote);
	printf("L'indice 0 ou l'indice 1 est incrementer de 1 : ");
	affTab(nbVote,2);
	tab[1] = 9;
    vote2(tab,indiceVotant,nbVote);
	printf("L'indice 1 est incrementer de 1 : ");
	affTab(nbVote,2);
}

void testIdRes2(){
	int res;
	int indiceVotant[2] = {0,1};
	int nbVote[2] = {0,0};
	res = indiceRes2(nbVote,indiceVotant);
	printf("On a res egale a 0 ou 1 : %d\n",res);
	nbVote[0] = 5;
	res = indiceRes2(nbVote,indiceVotant);
	printf("On a res egale a 0 : %d\n",res);
}

/*************************** MAIN ***************************/

int main(int argc,char* argv[]){
	printf("TEST VOTE 1 :\n");
	testVote1();
	printf("\nTEST ID RES 1 :\n");
	testIdRes1();
	printf("\nTEST VOTE 2 :\n");
	testVote2();
	printf("\nTEST ID RES 2 :\n");
	testIdRes2();
}  