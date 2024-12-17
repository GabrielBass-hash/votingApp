/** @file main.c
* @author Robin Pujol (pujol.robin31@gmail.com) | Emilien Sanchez (emilien.sanchez@univ-tlse3.fr)
* @brief Fonction main du programme
* @version 1.0
* @date 2023-11-23
* 
* @copyright Copyright (c) 2023
*
*/


/*************************** FICHIERS D'ENTÊTE ***************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "list.h"
#include "utils_sd.h"
#include "csv.h"
#include "verify_vote.h"
#include "sha256.h"
#include "sha256_utils.h"
#include "uninominale.h"
#include "condorcet_minimax.h"
#include "condorcet_pairs.h"
#include "condorcet_schulze.h"
#include "JugementMajoritaire.h"
#include "list_circuit.h"


/*************************** MACRO ***************************/
#define TAILLE_MAX 50


/*************************** FONCTIONS ***************************/
/**
 * @brief Fonction permettant de mettre un string en majuscule (et sa variante en minuscule)
 * 
 * @param dest 
 * @param src 
 * @return char * 
 */
char *strtoupper(const char * string){

    char * res = malloc(sizeof(string));
    strcpy(res,string);

    for(int i = 0; i < strlen(res); i++) {
        res[i] = toupper(res[i]);
    }

    return res;
}
char *strtolower(const char * string){

    char * res = malloc(sizeof(string));
    strcpy(res,string);

    for(int i = 0; i < strlen(res); i++) {
        res[i] = tolower(res[i]);
    }

    return res;
}


/**
 * @brief Affichage de la fonction de verification
 * (Demande les informations nécessaire à l'utilisateur afin de retrouver son vote)
 * 
 */
void affichageVerification(){

    // Définition des types des variables
    char hashRes[SHA256_BLOCK_SIZE*2 + 1]; 
    char* nom=(char*)malloc(20);
	char* prenom=(char*)malloc(20);
	char* nomPrenom=(char*)malloc(sizeof(nom)+sizeof(prenom));
	char* clef=(char*)malloc(15);
    char* choix_fichier=(char*)malloc(1) ;
    char* fichier=(char*)malloc(30);
    LinkedElement* res;
    
	printf("Entrez votre nom : \n");
	scanf("%s",nom);
    char * nomMaj = strtoupper(nom);

	printf("Entrez votre prenom : \n");
	scanf("%s",prenom);

    //char * prenomMin = strtolower(prenom);
    //prenomMin[0] = toupper(prenomMin[0]);

	strcpy(nomPrenom,nomMaj);
	strcat(nomPrenom," ");
	strcat(nomPrenom,prenom);

	printf("Entrez votre clef pour ce vote : \n");
	scanf("%s",clef);
    
    printf("Choix du fichier, Jugement ou Condorcet ?(j/c)\n");
    do{
        scanf("%s", choix_fichier);
        if (*choix_fichier == 'j')
        {
            fichier = "./fichiers/jugement.csv";
        }
        else if (*choix_fichier =='c')
        {
            fichier = "./fichiers/VoteCondorcet.csv";
        }
        else
        {
            perror("Choix du fichier incorrect !");
        }
    } while ((*choix_fichier != 'j') && (*choix_fichier != 'c')) ;

    hasheVotant( nomPrenom, clef, hashRes);
    res = search_vote(fichier, hashRes);
    if (res){
        affVote(res);
    }
    else{
        printf("Votre code \"%s%s\" hashe:(%s) n'existe pas dans le fichier %s.\n",nomPrenom,clef,hashRes,choix_fichier);
    }
}


/*************************** MAIN ***************************/

