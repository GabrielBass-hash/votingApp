/**
 * @file condorcet_schulze.h
 * @author Gabriel Basso
 * @brief Module d'entête des fonctions de la méthode de résolution du paradoxe 
 *        de condorcet selon la méthode Schulze
 * @version 1.0
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */


 #ifndef __CONDORCET_SCHULZE_H__
 #define __CONDORCET_SCHULZE_H__

 /*************************** FICHIER D'ENTÊTE ***************************/

 #include "list_circuit.h"

 /*************************** FONCTIONS D'ENTÊTE ***************************/

 /**
  * @brief
  *
  * @param  grapheTournoi, indiceTester
  * @return true si l'indiceTester a perdu une éléction
  * @return false si aucune défaite
  */
 bool defaiteIndice(list_arc* grapheTournoi,int indiceTester);

 /**
  * @brief
  *
  * @param matDuel, grapheTournoi
  * @return indice gagnant si un indice n'a plus aucun arc perdant
  * @return -1 si tout les indices ont au moins toujours une défaite
  */
 int winCondition(list_arc* grapheTournoi);

 /**
  * @brief
  *
  * @param grapheTournoi
  * @return indice de l'élément de la liste d'arc avec le poid le plus faible
  *
  */
 int lowestIndexByWeight(list_arc* grapheTournoi);


 /**
  * @brief affiche le gagnant par méthode Condorcet Schulze
  *
  * @param matDuel
  *
  */
 void condorcetSchulze(mat_duel* matDuel);


#endif //__CONDORCET_SCHULZE_H__
