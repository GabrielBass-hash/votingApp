/**
 * @file list.c
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief Implémentation de la structure de données en liste doublement chaînées avec sentinelle
 * @version 1.0
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"


/*************************** DÉFINITION DES FONCTIONS ***************************/

List * list_create(){
	List* l = malloc(sizeof(List));
	l->sentinel=malloc(sizeof(LinkedElement));
	l->sentinel->next=l->sentinel->previous=l->sentinel;
	return l;
}

List * list_push_back(List *l,char * idRep,char * date,char * idCours,char *idParticipant,int* tab){
	
	LinkedElement *new = (LinkedElement *)malloc(sizeof(LinkedElement));
	
	LinkedElement *old = l->sentinel->previous;

	new->idReponse=idRep;
	new->date=date;
	new->idCours=idCours;
	new->idParticipant=idParticipant;
	new->l = (List*)malloc(sizeof(List*));
	new->l=l;

	new->tabReponse= malloc(sizeof(int)*l->nbCandidats);
	for(int i = 0;i<l->nbCandidats;i++){
		new->tabReponse[i]=tab[i];
	}

	old->next=new;
	new->previous=old;
	l->sentinel->previous=new;
	new->next=l->sentinel;
	l->size++;

	

	return l;
}

void list_delete(ptrList *l) {
	LinkedElement* delete = (*l)->sentinel->next;
	while(delete!=(*l)->sentinel){
		LinkedElement* e= delete;
		delete = delete->next;
		free(e);
	}
	free((*l)->sentinel);
	free(*l);
	*l=NULL;
}

List * list_push_front(List *l,char * idRep,char * date,char * idCours,char *idParticipant,int* tab) {
	LinkedElement *new = malloc(sizeof(LinkedElement));
	LinkedElement *old = l->sentinel->next;
	new->idReponse=idRep;
	new->date=date;
	new->idCours=idCours;
	new->idParticipant=idParticipant;
	new->l=l;
	new->tabReponse=malloc(sizeof(int)*l->nbCandidats);
	for(int i = 0;i<l->nbCandidats;i++){
		new->tabReponse[i]=tab[i];
	}
	old->previous=new;
	new->next=old;
	l->sentinel->next=new;
	new->previous=l->sentinel;
	l->size++;
	return l;
}

LinkedElement* list_front(List *l){
	assert(!(list_is_empty(l)));
	return l->sentinel->next;
}

LinkedElement * list_back(List *l){
	assert(!(list_is_empty(l)));
	return l->sentinel->previous;
}

List * list_pop_front(List *l){
	assert(!(list_is_empty(l)));
	LinkedElement* oldFront = l->sentinel->next;
	LinkedElement* newFront = oldFront->next;
	l->sentinel->next=newFront;
	newFront->previous=l->sentinel;
	free(oldFront);
	l->size--;
	return l;
}

List *list_pop_back(List *l){
	assert(!(list_is_empty(l)));
	LinkedElement* oldBack = l->sentinel->previous;
	LinkedElement* newBack = oldBack->previous;
	l->sentinel->previous=newBack;
	newBack->next=l->sentinel;
	free(oldBack);
	l->size--;
	return l;
}

bool list_is_empty(List *l) {
	return l->size==0;
}

int list_size(List *l) {
	return l->size;
}

LinkedElement * getElemWithId(List *l,char * id){
	LinkedElement* result = NULL;
	bool trouve = false;
	for(LinkedElement* e = l->sentinel->next;e!=l->sentinel && !trouve;e=e->next){
		if(!strcmp(e->idParticipant,id)){
			result =e;
			trouve = true;
		}
	}
	return result;
}

int * getTabWithElem (LinkedElement *elem ){
	return elem->tabReponse;
}

LinkedElement * getElemAtI(List *l,int indice){
	if(indice>list_size(l)){
		return NULL;
	}
	LinkedElement* elem = l->sentinel;
	for(int i=0;i<indice;i++){
		elem=elem->next;
	}
	return elem;
}

void affElem(LinkedElement* elem){
	printf("Idreponse : %s  Date : %s IdCours : %s  IdParticipant : %s",elem->idReponse,elem->date,elem->idCours,elem->idParticipant);
	for(int i=0;i<elem->l->nbCandidats;i++){
		printf("%3d",elem->tabReponse[i]);
	}
	printf("\n");
}

void affList(List* l){
	for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
		affElem(e);
	}
}

void affVote(LinkedElement* elem){
	printf("Votre vote fais le %s pour %s :\n",elem->date,elem->idCours);
	for (int i = 0; i < elem->l->nbCandidats; i++){
		printf ("	- %-35s : %3d \n",elem->l->nomCandidats[i],elem->tabReponse[i]);
	}
}