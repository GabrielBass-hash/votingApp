/**
 * @file condorcet_pairs.c
 * @author Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Module d'implémentation des entêtes de condorcet_pairs.h
 * @version 1.0
 * @date 2023-12-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "condorcet_pairs.h" 

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

element_list_arc *popMaxElemListArc(list_arc *lArcs){
    
    if(lArcs->size == 1)
    {
        
        return list_arc_remove_at(lArcs, 0);
    }

    else if (lArcs->size > 1)
    {
        element_list_arc *max = list_arc_front(lArcs);

        element_list_arc *current = max->next;

        int indexCurrent = 0;
        int indexMax = 0;

        while (current != lArcs->sentinel)
        {
            indexCurrent ++; // indice de current
            if (max->arcElem->poids < current->arcElem->poids ){
                max = current;
                indexMax = indexCurrent; //
            }
            current = current->next;
        } 
        return list_arc_remove_at(lArcs, indexMax);;
    }
    return NULL;
}


// Fonction auxiliaire pour vérifier la présence de circuit
bool estCycliqueUtil(int v, bool visitee[], bool *recPile, list_arc* lRes) {
    if(visitee[v] == false) {
        // Marquer le nœud actuel comme visité et enregistrer dans la pile de récursion
        visitee[v] = true;
        recPile[v] = true;

        struct s_element_list_arc* current = lRes->sentinel->next;
        while(current != lRes->sentinel) {
            if(current->arcElem->indiceOrigine == v) {
                int dest = current->arcElem->indiceDest;
                if (!visitee[dest] && estCycliqueUtil(dest, visitee, recPile, lRes))
                    return true;
                else if (recPile[dest])
                    return true;
            }
            current = current->next;
        }
    }
    recPile[v] = false; // Supprimer le nœud de la pile de récursion
    return false;
}

// Fonction principale pour détecter les circuits
bool estCyclique(list_arc* lRes) {
    bool *visitee = (bool *)malloc(lRes->size * sizeof(bool));
    bool *recPile = (bool *)malloc(lRes->size * sizeof(bool));

    for(int i = 0; i < lRes->size; i++) {
        visitee[i] = false;
        recPile[i] = false;
    }

    // Appel récursif pour détecter les circuits en vérifiant chaque arc
    for(int i = 0; i < lRes->size; i++) {
        if (estCycliqueUtil(i, visitee, recPile, lRes)){
            free(visitee);
            free(recPile);
            return true;
        }
    }
    free(visitee);
    free(recPile);
    return false;
}

list_arc *grapheSansCycle(list_arc *lArcs){
    bool res ;
    list_arc * lRes = list_arc_create();
    while(list_arc_size(lArcs)>0){
        element_list_arc *e = list_arc_remove_at(lArcs,0);
        list_arc_push_back(lRes, e->arcElem);
        printf("On ajoute cette arc au graphe :\n");
        affArcElem(e);
        free(e);
        if ((res = estCyclique(lRes))){
            printf("L'ajout de cette element a creer un cycle on le retire donc de la liste.On passe au prochain arc.\n");
            element_list_arc * delete = list_arc_back(lRes);
            lRes = list_arc_pop_back(lRes);
            free(delete);
        }
        if(!res){
            printf("\nLa liste apres l'ajout de l'element :\n");
            affichageListArc(lRes);
        }
    }
    return lRes;
}

element_list_arc *elemGagnantGraphe(list_arc *lRes){

    for (element_list_arc *e = lRes->sentinel->next; e != lRes->sentinel; e = e->next)
    {
        if(!hasSuccesseur(lRes, e)){
            return e;
        }
    }
    return NULL;
}

void condorcetPair(mat_duel *matD){
    printf("La matrice de duel est :\n");
    afficherMat(matD);
    resDuelsMatrice(matD);
    printf("Matrice des arcs entre les candidats:\n");
    afficherMat(matD);
    printf("\n");
    list_arc *lArcs = grapheTournoi(matD);
    printf("Les arcs rentrer dans la liste pas dans le bon ordre:\n");
    affichageListArc(lArcs);
    printf("\n");

    list_arc * lTriee = list_arc_create();
    while (lArcs->size> 0)
    {           
        element_list_arc *elem = popMaxElemListArc(lArcs);
        list_arc_push_back(lTriee, elem->arcElem);
        free(elem);
    }
    printf("Les arcs rentrer dans la liste dans le bon ordre:\n");
    affichageListArc(lTriee);
    printf("\n");
    
    
    list_arc *lRes = grapheSansCycle(lTriee);
    printf("\nLes arc dans la liste sans cycle :\n");
    affichageListArc(lRes);
    printf("\n");

    element_list_arc *gagnant;
    if ((gagnant = elemGagnantGraphe(lRes)) == NULL ){
        printf("La liste est vide !!\n");
    }

    afficheMethode("Rangement des paires par ordre décroissant",matD->nbCandidats, matD->nbVotant, matD->nomCandidat, gagnant->arcElem->indiceOrigine);
    list_arc_delete(&lArcs);
    list_arc_delete(&lTriee);
    list_arc_delete(&lRes);
}
