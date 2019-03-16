#include "main.h"

void goToLine(int ligne, FILE* file){
    rewind(file);

    char temp[20];

    for(int i=0; i<ligne; i++){
        fgets(temp, 20, file);
    }
}

int readGetNbPeniche(FILE* file){
    goToLine(0,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;

}

int readGetNbTrain(FILE* file){
    goToLine(1,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}

int readGetNbCamion(FILE* file){
    goToLine(2,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}

int readGetNbContPen(FILE* file){
    goToLine(3,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}

int readGetNbContTrain(FILE* file){
    goToLine(4,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}

int readGetNbContCamion(FILE* file){
    goToLine(5,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}

int readGetNbDestination(FILE* file){
    goToLine(6,file);
    char temp[2];
    fgets(temp, 2, file);
    int num=atoi(temp);
    return num;
}


int readGetIdDestination(int idTransporteur, FILE* file){
    goToLine(7,file);

    int num=0;
    char buf[2];

    for(int i=0; i<idTransporteur;i++) {
        fread(buf, 1, sizeof buf, file);
        fseek(file, 1, SEEK_CUR);
    }

    fread(buf, 1, sizeof buf, file);

    num=atoi(buf);

    return num;
}

int readGetContenaireDestination(int idTransporteur, int idContenaire, FILE* file){

    goToLine(9+idTransporteur,file);
    int num=0;
    char buf[2];

    for(int i=0; i<idContenaire;i++) {
        fread(buf, 1, sizeof buf, file);
        fseek(file, 1, SEEK_CUR);
    }

    fread(buf, 1, sizeof buf, file);

    num=atoi(buf);

    return num;

}

int readGetWaitingIdDestination(int idTransporteur, FILE* file){
    goToLine(7,file);

    int num=0;
    char buf[2];

    for(int i=0; i<data.nbTotalId+idTransporteur;i++) {
        fread(buf, 1, sizeof buf, file);
        fseek(file, 1, SEEK_CUR);
    }

    fread(buf, 1, sizeof buf, file);

    num=atoi(buf);

    return num;
}

int readGetContenaireWaitingDestination(int idTransporteur, int idContenaire, FILE* file){

    goToLine(9+data.maxCam+data.maxTrain+data.maxPen+idTransporteur+1,file);
    int num=0;
    char buf[2];

    for(int i=0; i<idContenaire;i++) {
        fread(buf, 1, sizeof buf, file);
        fseek(file, 1, SEEK_CUR);
    }

    fread(buf, 1, sizeof buf, file);

    num=atoi(buf);

    return num;

}

void readFile(){
    sharedData->file = NULL;
    sharedData->file = fopen("test.txt", "r+");
    if (sharedData->file != NULL) {
        data.maxPen = readGetNbPeniche(sharedData->file);
        data.maxTrain=readGetNbTrain(sharedData->file);
        data.maxCam=readGetNbCamion(sharedData->file);

        data.nbContPen=readGetNbContPen(sharedData->file);
        data.nbContTrain=readGetNbContTrain(sharedData->file);
        data.nbContCamion=readGetNbContCamion(sharedData->file);
        data.nbDestinations=readGetNbDestination(sharedData->file);
    }
    else
        printf("ouverture pb");
}

