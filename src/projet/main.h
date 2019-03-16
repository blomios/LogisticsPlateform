//
// Created by antho on 05/01/18.
//

#ifndef LO41CLION_MAIN_H
#define LO41CLION_MAIN_H

#endif //LO41CLION_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define IFLAGS (SEMPERM | IPC_CREAT)
#define SEMPERM 0600
#define PENICHE 1
#define CAMION 2
#define TRAIN 3
#define STOCK 4
#define NBSTOCK 15

typedef struct {
    int id;
    int idDestination;
    int x;
    int y;
} Contenaire;


typedef struct Transporteur Transporteur;
struct Transporteur{
    int idTransporteur;
    int idDestination;
    int type;
    Contenaire listeContenaires[NBSTOCK];
};

typedef struct {
    int idTransporteurDestinataire;
    int idEmplacementDestinataire;
    int idCallerTransporteur;
    int idContenaireToMove;
} InfoToMove;

typedef struct {
    int idPortique;
    int semToCall;
    int semToStart;
    InfoToMove infoToMoveContenaire;

    int y;
    int semMove;
} Portique;

typedef struct {
    int nbProcessBloque;
    char bufferDisplayer[5][60];
    int posPortique0;
    int posPortique1;
    int bloquerPortique0;
    int bloquerPortique1;
    int mod;
    int vitessePortique;
    FILE* file;
} SharedData;

typedef struct Data Data;
struct Data{
    int nbDestinations;
    int maxPen;
    int maxCam;
    int maxTrain;
    int nbContPen;
    int nbContCamion;
    int nbContTrain;
    int nbTotalId;
    int nbTotalSem;
    int memid;
    int memPortique;
    int memCamionWaiting;
    int memSharedData;
    int nbMaxCont;

    int sem_id ;
    int semContenaire_id;
    int semDisplayer_id;
    int semPosy_id;

    struct sembuf sem_oper_P ;  /* Operation P */
    struct sembuf sem_oper_V ;  /* Operation V */

    struct sembuf sem_oper_Pcontenaire ;  /* Operation P */
    struct sembuf sem_oper_Vcontenaire ;  /* Operation V */

    struct sembuf sem_oper_Pdisplayer ;  /* Operation P */
    struct sembuf sem_oper_Vdisplayer ;  /* Operation V */

    struct sembuf sem_oper_Pposy ;  /* Operation P */
    struct sembuf sem_oper_Vposy ;  /* Operation V */
};


Data data;

union semun {
    int val;
    struct semid_ds *stat;
    ushort * array;
} ctl_arg;

Transporteur *identificationTab;
Transporteur *camionWaiting;
Portique *portiqueTab;
SharedData *sharedData;

void readFile();

void rotationTransporteurs(int idTransporteur,int idSecTransporteur);

int readGetContenaireWaitingDestination(int idTransporteur, int idContenaire, FILE* file);

int readGetWaitingIdDestination(int idTransporteur, FILE* file);

void pushCamion();

void displayer2();

int readGetIdDestination(int idTransporteur, FILE* file);

int readGetContenaireDestination(int idTransporteur, int idContenaire, FILE* file);

void setPosContenaire(int idTransporteur, int idContenaire);

void debloquerProcess(int semWaitResumeTest);

int getNbMaxCont();

int getNbContenaires(int type);

int rand_a_b(int a, int b);

void initStockSpace();

int getIdDestination();

int getMaxY();

void initPosPortique(int idPortique);

void portique(int semToStart, int semToCall, int idPortique, int semWaitResumeTest);

InfoToMove getMove(int idTransporteur);

int emptyStockSpace();

void initNouveauTransport(int id, int type, int semWaitResumeTest);

void godLike();

void Pportique(int semnum);

void Vportique(int semnum);

void Pposy(int semnum);

void Vposy(int semnum);

void Pdisplayer(int semnum);

void Vdisplayer(int semnum);

void Pcontenaire(int semnum);

void Vcontenaire(int semnum);

void displayInfo(char* info);

void clearScreen();

void displayer();

void nouvelleCargaison(int idTransporteur);

void fairePartirTransporteur(int idTransporteur);

int checkToDeliver(int idTransporteur);

void checkDechargement(int idTransporteur, int idPortique, int semWaitResumeTest);