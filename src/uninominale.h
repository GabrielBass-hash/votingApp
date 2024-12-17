/**
 * @file uninominale.h
 * @author  Emilien Sanchez (emilien.sanchez@univ-tlse3.fr)
 *          Robin Pujol (pujol.robin31@gmail.com)
 *          Robin Mounié (robin.mounie@gmail.com)
 *          Gabriel Basso(sendtomadgab@gmail.com)
 *          
 * @brief Module contenant les en-têtes des fonctions permettant le scrutin
 *  uninominale
 * @version 0.1
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 */

 #ifndef __UNINOMINALE_H__
 #define __UNINOMINALE_H__




/*************************** FICHIERS D'ENTÊTE ***************************/

#include "list.h"
#include "csv.h"
#include "utils_sd.h"

/*************************** DÉFINITION FONCTION ***************************/

/**
 * @brief fonction prennant en parametre les votes d'un votant et sort son candidats préféré
 *  en cas d'égalité -> fonction d'aléatoire 
 *  créer un tableau des resultats
 * 
 * @param vote 
 * @param res 
 * @param nbCandidats 
 */
void vote1(int* vote, int* res,int nbCandidats);

/**
 * @brief fonction d'affichage du mode de scrutin uninominale
 * 
 * @param nbVoteTot 
 * @param res 
 * @param indiceGagnant 
 * @param nomB 
 */
void affUninominale1(int nbVoteTot,int* res,int indiceGagnant, char* nomB[]);

/**
 * @brief fonction permettant de ressortir les deux candidats préférés
 * 
 * @param res 
 * @param max 
 * @param nbCandidats 
 */
void indiceRes1(int* res, int* max,int nbCandidats);

/**
 * @brief fonction pour le scrutin uninominale à 1 tour
 * 
 * @param l 
 * @param max 
 * @param res 
 */
void uninominale1 (List* l, int* max, int* res);

/**
 * @brief fonction pour le scrutin uninominale à 2 tours
 * 
 * @param l 
 * @return int 
 */
int uninominale2 (List* l);

/**
 * @brief permet de ressortir le gagnant parmis les deux candidats préférés
 * 
 * @param nbVoteCandidats 
 * @param gagnantPremierTours 
 * @return int 
 */
int indiceRes2(int* nbVoteCandidats,int* gagnantPremierTours);

/**
 * @brief fonction faisant un vote entre les 2 candidats préférés
 * 
 * @param tabReponse 
 * @param gagnantPremierTours 
 * @param nbVoteCandidats 
 */
void vote2(int* tabReponse,int* gagnantPremierTours,int* nbVoteCandidats );

#endif //__UNINOMINALE_H__