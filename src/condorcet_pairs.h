/**
 * @file condorcet_pairs.h
 * @author Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Module d'entête des fonctions de résolution du paradoxe de Condorcet 
 *         selon la méthode des rangements des pairs par ordre décroissant
 * @version 1.0
 * @date 2023-12-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #ifndef __CONDORCET_PAIR_H__
 #define __CONDORCET_PAIR_H__


/*************************** FICHIER D'ENTÊTE ***************************/
#include "list_circuit.h"


/*************************** FONCTIONS D'ENTÊTE ***************************/

/**
 * @brief retire l'élément maximal de la liste d'arc en paramètre
 * 
 * @param lArcs 
 * @return element_list_arc* 
 */
element_list_arc *popMaxElemListArc(list_arc *lArcs);


/**
 * @brief renvoie la liste des arcs sans cycle
 * 
 * @param l 
 * @return list_arc* 
 */
list_arc *grapheSansCycle(list_arc *lArcs);


/**
 * @brief renvoie l'élément gagnant de la liste d'arc
 * 
 * @param lRes 
 * @return element_list_arc* 
 */
element_list_arc *elemGagnantGraphe(list_arc *lRes);


/**
 * @brief affiche le gagnant de condorcet selon la méthode des rangements des pairs par ordre décroissant
 * 
 * @param matD 
 */
void condorcetPair(mat_duel *matD);

/**
 * @brief Fonction auxiliaire pour vérifier la présence de circuit
 * 
 * @param v 
 * @param visitee 
 * @param recPile 
 * @param lRes 
 * @return boolean
 */
bool estCycliqueUtil(int v, bool visitee[], bool *recPile, list_arc* lRes);

/**
 * @brief  Fonction principale pour détecter les circuits
 * 
 * @param lRes 
 * @return boolean
 */
bool estCyclique(list_arc* lRes);


#endif //__CONDORCET_PAIR_H__