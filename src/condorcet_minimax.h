/**
 * @file condorcet_minimax.h
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * 
 * @brief Module contenant l'ensemble des fonctions pour la methodes condorcet minimax
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #ifndef __CONDORCET_MINIMAX_H__
 #define __CONDORCET_MINIMAX_H__


/*************************** FICHIER D'ENTÊTE ***************************/

#include "utils_sd.h"

/*************************** FONCTIONS D'ENTÊTE ***************************/

/**
 * @brief cherche le minimum dans un tableau | fonction optimisé évitant 
 *  de lire tous les nombres du tableau
 * 
 * @param tab 
 * @param indice 
 * @param taille 
 * @return int 
 */
int miniVote(int tab[],int indice,int taille);

/**
 * @brief construit le tableau possèdant le minimum de chaque ligne
 * 
 * @param matDuel 
 * @param tabMini 
 */
void votesMinimun(mat_duel* matDuel,int tabMini[]);

/**
 * @brief Renvoie l'indice du maximum dans tabMini
 * 
 * @param tabMini 
 * @param taille 
 * @return int 
 */
int votesMaximun(int tabMini[],int taille);

/**
 * @brief Affichage le gagnant de condorcet selon la méthode Minimax
 * 
 * @param matDuel 
 */
void condorcetMinimax(mat_duel* matDuel);

#endif //__CONDORCET_MINIMAX_H__