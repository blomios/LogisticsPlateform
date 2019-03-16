#include "main.h"

void debloquerProcess(int semWaitResumeTest){
    Pportique(5);
    displayInfo("deblocage des process");
    for(int i=0; i<sharedData->nbProcessBloque; i++){
        Vportique(semWaitResumeTest);
    }
    sharedData->nbProcessBloque=0;
    Vportique(5);
}

int getMaxY(){
    int max=NBSTOCK/5;
    if((getNbContenaires(PENICHE)+1)*ceil(data.maxPen/2.0)>max) {
        max=(getNbContenaires(PENICHE)+1)*ceil(data.maxPen/2.0);
    }
    if((getNbContenaires(TRAIN)+1)*data.maxTrain>max) {
        max=(getNbContenaires(TRAIN)+1)*data.maxTrain;
    }
    if((getNbContenaires(CAMION)+1)*data.maxCam>max) {
        max=(getNbContenaires(CAMION)+1)*data.maxCam;
    }

    return max+1;
}

int getIdDestination(){

    int random=rand()%(data.nbDestinations+1);
    return random;

}

int getNbMaxCont(){
    int nbMaxCont=data.nbContPen;
    if(data.nbContTrain>nbMaxCont) nbMaxCont=data.nbContTrain;
    if (data.nbContCamion>nbMaxCont) nbMaxCont=data.nbContCamion;

    return nbMaxCont;
}

int rand_a_b(int a, int b){
    return (rand()%(b-a+1))+a;
}

int getNbContenaires(int type){
    if(type==PENICHE){
        return data.nbContPen;
    }

    else if(type==CAMION){
        return data.nbContCamion;
    }

    else if(type==TRAIN){
        return data.nbContTrain;
    }

    else if(type==STOCK){
        return NBSTOCK;
    }

    else return -1;
}