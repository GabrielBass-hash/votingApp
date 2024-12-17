/**
 * @file test_sha.c
 * @author Robin Pujol, Emilien Sanchez | (pujol.robin31@gmail.com), (emilien.sanchez@univ-tlse3.fr)
 * @brief Module de test des fonctions en lien avec la vérification de votes
 * @version 1.0
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/sha256.h"
#include "../src/sha256_utils.h"
#include "../src/verify_vote.h"
#include "../src/utils_sd.h"
#include "../src/list.h"


/*************************** MACRO ***************************/

int bufferSize = SHA256_BLOCK_SIZE;


/*************************** STRUCTURE ***************************/

struct Votant {
		char nom[20];
		char prenom[20];
		char identifiant[15];
	};


/*************************** DÉFINITIONS DES FONCTIONS ***************************/

char * tests_sha256(char *nom, char *prenom, char *clef){
	
	char nomPrenom[40];
	char * hashRes = (char*)malloc (bufferSize*2+1);

	strcpy(nomPrenom,nom);
	strcat(nomPrenom," ");
	strcat(nomPrenom,prenom); 
	
	hasheVotant(nomPrenom,clef,hashRes);
	int long_hash = strlen(hashRes); // sa longueur en caractères hexadécimaux
	printf("Le sha : %s avec %d caractères hexadécimaux, soit %d octets comme prévu\n\n",hashRes,long_hash,long_hash/2);

	return (char *)hashRes;
}


/*************************** MAIN ***************************/

int main(int argc, char const *argv[])
{
	struct Votant votants[3];

	strcpy(votants[0].nom, "SANCHEZ");
    strcpy(votants[0].prenom, "Emilien");
    strcpy(votants[0].identifiant, "iejzNC8K9");

    strcpy(votants[1].nom, "WICK");
    strcpy(votants[1].prenom, "John");
    strcpy(votants[1].identifiant, "1CodQuelkonk");

    strcpy(votants[2].nom, "MACRON");
    strcpy(votants[2].prenom, "Emmanuel");
    strcpy(votants[2].identifiant, "1CodeUnik");
	

	// Test de création de hash
	char * hashRes0 = (char*)malloc(bufferSize*2+1);
	char * hashRes1= (char*)malloc(bufferSize*2+1);
	char * hashRes2 = (char*)malloc(bufferSize*2+1);

	printf("Création du hash de %s %s: \n", votants[0].nom, votants[0].prenom) ; 
	hashRes0 = tests_sha256(votants[0].nom, votants[0].prenom, votants[0].identifiant);

	//hash qu'on utilisera après
	printf("Création du hash de %s %s: \n", votants[1].nom, votants[1].prenom) ; 
	hashRes1 = tests_sha256(votants[1].nom, votants[1].prenom, votants[1].identifiant );
	
	printf("Création du hash de %s %s: \n", votants[2].nom, votants[2].prenom) ; 
	hashRes2 = tests_sha256(votants[2].nom, votants[2].prenom, votants[2].identifiant);

	char * tabHashRes[3] = {hashRes0, hashRes1, hashRes2};

	for (int i = 0; i < 3; i++)
	{	
		// récupération du code utilisé dans le main afin de faire un jeu de test automatique
		LinkedElement *res = search_vote(("./fichiers/jugement.csv"), tabHashRes[i]);

    	if (res){
			printf("Résultat de %s %s : \n", votants[i].nom, votants[i].prenom);
        	affVote(res);
    	}
    	else{
        	printf("Résultat de %s %s : \nVotre code \"%s %s%s\" hashe:(%s) n'existe pas dans le fichier %s.\n\n", votants[i].nom, votants[i].prenom, votants[i].nom, votants[i].prenom, votants[i].identifiant, tabHashRes[i],"Jugement");
    	}    
	}
	return 0;
}
