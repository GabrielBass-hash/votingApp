/**
 * @file JugementMajoritaire.h
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #ifndef __JUGEMENT_MAJORITAIRE_H__
 #define __JUGEMENT_MAJORITAIRE_H__

/*************************** FICHIERS D'ENTÊTE ***************************/

#include "list.h"

/*************************** ENTÊTES DES FONCTIONS ***************************/

/**
 * @brief Le jugement majoritaire est une méthode de vote décidant du gagnant en fonction de qui à la meilleure appréciation médiane attribué par les électeurs.
 * 
 * @param l : Liste contenant les données de votes.
 */
void jugementMajoritaire(List *l);
/**
 * @brief  Une simple methode de trie par séléction d'un tableau d'entiers
 * 
 * @param tab 
 * @param tailleTab 
 */
void trierTableau(int tab[],int tailleTab);


#endif //__JUGEMENT_MAJORITAIRE_H__