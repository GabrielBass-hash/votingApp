/**
 * @file utils_sd.c
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * 
 * @brief Implementation de utils_sd.h
 * @version 1.0
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIER D'ENTÊTE ***************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <time.h>

#include "utils_sd.h"


/*************************** DÉCLARATION DES FONCTIONS ***************************/

void afficheMethode(char* nomMethode,int nbCandidats,int nbVotant,char** nomCandidats,int indiceGagant){
    printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s.\n",nomMethode,nbCandidats,nbVotant,nomCandidats[indiceGagant]);
}

int aleatoire(int n){
    return rand()%(n+1);
}

void affTab(int* tab, int taille){
    for (int i = 0; i < taille; i++)
    {
        printf("%d ",tab[i]);
    }
    printf("\n");
    
}

int min(int* tab, int nbCandidats){
    int res;
    res = 10;
    for(int i = 0 ; i < nbCandidats ; i++){
        if(res > tab[i] && tab[i] > 0){
            res = tab[i];
        }
    }
    return res;
}

void afficherMat(mat_duel* matDuel){
    printf("      %35s  ","");
    for(int i = 0 ; i<matDuel->nbCandidats;i++){
        printf("%3d ",i);
    }
    printf("\n");
    for(int i = 0; i<matDuel->nbCandidats;i++){
        printf("%3d : %-35s :",i,matDuel->nomCandidat[i]);
        for(int j = 0; j<matDuel->nbCandidats;j++){
            printf("%3d ",matDuel->mat[i][j]);
        }
        printf("\n");
    }
    return;
}

int *copy_tab(int *tab, int taille){
    int *copy = (int *)malloc(sizeof(int));
    for (int i = 0; i < taille; i++)
    {
        copy[i] = tab[i];
    }
    return copy;
    
}

mat_duel* genererMatDuel(List* l){
    srand(time(NULL));
    mat_duel* res = malloc(sizeof(mat_duel));
    res->nbCandidats = l->nbCandidats;
    res->nbVotant = l->size;
    res->nomCandidat = l->nomCandidats;
    res->mat = (int**)malloc(sizeof(int*)*res->nbVotant);
    for(int i=0;i<res->nbCandidats;i++){
        res->mat[i] = (int*)calloc(res->nbCandidats,sizeof(int));
    }
    for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
		for(int i = 0 ; i < l->nbCandidats ;i++){
            for(int j = i ; j < l->nbCandidats ; j++){
                if(i!=j){
                    if(e->tabReponse[i]==e->tabReponse[j]){
                        int r = aleatoire(1);
                        if(r){
                            res->mat[i][j]++;
                        }
                        else{
                            res->mat[j][i]++;
                        }
                    }
                    else if(e->tabReponse[i]==-1){
                        res->mat[j][i]++;
                    }
                    else if(e->tabReponse[j]==-1){
                        res->mat[i][j]++;
                    }
                    else if(e->tabReponse[i]<e->tabReponse[j]){
                        res->mat[i][j]++;
                    }
                    else{
                        res->mat[j][i]++;
                    }
                }
            }
        }
	}
    return res;
}

mat_duel* copieMatDuel(List* l){
    srand(time(NULL));
    mat_duel* res = malloc(sizeof(mat_duel));
    res->nbCandidats = l->nbCandidats;
    res->nbVotant = l->size;
    res->nomCandidat = l->nomCandidats;
    res->mat = (int**)malloc(sizeof(int*)*res->nbVotant);
    for(int i=0;i<res->nbCandidats;i++){
        res->mat[i] = (int*)calloc(res->nbCandidats,sizeof(int));
    }
    int ligne = 0;
    for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
		for(int i = 0 ; i < res->nbCandidats ; i++){
            res->mat[ligne][i] = e->tabReponse[i];
        }
        ligne++;
	}
    return res;
}

int vainqueurCondorcet(mat_duel* matDuel){
    int perdu = 0;
    for(int i = 0 ; i <matDuel->nbCandidats ; i++){
        for(int j = 0 ; j < matDuel->nbCandidats ; j++){
            if(i!=j){
                if(matDuel->mat[i][j]<matDuel->mat[j][i]){
                    perdu = 1;
                }
            }
            if(j==matDuel->nbCandidats-1 && !perdu){
                return i;
            }
        }
        perdu = 0;
    }
    return -1;
}


void matrice_delete(ptrMatDuel* matDuel){
    for(int i = 0 ; i < (*matDuel)->nbCandidats ; i++){
        free((*matDuel)->mat[i]);
    }
    free((*matDuel)->mat);
    free(*matDuel);
}