/**
 * @brief Fonction main de notre programme
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {
    int opt;
    char *fichierVote = (char*)malloc(sizeof(char)*50);
    char *fichierLog = (char*)malloc(sizeof(char)*50);
    char *tabElem[8];
    int aFichierVote = 0;
    int aFichierLog = 0;
    int voteBallots = 0;
    int matricesDuel = 0;
    int nbElem = 0;
    int uni1 = 0;
    int uni2 = 0;
    int cm = 0;
    int cp = 0;
    int cs = 0;
    int jm = 0;
    int all = 0;
    int descLog =0;
    while ((opt = getopt(argc, argv, "i:d:o:m:hv")) != -1) {
        switch (opt) {
            case 'i':
                if(!aFichierVote){
                    strcpy(fichierVote,optarg);
                    aFichierVote++;
                    voteBallots++;
                }
                else{
                    printf("Il y a deja un fichier de vote pris en comptre arret du processus\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd':
                if(!aFichierVote){
                    strcpy(fichierVote,optarg);
                    aFichierVote++;
                    matricesDuel++;
                }
                else{
                    printf("Il y a deja un fichier de vote pris en comptre arret du processus\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'o':
                if(!aFichierLog){
                    strcpy(fichierLog,optarg);
                    aFichierLog++;
                }
                else{
                    printf("Il y a deja un fichier de log pris en comptre arret du processus\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                tabElem[nbElem] = optarg;
                nbElem++;
                while(optind < argc && *argv[optind] != '-'){
                    tabElem[nbElem] = argv[optind];
                    nbElem++;
                    if(nbElem >= 8){
                        printf("Il y a trop d'argument pris en compte arret du processus\n");
                        exit(EXIT_FAILURE);
                    }
                    optind++;
                }
                break;
            case 'v':
                affichageVerification();
                break;
            case 'h':
                printf("Usage : %s -i/d ./fichiers/<nom>.csv -o <nom>.txt -m {uni1,uni2,cm,cp,cs,jm,all} -v -h\n",argv[0]);
                printf("Faites attention pour le fichier csv de bien mettre le bon chemin ex : -d ./fichiers/2012.csv\n");
                printf("Et pour le fichier de log de bien mettre un .txt\n");
                printf("-i fichiers de vote par ballots\n-d fichier de matrices de duel\n-o fichier de log ou sera ecris les calculs\n-m les methodes a utiliser\n-h help\n-v pour verifier son vote\n");
                exit(0);
                break;
            case '?':
                printf("Balise non reconnue arret du processus\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    for (; optind < argc; optind++) {
        printf("Il y a des argument en trop arret du processus\n");
        exit(EXIT_FAILURE);
    }
    if(!aFichierVote){
        printf("Il n'y a pas de fichier de vote/matrice de duel pris en compte arret du processus\n");
        exit(EXIT_FAILURE);
    }
    if(!nbElem){
        printf("Il n'y a pas de methodes de vote pris en compte arret du processus\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0 ; i < nbElem && !all; i++){
        if(!strcmp(tabElem[i],"uni1")){
            if(matricesDuel){
                printf("La methode %s ne peut pas etre appliquer sur des matrices de duel arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
            else if(!uni1){
                uni1++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"uni2")){
            if(matricesDuel){
                printf("La methode %s ne peut pas etre appliquer sur des matrices de duel arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
            else if(!uni2){
                uni2++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"cm")){
            if(!cm){
                cm++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"cp")){
            if(!cp){
                cp++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"cs")){
            if(!cs){
                cs++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"jm")){
            if(matricesDuel){
                printf("La methode %s ne peut pas etre appliquer sur des matrices de duel arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
            else if(!jm){
                jm++;
            }
            else{
                printf("La methode %s est deja present parametre incorect arret du processus\n",tabElem[i]);
                exit(EXIT_FAILURE);
            }
        }
        else if(!strcmp(tabElem[i],"all")){
            if(voteBallots){
                uni1 = 1;
                uni2 = 1;
                cm = 1;
                cp = 1;
                cs = 1;
                jm = 1;
                all = 1;
            }
            else{
                uni1 = 0;
                uni2 = 0;
                cm = 1;
                cp = 1;
                cs = 1;
                jm = 0;
                all = 1;
            }
        }
        else{
            printf("%s n'est pas reconnue comme methode arret du processus\n",tabElem[i]);
            exit(EXIT_FAILURE);
        }
    }
    if(aFichierLog){
        
        if((descLog = open(fichierLog,O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR)) == -1){
            perror("Erreur lors de l'ouverture ou la creation du fichier");
            exit(EXIT_FAILURE);
        }
        dup2(descLog,STDOUT_FILENO);
    }
    List* list;
    mat_duel* matDuel;
    int gagnantSansParadoxe;
    if(voteBallots){
        list = extractCSVFile(fichierVote);
        matDuel = genererMatDuel(list);
    }
    else{
        list = extractCSVMat(fichierVote);
        matDuel = copieMatDuel(list);
    }
    if(uni1){
        int* max = calloc(2,sizeof(int));
        int* tab_res = calloc(list->nbCandidats,sizeof(int));
        printf("Debut des calcul pour uninominale 1:\n");
        uninominale1(list, max, tab_res);
        affUninominale1(list->size, tab_res, max[0], list->nomCandidats);
        free(max);
        free(tab_res);
    }
    if(uni2){
        printf("Debut des calcul pour uninominale 2:\n");
        uninominale2(list);
    }
    if(cm){
        if((gagnantSansParadoxe = vainqueurCondorcet(matDuel))==-1){
            printf("Debut des calcul pour condorcet minimax:\n");
            condorcetMinimax(matDuel);
        }
        else{
            printf("Il y a un vainqueur de condorcet donc on ne feras pas la methodes condorcet minimax\n");
            afficheMethode("Condorcet",matDuel->nbCandidats,matDuel->nbVotant,matDuel->nomCandidat,gagnantSansParadoxe);
        }
    }
    if(cp){
        if((gagnantSansParadoxe = vainqueurCondorcet(matDuel))==-1){
            printf("Debut des calcul pour condorcet pair:\n");
            condorcetPair(matDuel);
        }
        else{
            printf("Il y a un vainqueur de condorcet donc on ne feras pas la methodes condorcet paire\n");
            afficheMethode("Condorcet",matDuel->nbCandidats,matDuel->nbVotant,matDuel->nomCandidat,gagnantSansParadoxe);
        }
    }
    if(cs){
        if((gagnantSansParadoxe = vainqueurCondorcet(matDuel))==-1){
            printf("Debut des calcul pour condorcet schulze:\n");
            condorcetSchulze(matDuel);
        }
        else{
            printf("Il y a un vainqueur de condorcet donc on ne feras pas la methodes condorcet schulze\n");
            afficheMethode("Condorcet",matDuel->nbCandidats,matDuel->nbVotant,matDuel->nomCandidat,gagnantSansParadoxe);
        }
    }
    if(jm){
        printf("Debut des calcul pour jugement majoritaire:\n");
        jugementMajoritaire(list);
    }
    free(fichierLog);
    free(fichierVote);
    list_delete(&list);
    matrice_delete(&matDuel);
    close(descLog);
    return 0;
}
