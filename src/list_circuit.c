/**
 * @file list_circuit.c
 * @author  Robin Pujol (pujol.robin31@gmail.com) || Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Implementation de list_circuit.h
 * @version 1.0
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "list_circuit.h"
#include "csv.h"

/*************************** DÉFINITIONS DES FONCTIONS ***************************/

list_arc* list_arc_create(){
    list_arc* l = (list_arc *)malloc(sizeof(list_arc));
    l->size = 0;
    l->sentinel= (element_list_arc *)malloc(sizeof(element_list_arc));
	l->sentinel->arcElem = NULL;
	l->sentinel->next = l->sentinel->previous = l->sentinel;
    return l;
}

list_arc* list_arc_push_back(list_arc* l,arc* newArcElem){

    element_list_arc* new = (element_list_arc*)malloc(sizeof(element_list_arc));

	new->arcElem = newArcElem;
    
	element_list_arc* old = l->sentinel->previous;
    
    old->next=new;
    new->previous=old;
    l->sentinel->previous=new;
    new->next=l->sentinel;
    l->size++;

    return l;
}

void list_arc_delete(ptrListArc *l){
    element_list_arc* delete = (*l)->sentinel->next;
	while(delete!=(*l)->sentinel){
		element_list_arc* e= delete;
		free(e->arcElem);
		delete = delete->next;
		free(e);
	}
	free((*l)->sentinel);
	free(*l);
}

list_arc* list_arc_push_front(list_arc* l,arc* newArcElem){
    element_list_arc* new = (element_list_arc*)malloc(sizeof(element_list_arc));
    element_list_arc* old = l->sentinel->previous;
	new->arcElem = (arc *)malloc(sizeof(arc));
    new->arcElem = newArcElem;
    old->previous=new;
	new->next=old;
	l->sentinel->next=new;
	new->previous=l->sentinel;
	l->size++;
	return l;
}

element_list_arc* list_arc_front(list_arc* l){
    assert(!(list_arc_is_empty(l)));
    return l->sentinel->next;
}

element_list_arc* list_arc_back(list_arc* l){
    assert(!(list_arc_is_empty(l)));
    return l->sentinel->previous;
}

list_arc* list_arc_pop_front(list_arc* l){
    assert(!(list_arc_is_empty(l)));
	element_list_arc* oldFront = l->sentinel->next;
	element_list_arc* newFront = oldFront->next;
	l->sentinel->next=newFront;
	newFront->previous=l->sentinel;
	l->size--;
	return l;
}

list_arc* list_arc_pop_back(list_arc* l){
	assert(!(list_arc_is_empty(l)));
	element_list_arc* oldBack = l->sentinel->previous;
	element_list_arc* newBack = oldBack->previous;
	l->sentinel->previous=newBack;
	newBack->next=l->sentinel;
	l->size--;
	return l;
}

int list_arc_is_empty(list_arc *l) {
	return l->size==0;
}

int list_arc_size(list_arc *l) {
	return l->size;
}

element_list_arc* list_arc_remove_at(list_arc* l, int index) {
    
    assert(index >= 0 && index < l->size);
    element_list_arc* removedArc = l->sentinel;

    for (int i = 0; i <= index; i++){
        removedArc = removedArc->next;
    }
    removedArc->previous->next = removedArc->next;
    removedArc->next->previous = removedArc->previous;
    l->size--;
    return removedArc;
}

element_list_arc* list_arc_get_element_at_index(list_arc* l, int index) {
    assert(index >= 0 && index < l->size);

    element_list_arc* current = l->sentinel->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}



bool contains(list_arc * l, element_list_arc * e){
	if (l->size == 0) return false;

	for (element_list_arc * current = l->sentinel->next ; current != l->sentinel ; current = current->next )
	{	
		if (current == e){
			return true;
		}
	}
	return false;
}

/*le tabStaut a pour signification :(-1 pour libre, 0 pour ouvert, 1 pour fermé) */
bool circuits(list_arc *l, int nbCandidats){
	printf("\n Entree dans la fonction circuits\n");
	
	for (element_list_arc * e = l->sentinel->next ; e != l->sentinel; e = e->next )
	{
		printf("TAB INIT\n");
		int *tabStatut = (int *)malloc(nbCandidats * sizeof(int));
		// init le tab à -1 sur tout les elem
		for (int i = 0; i < nbCandidats; i++)
		{
			tabStatut[i] =-1;
		}

		if (dfsCircuit(l, tabStatut, e)){
			free(tabStatut);
			return true;
		}
		free(tabStatut);
	}
	return false;
}

void test(list_arc* l){
	for (element_list_arc * y = l->sentinel->next ; y != l->sentinel; y = y->next)
	{
		list_arc_pop_front(l);
	}
	printf("LIST SUCC DELETE\n");
	list_arc_delete(&l);
}

