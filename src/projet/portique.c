#include "main.h"

void movePortiqueTo(int posDest, int idPortique){

    if(idPortique==0) {
        while(posDest!=sharedData->posPortique0) {
            usleep(sharedData->vitessePortique);
            Pposy(0);
            if (posDest > sharedData->posPortique0 && sharedData->bloquerPortique0 == 0) {
                if(sharedData->posPortique1==sharedData->posPortique0+1) {
                    sharedData->bloquerPortique1=1;
                    sharedData->posPortique1++;
                }
                sharedData->posPortique0++;
                Vdisplayer(0);
                //printf("%d , %d\n", sharedData->posPortique0,sharedData->posPortique1);

            } else if (posDest < sharedData->posPortique0 && sharedData->bloquerPortique0 ==0) {
                if(sharedData->posPortique1==sharedData->posPortique0-1) {
                    sharedData->bloquerPortique1=1;
                    sharedData->posPortique1--;
                }
                sharedData->posPortique0--;
                Vdisplayer(0);
                //printf("%d , %d\n", sharedData->posPortique0,sharedData->posPortique1);
            }
            Vposy(0);
        }

        if(sharedData->bloquerPortique1==1){
            sharedData->bloquerPortique1=0;
        }
    }

    else{
        while(posDest!=sharedData->posPortique1) {
            usleep(sharedData->vitessePortique);
            Pposy(0);
            if (posDest > sharedData->posPortique1 && sharedData->bloquerPortique1 ==0) {
                if (sharedData->posPortique0 == sharedData->posPortique1 + 1) {
                    sharedData->bloquerPortique0 = 1;
                    sharedData->posPortique0++;
                }
                sharedData->posPortique1++;
                Vdisplayer(0);
                //printf("%d , %d\n", sharedData->posPortique0,sharedData->posPortique1);

            } else if (posDest < sharedData->posPortique1 && sharedData->bloquerPortique1 ==0) {
                if (sharedData->posPortique0 == sharedData->posPortique1 - 1) {
                    sharedData->bloquerPortique0 = 1;
                    sharedData->posPortique0--;
                }
                sharedData->posPortique1--;
                Vdisplayer(0);
                //printf("%d , %d\n", sharedData->posPortique0,sharedData->posPortique1);
            }
            Vposy(0);
        }

        if(sharedData->bloquerPortique0==1){
            sharedData->bloquerPortique0=0;
        }
    }
}

void initPosPortique(int idPortique){
    sharedData->bloquerPortique1=0;
    sharedData->bloquerPortique0=0;
    if(idPortique==0){

        int max=getMaxY();
        sharedData->posPortique0=max;

    }
    else if(idPortique==1){
        sharedData->posPortique1=0;
    }
}

void portique(int semToStart, int semToCall, int idPortique, int semWaitResumeTest){
    //se deplace vers le transporteur qui doit decharger son contenaire
    if(!fork()){
        for(;;){
            Pportique(semToStart);//Semaphore pour demarrer le processus de deplacement de contenaire


            int idTransporteurDestinataire=portiqueTab[idPortique].infoToMoveContenaire.idTransporteurDestinataire;
            int idEmplacementDestinataire=portiqueTab[idPortique].infoToMoveContenaire.idEmplacementDestinataire;
            int idCallerTransporteur=portiqueTab[idPortique].infoToMoveContenaire.idCallerTransporteur;
            int idContenaireToMove=portiqueTab[idPortique].infoToMoveContenaire.idContenaireToMove;

            int destCont=identificationTab[idCallerTransporteur].listeContenaires[idContenaireToMove].idDestination;


            movePortiqueTo(identificationTab[idCallerTransporteur].listeContenaires[idContenaireToMove].y,idPortique);

            //Pportique(portiqueTab[idPortique].semMove);


            //Notifie le dechargement
            identificationTab[idCallerTransporteur].listeContenaires[idContenaireToMove].idDestination=-1;

            displayInfo("dechargement terminé");
            Vdisplayer(0);

            Vcontenaire(idCallerTransporteur*data.nbMaxCont+idContenaireToMove);

            //Se deplace vers le transporteur a charger

            //printf("Le transporteur %d prend un contenaire et le met a l'emplacement %d\n",idTransporteurDestinataire, idEmplacementDestinataire)

            movePortiqueTo(identificationTab[idTransporteurDestinataire].listeContenaires[idEmplacementDestinataire].y,idPortique);

            identificationTab[idTransporteurDestinataire].listeContenaires[idEmplacementDestinataire].idDestination=destCont;

            //printf("test: %d\n", identificationTab[idTransporteurDestinataire].listeContenaires[idEmplacementDestinataire]);
            Vcontenaire(idTransporteurDestinataire*data.nbMaxCont+idEmplacementDestinataire);



            displayInfo("chargement terminé");
            Vdisplayer(0);
            Vportique(semToCall); //Semaphore pour appeler un nouveau transporteur
            debloquerProcess(semWaitResumeTest);
            //printf("portique rendu\n");
        }

        exit(0);
    }
}