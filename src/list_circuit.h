/**
 * @file list_circuit.c
 * @author  Robin Pujol (pujol.robin31@gmail.com) || Emilien SANCHEZ (emilien.sanchez16@gmail.com)
 * @brief Ensemble des fonctions permettant de créer la liste des arcs et de vérifier si il y a des circuits
 * @version 1.0
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #ifndef __LIST_CIRCUIT_H__
 #define __LIST_CIRCUIT_H__


#include "utils_sd.h"



/*************************** STRUCTURES ***************************/


typedef struct s_list_arc list_arc;
typedef struct s_element_list_arc element_list_arc;
typedef struct s_arc arc;
typedef list_arc *ptrListArc;


/**
 * @brief structure des arcs
 * 
 */
struct s_arc {
    int poids;
    int indiceOrigine;
    int indiceDest;
};

/**
 * @brief structure des éléments des listes
 * 
 */
struct s_element_list_arc {
    arc* arcElem;
    element_list_arc* next;
    element_list_arc* previous;
};

/**
 * @brief structure des listes d'arcs
 * 
 */
struct s_list_arc {
    element_list_arc* sentinel;
    char** nomCandidats;
    int size;
};

/*************************** DÉCLARATION FONCTION ***************************/

/**
 * @brief crée une liste et l'a renvoie
 * 
 * @return list_arc* 
 */
list_arc* list_arc_create();

/**
 * @brief prend une liste et un élément et renvoie la liste avec
 *        l'élément ajouté à la fin 
 * 
 * @param l 
 * @param newArcElem 
 * @return list_arc* 
 */
list_arc* list_arc_push_back(list_arc* l,arc* newArcElem);

/**
 * @brief prend une liste en param et la supprime
 * 
 * @param l 
 */
void list_arc_delete(ptrListArc *l);

/**
 * @brief prend une liste et un élément et renvoie la liste avec
 * l'élément ajouté au début 
 * 
 * @param l 
 * @param newArcElem 
 * @return list_arc* 
 */
list_arc* list_arc_push_front(list_arc* l,arc* newArcElem);

/**
 * @brief renvoie le premier élément de la liste
 * 
 * @param l 
 * @return element_list_arc* 
 */
element_list_arc* list_arc_front(list_arc* l);

/**
 * @brief renvoie le dernier élément de la liste
 * 
 * @param l 
 * @return element_list_arc* 
 */
element_list_arc* list_arc_back(list_arc* l);

/**
 * @brief supprime le premier élément d'une liste
 * 
 * @param l 
 * @return list_arc* 
 */
list_arc* list_arc_pop_front(list_arc* l);

/**
 * @brief upprime le dernier élément d'une liste
 * 
 * @param l 
 * @return list_arc* 
 */
list_arc* list_arc_pop_back(list_arc* l);

/**
 * @brief retourne un entier afin de savoir si la liste est vide ou
 * non
 * 
 * @param l 
 * @return int 
 */
int list_arc_is_empty(list_arc *l);

/**
 * @brief renvoie la taille de la liste
 * 
 * @param l 
 * @return int 
 */
int list_arc_size(list_arc *l);

/**
 * @brief Renvoie un boolean sur l'appartenance de e dans l
 * 
 * @param l 
 * @param e 
 * @return true 
 * @return false 
 */
bool contains(list_arc * l, element_list_arc * e);


/**
 * @brief renvoie un boolean sur la contenance de circuit dans l
 * 
 * @param l 
 * @param nbCandidats 
 * @return true 
 * @return false 
 */
bool circuits(list_arc *l, int nbCandidats);

/**
 * @brief 
 * 
 * @param l 
 * @param index 
 * @return element_list_arc* 
 */
element_list_arc *list_arc_remove_at(list_arc* l, int index);

/**
 * @brief resultats des duels dans une matrice de duels
 * 
 * @param l
 * @return mat_duel* 
 */
mat_duel *resDuelsMatrice(mat_duel *matD);


/**
 * @brief création de la liste des arcs de la matrice
 * 
 * @param matD 
 * @return list_arc* 
 */
list_arc *grapheTournoi(mat_duel *matD);


/**
 * @brief affichage de la liste d'arcs
 * 
 * @param l 
 */
void affichageListArc(list_arc *l);

/**
 * @brief affichage des arcs d'un élément
 * 
 */
void affArcElem(element_list_arc *e);

/**
 * @brief 
 * 
 * @param l 
 * @param index 
 * @return element_list_arc* 
 */
element_list_arc* list_arc_get_element_at_index(list_arc* l, int index);

/**
 * @brief 
 * 
 * @param l 
 * @param tabStatut 
 * @param e 
 * @return true 
 * @return false 
 */
int dfsCircuit(list_arc *l, int *tabStatut,element_list_arc *e);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool hasSuccesseur(list_arc *lRes,element_list_arc *elem);

#endif //__LIST_CIRCUIT_H__