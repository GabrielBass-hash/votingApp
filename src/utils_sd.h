/**
 * @file utils_sd.c
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * 
 * @brief Module contenant l'ensemble des fonctions utilitaires
 * @version 1.0
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */


 #ifndef __UTILS_SD_H__
 #define __UTILS_SD_H__


/*************************** FICHIER D'ENTÊTE ***************************/

#include "list.h"
#include "csv.h"


/*************************** STRUCTURES ***************************/

/**
 * @brief nommage de la structure
 * 
 */

typedef struct s_mat_duel mat_duel;

/**
 * @brief definition de la structure de la matrice de duels
 * 
 */

struct s_mat_duel {
    int nbCandidats;
    int nbVotant;
    int** mat;
    char** nomCandidat;
};

typedef mat_duel* ptrMatDuel;


/*************************** DÉCLARATION DES FONCTIONS ***************************/

/**
 * @brief fonction renvoyant un nombre "pseudo-aléatoire"
 * 
 * @param n 
 * @return int 
 */
int aleatoire (int n);

/**
 * @brief affichage d'un tableau
 * 
 * @param tab 
 * @param taille 
 */
void affTab(int* tab, int taille);

/**
 * @brief ressort le vote minimale d'un tableau 
 *  (10 le moins aimé | 1 le préféré | -1 ne se prononce pas)
 * 
 * @param tab 
 * @param nbCandidats 
 * @return int 
 */
int min(int* tab, int nbCandidats);

/**
 * @brief 
 * 
 * @param tab 
 * @param taille 
 * @return int* 
 */
int *copy_tab(int *tab, int taille);



/**
 * @brief genere une matrice de duels à partir de la structure de liste
 * 
 * @param l 
 * @return mat_duel* 
 */
mat_duel* genererMatDuel(List* l);

/**
 * @brief affichage clair d'une matrice de duels
 * 
 * @param matDuel 
 */
void afficherMat(mat_duel* matDuel);

/**
 * @brief permet, à partir d'une matrice de duel,
 *  de dire si il y a vainqueur de Condorcet de façon uninanime 
 *  (sans égalité) -> si -1 est retourné cas de l'égalité
 * 
 * @param matDuel 
 * @return int 
 */
int vainqueurCondorcet(mat_duel* matDuel);


mat_duel* copieMatDuel(List* l);


void afficheMethode(char* nomMethode,int nbCandidats,int nbVotant,char** nomCandidats,int indiceGagant);


void matrice_delete(ptrMatDuel* matDuel);


#endif //__UTILS_SD_H__