int dfsCircuit(list_arc *l, int *tabStatut, element_list_arc *x){
	printf("ON RENTRE DANS DFS\n");
	list_arc * listSucc = list_arc_create();
	printf("LIST SUCC CREER\n");

	for (element_list_arc * e = l->sentinel->next ; e != l->sentinel; e = e->next )
	{
		if(e->arcElem->indiceOrigine == x->arcElem->indiceDest){
			printf("AJOUT D UN SUCCESSEUR\n");
			list_arc_push_back(listSucc, e->arcElem);
		}
	}
	
	printf("\nArc %d->%d de poids %d; ces sucesseurs sont : \n", x->arcElem->indiceOrigine, x->arcElem->indiceDest, x->arcElem->poids);
	affichageListArc(listSucc);

	tabStatut[x->arcElem->indiceOrigine] = 0;
	int r ;
	for (element_list_arc * y = listSucc->sentinel->next ; y != listSucc->sentinel; y = y->next)
	{
		printf("\t\ton boucle sur les successuers :\n");
		affArcElem(y);
		int *cop = copy_tab(tabStatut, l->size) ;

		if (tabStatut[y->arcElem->indiceDest] == -1){
			tabStatut[y->arcElem->indiceDest] = 0 ;
			r = dfsCircuit(l, tabStatut, y);
			if (r == 1){
				printf("CAS OU IL Y A UN CIRCUIT\n");
				free(cop);
				printf("FREE COP\n");
				test(listSucc);
				printf("FREE SUCC\n");
				return 1;
			}
			else if (r == 0){
					tabStatut = cop;
				}
			
		}
		else if (tabStatut[y->arcElem->indiceDest] == 0){
			printf("CAS OU IL Y A UN CIRCUIT\n");
			free(cop);
			printf("FREE COP\n");
			test(listSucc);
			printf("FREE SUCC\n");
			return 1;
			}
		free(cop);
	}
	printf("CAS OU IL N Y A PAS DE CIRCUIT\n");
	tabStatut[x->arcElem->indiceOrigine] = 1;
	test(listSucc);
	return 0;
}

mat_duel *resDuelsMatrice(mat_duel *matD){
	srand(time(NULL));
	int j = 0; //compteur qui permet de ne regarder que la partie supérieur de la matrice
	
	// creation de la matrice actualisé
	for (int i = 0; i < matD->nbCandidats; i++)
	{	
		j = i + 1;
		for (int k = j ; k < matD->nbCandidats; k++)
		{	
			if (matD->mat[i][k] != 0){

				int diff1 = matD->mat[i][k] - matD->mat[k][i] ;
				int diff2 = matD->mat[k][i] - matD->mat[i][k] ;

				if (diff1 == diff2){ // gestion du "pairwise tie" via aléatoire
					
					if(aleatoire(1))
					{
						matD->mat[i][k] = diff1;
						matD->mat[k][i] = 0;
					}
					else
					{
						matD->mat[i][k] = 0;
						matD->mat[k][i] = diff2;
					}
					
				}
				else if (diff1 > diff2)
				{					
					matD->mat[i][k] = diff1;
					matD->mat[k][i] = 0;

				}
				else if (diff1 < diff2)
				{
					matD->mat[i][k] = 0;
					matD->mat[k][i] = diff2;
				}
			}
		}
	}
	return matD;
}

list_arc *grapheTournoi(mat_duel *matD){
	srand(time(NULL));
	list_arc *lArcs = list_arc_create();
	
	for (int i = 0; i < matD->nbCandidats; i++)
	{
		for (int j = 0; j < matD->nbCandidats; j++)
		{
			if(matD->mat[i][j] != 0){
				arc *allocArc = (arc *)malloc(sizeof(arc));
				allocArc->indiceOrigine = i;
				allocArc->indiceDest = j;
				allocArc->poids = matD->mat[i][j];

				list_arc_push_back(lArcs, allocArc);
			}
		}
	}
	return lArcs;
}

void affichageListArc(list_arc *l){

    for (element_list_arc *e = l->sentinel->next; (e!= l->sentinel);e = e->next )
    {	
		affArcElem(e);
    }
    
}

void affArcElem(element_list_arc *e) {
        printf("\n");
        printf("\tindice origine : %d\n", e->arcElem->indiceOrigine);
        printf("\tindice destination : %d\n", e->arcElem->indiceDest);
        printf("\tpoids : %d\n", e->arcElem->poids);
}

bool hasSuccesseur(list_arc *lRes,element_list_arc *elem){

	for (element_list_arc *e = lRes->sentinel->next ; e != lRes->sentinel; e = e->next)
	{
		if(elem->arcElem->indiceOrigine == e->arcElem->indiceDest){
			return true;
		}
	}
	return false;
}