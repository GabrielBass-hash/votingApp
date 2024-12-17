/**
 * @file list.h
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief Structure de données en liste doublement chaînées avec sentinelle
 * @version 1.0
 * @date 2023-10-9
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LIST_H__
#define __LIST_H__

/*************************** FICHIER D'ENTÊTE ***************************/

#include <stdbool.h>

/*************************** DÉFINITIONS DES STRUCTURES  ***************************/

typedef struct s_List List;
typedef struct s_LinkedElement LinkedElement;
typedef List * ptrList;

struct s_LinkedElement {
	char * idReponse;
	char * date;
	char * idCours;
	char * idParticipant;
	int* tabReponse;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
	List* l;
};

struct s_List {
	LinkedElement *sentinel;
	char** nomCandidats;
	int size;
	int nbCandidats;
};

/*************************** DÉCLARATION DES FONCTIONS ***************************/

/**
 * @brief Initialise une liste vide
 * @return List* : un pointeur vers une liste vide
 */
List * list_create();

/**
 * @brief  Renvoie la taille de la liste
 * 
 * @param l 
 * @return int 
 */
int list_size(List *l);

/**
 * @brief Ajoute un nouvel élément, composé des autres paramètres, à l'arrière d'une liste l
 * 
 * @param l 
 * @param idRep 
 * @param date 
 * @param idCours 
 * @param idParticipant 
 * @param tab 
 * @return List* 
 */
List * list_push_back(List *l,char * idRep,char * date,char * idCours,char *idParticipant,int* tab);



/**
 * @brief Ajoute un nouvel élément, composé des autres paramètres, à l'avant d'une liste l
 * 
 * @param l 
 * @param idRep 
 * @param date 
 * @param idCours 
 * @param idParticipant 
 * @param tab 
 * @return List* 
 */
List * list_push_front(List *l,char * idRep,char * date,char * idCours,char *idParticipant,int* tab) ;

/**
 * @brief Renvoie le premier élément de la liste l
 * 
 * @param l 
 * @return LinkedElement *
 */
LinkedElement * list_front(List *l);

/**
 * @brief Renvoie le dernier élément de la liste l
 * 
 * @param l 
 * @return LinkedElement *
 */
LinkedElement * list_back(List *l);

/**
 * @brief Supprime le premier élément d'une liste l et décremente la taille de liste de 1
 * 
 * @param l 
 * @return List* 
 */
List * list_pop_front(List *l);

/**
 * @brief Supprime le premier élément d'une liste l et décremente la taille de liste de 1
 * 
 * @param l 
 * @return List* 
 */
List * list_pop_back(List *l);

/**
 * @brief Renvoie un boolean disant si la liste est vide ou non.
 * 
 * @param l 
 * @return true si liste vide
 * @return false si list pas vide
 */
bool list_is_empty(List *l);


/**
 * @brief Retourne l'élément de la liste associe à l'identifiant du participant
 * 
 * @param l 
 * @param id 
 * @return LinkedElement* 
 */
LinkedElement * getElemWithId(List *l,char * id);

/**
 * @brief Renvoie le tableau contenant les votes grâce à l'élément en paramètre
 * 
 * @param elem 
 * @return int* 
 */
int * getTabWithElem (LinkedElement *elem );


/**
 * @brief Renvoie l'élément à l'indice i de la liste
 * 
 * @param l 
 * @param indice 
 * @return LinkedElement* 
 */
LinkedElement * getElemAtI(List *l,int indice);

/**
 * @brief Affiche sur la console les différents paramètre de l'élément
 * 
 * @param elem 
 */
void affElem(LinkedElement* elem);

/**
 * @brief Affiche sur la console l'entièreté de la liste 
 * (fonction permettant de tester si le csv a bien été extrait)
 * 
 * @param l 
 */
void affList(List* l);

/**
 * @brief Affiche sur la console les votes de l'élément
 * 
 * @param elem 
 */
void affVote(LinkedElement* elem);


/**
 * @brief Renvoie un pointeur de liste null et libère la mémoire occupé par la liste
 * 
 * @param l 
 */
void list_delete(ptrList *l);


#endif //__LIST_H__