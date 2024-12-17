/**
 * @file tests_condorcet_pair.c
 * @author Basso Gabriel  (sendtomadgab@gmail.com)
 * @brief Module de test des fonctions en lien avec le scrutin condorcet schulze
 * @version 1.0
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */


/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "../src/condorcet_schulze.h"

#include "../src/list.h"
#include "../src/list_circuit.h"

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

/**
 * @brief fonction test, vérifiant étape par étape le bon
 *        fonctionnement de la méthode
 * 
 */
void testVoteCondorcet()
{
  printf("****VoteCondorcet Test****\n");
  List *listCondorcet = extractCSVFile("./fichiers/VoteCondorcet.csv");
  mat_duel *matCondorcet = genererMatDuel(listCondorcet);
  list_arc *arcCondorcet = grapheTournoi(matCondorcet);
  assert(lowestIndexByWeight(arcCondorcet)==33);
  printf("lowestIndexByWeight Init: Validé\n");
  list_arc_remove_at(arcCondorcet,lowestIndexByWeight(arcCondorcet));
  assert(lowestIndexByWeight(arcCondorcet)==32);
  printf("lowestIndexByWeight n+1: Validé\n");
  list_arc_remove_at(arcCondorcet,lowestIndexByWeight(arcCondorcet));
  assert(defaiteIndice(arcCondorcet,0)==true);
  printf("defaiteIndice: cas True: Validé\n");
  assert(winCondition(arcCondorcet)==-1);
  printf("winCondition: cas False: Validé\n");
  while(winCondition(arcCondorcet)==-1)
  {
    list_arc_remove_at(arcCondorcet,lowestIndexByWeight(arcCondorcet));
  }
  assert(winCondition(arcCondorcet)!=-1);
  printf("winCondition: cas True: Validé\n");
  assert(defaiteIndice(arcCondorcet,winCondition(arcCondorcet))==false);
  printf("defaiteIndice: cas False: Validé\n");
  condorcetSchulze(matCondorcet);
  printf("\n\n****VoteCondorcet Test****\n");
}

// void testCalcul1()
// {
//   printf("****Calcul1 Test****\n");
//   List *listCalcul1 = extractCSVMat("./fichiers/calcul1.csv");
//   mat_duel *matCalcul1=copieMatDuel(listCalcul1);
//   list_arc *arcCalcul1=grapheTournoi(matCalcul1);
//   assert(lowestIndexByWeight(arcCalcul1)==18);
//   printf("lowestIndexByWeight Init: Validé\n");
//   list_arc_remove_at(arcCalcul1,lowestIndexByWeight(arcCalcul1));
//   assert(lowestIndexByWeight(arcCalcul1)==16);
//   printf("lowestIndexByWeight n+1: Validé\n");
//   list_arc_remove_at(arcCalcul1,lowestIndexByWeight(arcCalcul1));
//   assert(defaiteIndice(arcCalcul1,0)==true);
//   printf("defaiteIndice cas True: Validé\n");
//   assert(winCondition(arcCalcul1)==-1);
//   printf("winCondition: cas False: Validé\n");
//   while(winCondition(arcCalcul1)==-1)
//   {
//     list_arc_remove_at(arcCalcul1,lowestIndexByWeight(arcCalcul1));
//   }
//   assert(winCondition(arcCalcul1)!=-1);
//   printf("winCondition: cas True: Validé\n");
//   assert(defaiteIndice(arcCalcul1,winCondition(arcCalcul1))==false);
//   printf("defaiteIndice: cas False: Validé\n");
//   condorcetSchulze(matCalcul1);
//   printf("\n\n****Calcul1 Test****\n");
//
// }

/*************************** MAIN ***************************/

/**
 * @brief fonction principale du programme de test
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
  testVoteCondorcet();
  return 0;
}
