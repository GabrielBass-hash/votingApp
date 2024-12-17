/**
 * @file verify_vote.h
 * @author Emilien Sanchez, Robin Pujol | (emilien.sanchez16@gmail.com), (pujol.robin31@gmail.com)
 * @brief Module contenant les déclarations des fonctions de vérifications
 * @version 1.0
 * @date 2023-10-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef verify_vote_h
#define verify_vote_h

/*************************** FICHIERS D'ENTÊTE ***************************/
#include "sha256.h"
#include "list.h"


/*************************** DÉCLARATIONS FONCTIONS ***************************/
/**
 * @brief Fonction qui permet de calculer le hash d'une chaîne de caractère
 * 
 * @param nomComplet 
 * @param clef 
 * @param hashRes 
 */
void hasheVotant(char* nomComplet,char* clef,char hashRes[SHA256_BLOCK_SIZE*2 + 1]);

/**
 * @brief Renvoie l'élément dans la liste contenant toute les informations concernant le vote lié au hash
 * 
 * @param filename 
 * @param hashRes  
 * @return LinkedElement* 
 */
LinkedElement * search_vote (const char *filename, char hashRes[SHA256_BLOCK_SIZE*2 + 1]); 

#endif /* verify_vote_h */
