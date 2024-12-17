/**
 * @file csv.h
 * @author Gabriel Basso(sendtomadgab@gmail.com)| Robin Pujol (pujol.robin31@gmail.com)
 * @brief Implementation de csv.h
 * @version 1.0
 * @date 2023-11-25
 *
 * @copyright Copyright (c) 2023
 */

/*************************** FICHIERS D'ENTÊTE ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"


/*************************** DÉFINITION FONCTION ***************************/

List* extractCSVFile(const char *filename)
{
  FILE *file = fopen(filename,"r");
  if (!file) {
    perror("Error opening file");
    exit(1);
  }
  char line[1024];
  List* l = list_create();
  char* token;

  char** tabCandidat = NULL;
  fgets(line,sizeof(line),file);
  int n = 0;
  token = strtok(line,",");
  while(token!=NULL){
    if(n>3){
      tabCandidat = realloc(tabCandidat,(n-3)*sizeof(char*));
      tabCandidat[n-4]=(char*)malloc((strlen(token)+1)*sizeof(char));
      strcpy(tabCandidat[n-4],token);
    }
    token = strtok(NULL,",");
    n++;
  }
  int nbCandidat = n - 4;
  l->nomCandidats= (char**)malloc(nbCandidat*sizeof(char*));
  for (int i = 0; i < nbCandidat; i++)
  {
    char * pointeur = strchr(tabCandidat[i],'\n');
    if(pointeur !=NULL){
      *pointeur = ' ';
    }
    l->nomCandidats[i] = (char*)malloc((strlen(tabCandidat[i])+1)*sizeof(char));
    l->nomCandidats[i] = tabCandidat[i];
  }
  l->nbCandidats=nbCandidat;
  int* tab = malloc(sizeof(int)*nbCandidat);
  while (fgets(line,sizeof(line),file))
  {
    token=strtok(line,",");
    char* idRep=(char*)malloc((strlen(token)+1)*sizeof(char));
    strcpy(idRep,token);
    token=strtok(NULL,",");
    char* date=(char*)malloc((strlen(token)+1)*sizeof(char));
    strcpy(date,token);
    token=strtok(NULL,",");
    char* idCours=(char*)malloc((strlen(token)+1)*sizeof(char));
    strcpy(idCours,token);
    token=strtok(NULL,",");
    char* idParticipant=(char*)malloc((strlen(token)+1)*sizeof(char));
    strcpy(idParticipant,token);
    for(int i = 0 ; i < nbCandidat ; i++){
      token = strtok(NULL,",");
      char* num = (char*)malloc((strlen(token)+1)*sizeof(char));
      strcpy(num,token);
      tab[i] = atoi(num);
      free(num);
    }
    list_push_back(l,idRep,date,idCours,idParticipant,tab);
  }
  free(tab);
  free(tabCandidat);
  fclose(file);
  return l;
}

List* extractCSVMat(const char *filename){
  FILE *file = fopen(filename,"r");
  if (!file) {
    perror("Error opening file");
    exit(1);
  }
  char line[1024];
  List* l = list_create();
  char* token;
  char** tabCandidat = NULL;
  fgets(line,sizeof(line),file);
  int n = 0;
  token = strtok(line,",");
  while(token!=NULL){
    tabCandidat = realloc(tabCandidat,(n+1)*sizeof(char*));
    tabCandidat[n]=(char*)malloc((strlen(token)+1)*sizeof(char));
    strcpy(tabCandidat[n],token);
    token = strtok(NULL,",");
    n++;
  }
  int nbCandidat = n ;
  l->nomCandidats= (char**)malloc(nbCandidat*sizeof(char*));
  for (int i = 0; i < nbCandidat; i++)
  {
    char * pointeur = strchr(tabCandidat[i],'\n');
    if(pointeur !=NULL){
      *pointeur = ' ';
    }
    l->nomCandidats[i] = (char*)malloc((strlen(tabCandidat[i])+1)*sizeof(char));
    l->nomCandidats[i] = tabCandidat[i];
  }
  l->nbCandidats=nbCandidat;
  int* tab = malloc(sizeof(int)*nbCandidat);
  while (fgets(line,sizeof(line),file))
  {
    token = strtok(line,",");
    for(int i = 0 ; i < nbCandidat ; i++){
      char* num = (char*)malloc((strlen(token)+1)*sizeof(char));
      strcpy(num,token);
      tab[i] = atoi(num);
      token = strtok(NULL,",");
      free(num);
    }
    char* idRep = malloc(2*sizeof(char));
    char* date = malloc(2*sizeof(char));
    char* idParticipant = malloc(2*sizeof(char));
    char* idCours = malloc(2*sizeof(char));
    strcpy(idRep," ");
    strcpy(date," ");
    strcpy(idParticipant," ");
    strcpy(idCours," ");
    list_push_back(l,idRep,date,idCours,idParticipant,tab);
  }
  free(tabCandidat);
  free(tab);
  fclose(file);
  return l;
}