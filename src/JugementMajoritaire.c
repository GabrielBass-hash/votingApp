/**
 * @file JugementMajoritaire.c
 * @author Robin Mounié (robin.mounie@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "utils_sd.h"

/*************************** STRUCTURES ***************************/

typedef struct {
    int MinV;
    int * indicesMinV;
    int nbIndices;
} minRes;

/*************************** ENTÊTES DES FONCTIONS ***************************/

void trierTableau(int tab[],int tailleTab);
int recupererVoteCadidat(int i , List *l,int ** tableau);
void afficherMentionCandidats(int i);
int voteJM(int * tabVoteCandidats[],int tabNbVoteCandidats[],int nbCandidats,List * l);
void trouverMinimum(int tableau[], int taille,minRes * resultat);


/*************************** DÉFINITIONS D'ENTÊTE ***************************/

void jugementMajoritaire(List *l){
    int tailleTabCandidats=l->nbCandidats;
    int **tabVoteCandidats = malloc(tailleTabCandidats * sizeof(int *));// a l'indice i se trouve le tableau des votes pour le candidats i
    for (int i = 0; i < tailleTabCandidats; i++) {
        tabVoteCandidats[i] = malloc(list_size(l) * sizeof(int));
    }   
    int tabNbVoteCandidats[tailleTabCandidats]; // a l'indice i se trouve le nombre de votes pour le candidats i
    for(int i = 0;i<l->nbCandidats;i++){
        int nbVoteCandidats=recupererVoteCadidat(i,l,tabVoteCandidats);
        trierTableau(tabVoteCandidats[i],nbVoteCandidats);
        tabNbVoteCandidats[i]=nbVoteCandidats;
    }
    int indiceGagnant = voteJM((int ** )tabVoteCandidats,tabNbVoteCandidats,tailleTabCandidats,l);
    afficheMethode("jugement majoritaire",l->nbCandidats,l->size,l->nomCandidats,indiceGagnant);
    for (int i = 0; i < tailleTabCandidats; i++) {
        free(tabVoteCandidats[i]);
    }
    free(tabVoteCandidats);
}

int voteJM(int * tabVoteCandidats[],int tabNbVoteCandidats[],int nbCandidats,List * l){
    if(nbCandidats==1){
        printf("Sortie 1\n");
        return 0;
    }else{
        int tabMedianes[nbCandidats];
        for(int i =0;i<nbCandidats;i++){
            int indiceDim2 = (tabNbVoteCandidats[i]/2);
            tabMedianes[i] = tabVoteCandidats[i][indiceDim2];
        }
        minRes resultat;
        resultat.indicesMinV = malloc(nbCandidats*sizeof(int));
        resultat.MinV = -1;
        resultat.nbIndices=0;
        
        trouverMinimum(tabMedianes,nbCandidats,&resultat);
        printf("Les candidats a avoir la médiane la plus base sonts : \n");
        for(int i = 0; i<resultat.nbIndices;i++){
            printf("    - %s\n",l->nomCandidats[resultat.indicesMinV[i]]);
        }
        printf("Ces candidats ont eu la mention : ");
        afficherMentionCandidats(resultat.MinV);
        if(resultat.nbIndices ==1){
            int res = resultat.indicesMinV[0];
            free(resultat.indicesMinV);
            return res;
        }else{
            bool trouve = false;
            int cpt = 0;
            while (!trouve&&cpt<nbCandidats/2){
                cpt++;
                for(int i = 0; i<resultat.nbIndices;i++){ // indicesMinV[i] = candidats avec une mediane minimale
                    int indiceRecherche =(tabNbVoteCandidats[resultat.indicesMinV[i]]/2)-cpt;
                    if(tabVoteCandidats[resultat.indicesMinV[i]][indiceRecherche]<resultat.MinV){
                        int res = resultat.indicesMinV[i];
                        free(resultat.indicesMinV);
                        return res;
                    }
                }
            }
            int res = resultat.indicesMinV[rand()%resultat.nbIndices];
            free(resultat.indicesMinV);
            return res;            
        }

    }
}

void trierTableau(int tab[],int tailleTab){
    for(int i = 0 ; i<tailleTab;i++){
        for(int j = i+1 ; j<tailleTab ; j++){
            if(tab[i]>tab[j]){
                int tmp = tab[i];
                tab[i]=tab[j];
                tab[j]=tmp;
            }
        }
    }
}


int recupererVoteCadidat(int i , List *l,int **tableau){
    int j = 0;
    for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
        switch(e->tabReponse[i]){
            case 1 : tableau[i][j] = 1 ;break;
            case 2 : tableau[i][j] = 2 ;break;
            case 3 : tableau[i][j] = 2 ;break;
            case 4 : tableau[i][j] = 3 ;break;
            case 5 : tableau[i][j] = 3 ;break;
            case 6 : tableau[i][j] = 4 ;break;
            case 7 : tableau[i][j] = 4 ;break;
            case 8 : tableau[i][j] = 5 ;break;
            case 9 : tableau[i][j] = 5 ;break;
            default : tableau[i][j] = 6 ;break;
        }
        j++;
    }
    return j;
}

void afficherMentionCandidats(int i){
    switch(i){
        case 1 : printf("TB");break;
        case 2 : printf("B");break;
        case 3 : printf("AB");break;
        case 4 : printf("P");break;
        case 5 : printf("M");break;
        case 6 : printf("F");break;
        default :break;
    }
    printf(" ");
}

void trouverMinimum(int tableau[], int taille,minRes * resultat) {
    resultat->MinV = tableau[0];
    resultat->nbIndices = 0;
    for (int i = 1; i < taille; ++i) {
        if (tableau[i] < resultat->MinV) {
            resultat->MinV = tableau[i];
            resultat->nbIndices = 0;
        }
        if (tableau[i] == resultat->MinV) {
            resultat->indicesMinV[resultat->nbIndices] = i;
            ++resultat->nbIndices;
        }
    }

}