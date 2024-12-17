/**
 * @file condorcet_minimax.c
 * @author Robin Pujol (pujol.robin31@gmail.com)
 * @brief Implémentation du module condorcet_minimax.h
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/*************************** FICHIER D'ENTÊTE ***************************/

#include "condorcet_minimax.h"
#include "stdio.h"


/*************************** DÉFINITION DES FONCTIONS ***************************/

int miniVote(int tab[],int indice,int taille){
    int min;
    if(indice == 0 ){
        min = tab[1];
    }
    else{
        min = tab[0];
    }
    for(int i = 0 ; i < taille ; i++){
        if(i!=indice && min > tab[i]){
            min = tab[i];
        }
    }
    return min;
}

void votesMinimun(mat_duel* matDuel,int tabMini[]){
    for(int i = 0;i<matDuel->nbCandidats;i++){
        tabMini[i] = miniVote(matDuel->mat[i],i,matDuel->nbCandidats);
    }
}

int votesMaximun(int tabMini[],int taille){
    int max = tabMini[0];
    int indiceMax = 0;
    for(int i = 1 ; i < taille ; i++){
        if(max < tabMini[i]){
            max = tabMini[i];
            indiceMax = i;
        }
    }
    return indiceMax;
}

void condorcetMinimax(mat_duel* matDuel){
    printf("La matrice de duel est :\n");
    afficherMat(matDuel);
    int tabMini[matDuel->nbCandidats];
    votesMinimun(matDuel,tabMini);
    printf("Les plus grandes defaites des candidats sont :\n");
    for(int i =0;i<matDuel->nbCandidats;i++){
        printf("\t%s : %d\n",matDuel->nomCandidat[i],tabMini[i]);
    }
    int gagnant = votesMaximun(tabMini,matDuel->nbCandidats);
    printf("Le maximun de ces defaites est %s : %d.\n",matDuel->nomCandidat[gagnant],tabMini[gagnant]);
    afficheMethode("condorcet minimax",matDuel->nbCandidats,matDuel->nbVotant,matDuel->nomCandidat,gagnant);
}