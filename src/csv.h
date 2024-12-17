/**
 * @file csv.h
 * @author Gabriel Basso (sendtomadgab@gmail.com) | Robin Pujol (pujol.robin31@gmail.com)
 * @brief Lecture du fichier CSV afin d'en extraire une liste
 * @version 1.0
 * @date 2023-11-25
 *
 * @copyright Copyright (c) 2023
 *
 */

 #ifndef __CSV_H__
 #define __CSV_H__

#include "list.h"

/*************************** DÉCLARATION FONCTION ***************************/

/**
 * @brief Extrait les données du fichier csv nommé filename (standardisé proG)
 * 
 * @param filename : Nom du fichier contenant les données à extraire.
 * @return List* : un pointeur vers une liste contenant tout le fichier csv
 */
List* extractCSVFile(const char *filename);
/**
 * @brief les données du fichier csv nommé filename (standardisé matrice de duel)
 * 
 * @param filename Nom du fichier contenant les données à extraire
 * @return List* un pointeur vers une liste contenant tout le fichier csv
 */
List* extractCSVMat(const char *filename);


#endif //__CSV_H__
