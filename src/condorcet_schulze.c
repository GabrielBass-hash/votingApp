/**
 * @file condorcet_schulze.c
 * @author Gabriel Basso (sendtomadgab@gmail.com)
 * @brief Module d'implémentation des fonctions de condorcet_schulze.h
 * @version 1.0
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 /*************************** FICHIER D'ENTÊTE ***************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "condorcet_schulze.h"

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

bool defaiteIndice(list_arc* grapheTournoi,int indiceTester)
{
  for (element_list_arc *e = grapheTournoi->sentinel->next; (e!= grapheTournoi->sentinel);e = e->next )
  {
    if (e->arcElem->indiceDest==indiceTester)
    {
      return true;
    }
  }
  return false;
}


int winCondition(list_arc* grapheTournoi)
{
  for (element_list_arc *e = grapheTournoi->sentinel->next; ((e!= grapheTournoi->sentinel));e = e->next )
  {
    if (!defaiteIndice(grapheTournoi,e->arcElem->indiceOrigine))
    {
      return e->arcElem->indiceOrigine;
    }
  }
  return -1;
}

int lowestIndexByWeight(list_arc* grapheTournoi)
{
  element_list_arc* test= list_arc_front(grapheTournoi);
  int lowestIndexByWeight=0;
  int lowestWeight=test->arcElem->poids;
  for (int i=0; i< grapheTournoi->size;i++)
  {
    test= list_arc_get_element_at_index(grapheTournoi,i);
    if(lowestWeight > test->arcElem->poids)
    {
      lowestIndexByWeight=i;
      lowestWeight=test->arcElem->poids;
    }
  }
  return lowestIndexByWeight;
}

void condorcetSchulze(mat_duel* matDuel)
{
  resDuelsMatrice(matDuel);
  afficherMat(matDuel);
  list_arc *lArcs = grapheTournoi(matDuel);
  affichageListArc(lArcs);
  while(winCondition(lArcs)==-1)
  {
    list_arc_remove_at(lArcs,lowestIndexByWeight(lArcs));
  }
  afficheMethode("CondorcetSchulze",matDuel->nbCandidats, matDuel->nbVotant, matDuel->nomCandidat,winCondition(lArcs));
  list_arc_delete(&lArcs);
}
