#include "main.h"

void nouvelleCargaison(int idTransporteur){

    if(sharedData->mod==0){
        srand(time(NULL) ^ getpid());//on reinitialise le random pour ne pas avoir les meme valeurs lorsque plusieurs process s'executent en parallele
        for(int i=0;i<getNbContenaires(identificationTab[idTransporteur].type);i++){
            if (rand_a_b(0, 4) != 4) {
                int random = getIdDestination();
                identificationTab[idTransporteur].listeContenaires[i].idDestination = random;
            } else {
                identificationTab[idTransporteur].listeContenaires[i].idDestination = -1;
            }
        }
    }
    else{
        for(int i=0;i<getNbContenaires(identificationTab[idTransporteur].type);i++){
            identificationTab[idTransporteur].listeContenaires[i].idDestination=readGetContenaireDestination(idTransporteur,i,sharedData->file);
        }
    }
}

void fairePartirTransporteur(int idTransporteur){

    if(sharedData->mod==0){


        if(identificationTab[idTransporteur].type==CAMION){
            rotationTransporteurs(idTransporteur, 0);
            pushCamion();
        }

        else{
            for (int i = 0; i < getNbContenaires(identificationTab[idTransporteur].type); i++) {
                identificationTab[idTransporteur].listeContenaires[i].idDestination = -1;
            }

            srand(time(NULL) ^ getpid());
            identificationTab[idTransporteur].idDestination = getIdDestination();

            nouvelleCargaison(idTransporteur);
        }
    }
}

void rotationTransporteurs(int idTransporteur,int idSecTransporteur){
    int idDestTemp=identificationTab[idTransporteur].idDestination;
    int idContDestTemp=identificationTab[idTransporteur].listeContenaires[0].idDestination;

    identificationTab[idTransporteur].idDestination=camionWaiting[idSecTransporteur].idDestination;
    identificationTab[idTransporteur].listeContenaires[0].idDestination=camionWaiting[idSecTransporteur].listeContenaires[0].idDestination;

    camionWaiting[idSecTransporteur].idDestination=idDestTemp;
    camionWaiting[idSecTransporteur].listeContenaires[0].idDestination=idContDestTemp;
}

void pushCamion(){

    for(int i=0; i<data.maxCam-1; i++){

        camionWaiting[i].idDestination=camionWaiting[i+1].idDestination;
        camionWaiting[i].listeContenaires[0].idDestination=camionWaiting[i+1].listeContenaires[0].idDestination;
    }
    srand(time(NULL) ^ getpid());
    camionWaiting[data.maxCam-1].idDestination=getIdDestination();
    camionWaiting[data.maxCam-1].listeContenaires[0].idDestination=getIdDestination();
}

int checkToDeliver(int idTransporteur){
    //Verifie si la cargaison est pleine ou non

    int nbContToDistrib=0;

    for(int i=0;i<getNbContenaires(identificationTab[idTransporteur].type);i++){
        if(identificationTab[idTransporteur].listeContenaires[i].idDestination != identificationTab[idTransporteur].idDestination || identificationTab[idTransporteur].listeContenaires[i].idDestination == -1){
            nbContToDistrib++;
        }
    }

    return nbContToDistrib;
}

void checkDechargement(int idTransporteur, int idPortique, int semWaitResumeTest){
    if(!fork()){

        int bloque=0;
        //Tant qu on a une cargaison a distribuer
        for(;;){

            if(checkToDeliver(idTransporteur)==0){

                displayInfo("Transporteur qui part");

                fairePartirTransporteur(idTransporteur);

            }

            if(bloque==1){
                Pportique(semWaitResumeTest);
                bloque=0;
            }

            Pportique(6+idPortique);

            InfoToMove move=getMove(idTransporteur);

            if(move.idTransporteurDestinataire!=-1 && move.idEmplacementDestinataire!=-1 && move.idContenaireToMove!=-1){

                portiqueTab[idPortique].infoToMoveContenaire=move;
                Vportique(portiqueTab[idPortique].semToStart);
            }

            else{
                //printf("rien trouvé :/\n");
                Pportique(5);
                sharedData->nbProcessBloque++;
                //printf("ajout d'un process bloqué: %d\n", sharedData->nbProcessBloque);
                bloque=1;
                Vportique(5);
                Vportique(8);
                Vportique(portiqueTab[idPortique].semToCall);
            }
        }
    }
}

void setPosContenaire(int idTransporteur, int idContenaire){
    int x=0;
    int y=0;
    if(identificationTab[idTransporteur].type==PENICHE){
        if(idTransporteur>=data.maxPen/2){
            x=3;
            y=(idTransporteur-((data.maxPen/2)))*(data.nbContPen+1)+idContenaire;
        }
        else {
            x=1;
            y=idTransporteur*(data.nbContPen+1)+idContenaire;
        }
    }
    else if(identificationTab[idTransporteur].type==CAMION){
        x=9;
        y=(idTransporteur-data.maxPen)*(data.nbContCamion+1)+idContenaire;
    }
    else if(identificationTab[idTransporteur].type==TRAIN){
        x=6;
        y=(idTransporteur-data.maxPen-data.maxCam)*(data.nbContTrain+1)+idContenaire;
    }

    else if(identificationTab[idTransporteur].type==STOCK){
        x=idContenaire%5+12;
        y=idContenaire/5+2;
    }

    identificationTab[idTransporteur].listeContenaires[idContenaire].x=x;
    identificationTab[idTransporteur].listeContenaires[idContenaire].y=y+1;

}


void initNouveauTransport(int id, int type, int semWaitResumeTest){



    identificationTab[id].idTransporteur=id;
    identificationTab[id].type=type;

    if(sharedData->mod==0) {
        srand(time(NULL) ^ getpid());
        identificationTab[id].idDestination = getIdDestination();
    }
    else
    {

        identificationTab[id].idDestination = readGetIdDestination(id,sharedData->file);
        printf("%d \n",readGetIdDestination(id,sharedData->file));
    }

    nouvelleCargaison(id);

    for (int i = 0; i < getNbContenaires(identificationTab[id].type); i++) {
        setPosContenaire(id, i);
    }



    checkDechargement(id, 0, semWaitResumeTest);
    checkDechargement(id, 1, semWaitResumeTest);
}