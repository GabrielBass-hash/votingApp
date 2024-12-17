/**
 * @file verify_vote.c
 * @author Emilien Sanchez, Robin Pujol | (emilien.sanchez16@gmail.com), (pujol.robin31@gmail.com)
 * @brief Implémentation des fonctions de vérifications
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

#include "verify_vote.h"
#include "sha256_utils.h"
#include "csv.h"


/*************************** DÉFINITIONS DES FONCTIONS ***************************/
void hasheVotant(char* nomComplet,char* clef,char hashRes[SHA256_BLOCK_SIZE*2 + 1]){
    char* item = malloc(sizeof(nomComplet)+sizeof(clef));
    strcpy(item,nomComplet);
    strcat(item,clef);
    sha256ofString((BYTE*)item,hashRes);
}


LinkedElement *search_vote (const char *filename, char hashRes[SHA256_BLOCK_SIZE*2 + 1] ){
    List * liste_ballot = extractCSVFile(filename);
    return getElemWithId(liste_ballot,hashRes);
}