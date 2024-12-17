/**
 * @file uninominale.c
 * @author  Emilien Sanchez (emilien.sanchez@univ-tlse3.fr)
 *          Robin Pujol (pujol.robin31@gmail.com)
 *          Robin Mounié (robin.mounie@gmail.com)
 *          Gabriel Basso(sendtomadgab@gmail.com)
 *          
 * @brief Implementation de uninominale.h
 * @version 1.0
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 */

/*************************** FICHIER D'ENTÊTE ***************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <time.h>

#include "uninominale.h"


/*************************** FICHIER D'ENTÊTE ***************************/

void vote1(int* vote, int* res,int nbCandidat){
    int nbChoix = 0;
    int* choix = calloc(nbCandidat,sizeof(int));
    int minVote = min(vote,nbCandidat);
    for (int i = 0; i < nbCandidat; i++)
    {
        
        if (vote[i]== minVote){
            choix[nbChoix] =i;
            nbChoix ++;
        }
    }
    if (nbChoix >0){
        res[choix[aleatoire(nbChoix-1)]]++;
    }

}

void affUninominale1(int nbVoteTot,int* res,int indiceGagnant, char* nomB[]){
    float score = ((float)res[indiceGagnant]/ (float)nbVoteTot) *100;
	printf("Mode de scrutin : uninominal a un tour, 10 candidats, %d votants, vainqueur = %s, score = %.2f %% \n",nbVoteTot,nomB[indiceGagnant],score);
}


void indiceRes1(int* res, int* max,int nbCandidats){
    int ale;

    if (res[0]> res[1]){
        max[0] = 0; 
        max[1] = 1;
    }
    else if (res[0] < res[1])
    {
        max[0] = 1; 
        max[1] = 0;
    }
    else
    {
        max[0] = aleatoire(1); 
        max[1] = (max[0]+1)%2 ;
    }

    for (int i = 2; i < nbCandidats; i++)
    {
        
        if (res[i]>res[max[0]])
        {
            max[1] = max[0];
            max[0] = i;
        }
        else if (res[i] == res[max[0]])
        {
            ale = aleatoire(1);
            max[ale] = max[0];
            max [(ale +1)%2] = i ;
        }
        else if (res[i]>res[max[1]])
        {
            max[1] =i;        
        }
        else if (res[i] == res[max[1]])
        {
            if (aleatoire(1)){
                max[1] =i;
            }
        }
    }
}

void uninominale1 (List* l, int* max, int* res){
    srand(time(NULL));
    for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
		vote1(e->tabReponse, res,l->nbCandidats);
	}
    indiceRes1(res, max,l->nbCandidats);

}

void vote2(int* tabReponse,int* gagnantPremierTours,int* nbVoteCandidats ){
    int candidatA=tabReponse[gagnantPremierTours[0]];
    int candidatB=tabReponse[gagnantPremierTours[1]];
    if(candidatA==candidatB){
        nbVoteCandidats[aleatoire(1)]++;
    }else if(candidatA == -1){
        nbVoteCandidats[1]++;
    }else if(candidatB == -1){
        nbVoteCandidats[0]++;
    }else if(candidatA>candidatB){
        nbVoteCandidats[1]++;
    }else if (candidatA<candidatB){
        nbVoteCandidats[0]++;
    }
}

int indiceRes2(int* nbVoteCandidats,int* gagnantPremierTours){
    if(nbVoteCandidats[0]==nbVoteCandidats[1]){
    return gagnantPremierTours[aleatoire(1)];
    }else if(nbVoteCandidats[0]>nbVoteCandidats[1]){
        return gagnantPremierTours[0];
    }
    return gagnantPremierTours[1];
}
int uninominale2 (List* l){
    int* gagnantPremierTours = calloc(2,sizeof(int));
    int* nbVoteCandidats = calloc(2,sizeof(int));
    int* res = calloc(l->nbCandidats,sizeof(int));
    int nbVoteTot = l->size;
    float score;
    int gagnant;
    uninominale1(l,gagnantPremierTours,res);
    score = ((float)res[gagnantPremierTours[0]]/ (float)nbVoteTot) *100;
    printf("\nMode de scrutin : uninominal à deux tours, tour 1, 10 candidats, %d votants, vainqueur = %s, score : %.2f %%\n",list_size(l),l->nomCandidats[gagnantPremierTours[0]],score);
    score = ((float)res[gagnantPremierTours[1]]/ (float)nbVoteTot) *100;
    printf("Mode de scrutin : uninominal à deux tours, tour 1, 10 candidats, %d votants, vainqueur = %s, score : %.2f %%\n",list_size(l),l->nomCandidats[gagnantPremierTours[1]],score);
    for(LinkedElement* e = l->sentinel->next;e!=l->sentinel ;e=e->next){
       vote2(e->tabReponse,gagnantPremierTours,nbVoteCandidats);
    }
    gagnant= indiceRes2(nbVoteCandidats,gagnantPremierTours);
    score = ((float)nbVoteCandidats[gagnant]/ (float)nbVoteTot) *100;
    printf("\nMode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s ,score : %.2f %%\n",list_size(l),l->nomCandidats[gagnant],score);
    return gagnant;
}