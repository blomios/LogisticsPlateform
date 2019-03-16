#include "main.h"

void displayInfo(char* info){
    char finalInfo[60];

    char* coul="\x1B[32m";

    switch(rand_a_b(0,4))
    {
        case 0:
            coul="\x1B[31m";
            break;

        case 1:
            coul="\x1B[32m";
            break;

        case 2:
            coul="\x1B[33m";
            break;

        case 3:
            coul="\x1B[34m";
            break;
        case 4:
            coul="\x1B[35m";
            break;
        default:
            coul="\x1B[32m";
            break;
    }

    sprintf(finalInfo,"%s%s",coul,info);

    int check=0;
    for(int i=0; i<5; i++){
        if(sharedData->bufferDisplayer[i]==NULL && check==0){
            strcpy(sharedData->bufferDisplayer[i],finalInfo);
            check=1;
        }
    }
    if(check==0){
        for(int i=0; i<4; i++){
            strcpy(sharedData->bufferDisplayer[i],sharedData->bufferDisplayer[i+1]);
        }
        strcpy(sharedData->bufferDisplayer[4],finalInfo);
    }
}

void clearScreen(){
    system("clear");
}

void displayer2(){
    int nbPerLigne=4;

    int nbLine=(int) ceil(data.nbTotalId/((double)nbPerLigne));

    if(!fork()){
        for(;;){
            Pdisplayer(0);
            clearScreen();
            for(int i=0;i<nbLine; i++){

                printf("\n");

                for(int l=0;l<nbPerLigne; l++){
                    if(identificationTab[i*nbPerLigne+l].idTransporteur==i*nbPerLigne+l && identificationTab[i*nbPerLigne+l].idDestination!=-1){
                        printf("      \x1B[32mT%d \x1B[31mdest:%d", identificationTab[i*nbPerLigne+l].idTransporteur, identificationTab[i*nbPerLigne+l].idDestination);
                    }
                    else{
                        printf("        ");
                    }
                }
                printf("\n");

                //printf("             \x1B[32mT%d \x1B[31mdest:%d       \x1B[32mT%d \x1B[31mdest:%d       \x1B[32mT%d \x1B[31mdest:%d\x1B[0m\n", identificationTab[i*nbPerLigne].idTransporteur, identificationTab[i*nbPerLigne].idDestination,identificationTab[i*nbPerLigne+1].idTransporteur, identificationTab[i*nbPerLigne+1].idDestination,identificationTab[i*nbPerLigne+2].idTransporteur, identificationTab[i*nbPerLigne+2].idDestination);
                for(int j=0; j<getNbMaxCont(); j++){
                    int contT1;
                    int contT2;
                    int contT3;

                    char *coul="\x1B[33m";


                    for(int k=0; k<nbPerLigne; k++){

                        if(identificationTab[i*nbPerLigne+k].type==TRAIN){
                            coul="\x1B[34m";
                        }
                        else if(identificationTab[i*nbPerLigne+k].type==CAMION){
                            coul="\x1B[35m";
                        }
                        else if(identificationTab[i*nbPerLigne+k].type==PENICHE){
                            coul="\x1B[33m";
                        }

                        if(j<getNbContenaires(identificationTab[i*nbPerLigne+k].type) && identificationTab[i*nbPerLigne+k].idDestination!=-1){
                            printf("            %s%d", coul,(char) identificationTab[i*nbPerLigne+k].listeContenaires[j].idDestination);
                        }
                        else{
                            printf("              ");
                        }

                    }
                    printf("\n");
                }
                printf("\n");

            }
            for(int countDisplayer=0; countDisplayer<5; countDisplayer++){
                printf("%s\n",sharedData->bufferDisplayer[countDisplayer]);
            }
            printf("\n");
            printf("\x1B[33mPeniche    \x1B[34mTrain     \x1B[35mCamion    \n");


        }
    }
}

void displayer(){
    if(!fork()) {

        int tailleX = 17;
        int tailleY = getMaxY();

        char grille[tailleX][tailleY][10];

        for (;;) {
            Pdisplayer(0);

            for (int i = tailleY; i > 0; i--) {
                for (int j = 0; j < tailleX; j++) {
                    strcpy(grille[j][i], "-2");
                }
            }



            for (int i = 0; i < data.nbTotalId; i++) {

                for (int j = 0; j < getNbContenaires(identificationTab[i].type); j++) {
                    int x = identificationTab[i].listeContenaires[j].x;
                    int y = identificationTab[i].listeContenaires[j].y;
                    int val = identificationTab[i].listeContenaires[j].idDestination;

                    char buff[10]; // Nombre maximal de chiffres + 1



                    sprintf(buff, "%d", val); // Conversion de l'entier

                    strcpy(grille[x][y], buff);
                }
            }

            for (int i = 0; i < data.maxCam; i++) {
                int x = camionWaiting[i].listeContenaires[0].x;
                int y = camionWaiting[i].listeContenaires[0].y;
                int val = camionWaiting[i].listeContenaires[0].idDestination;

                char buff[10]; // Nombre maximal de chiffres + 1

                sprintf(buff, "%d", val); // Conversion de l'entier

                strcpy(grille[x][y], buff);
            }

            for(int i=0; i<NBSTOCK; i++){
                int x = identificationTab[data.nbTotalId].listeContenaires[i].x;
                int y = identificationTab[data.nbTotalId].listeContenaires[i].y;
                int val = identificationTab[data.nbTotalId].listeContenaires[i].idDestination;

                char buff[10]; // Nombre maximal de chiffres + 1

                sprintf(buff, "%d", val); // Conversion de l'entier

                strcpy(grille[x][y], buff);
            }

            int posPortique0=sharedData->posPortique0;
            int posPortique1=sharedData->posPortique1;

            for(int i=0; i<tailleX; i++){
                strcpy(grille[i][posPortique0],"#1");
            }
            for(int i=0; i<tailleX; i++){

                strcpy(grille[i][posPortique1],"#2");
            }

            clearScreen();

            for (int i = tailleY; i >= 0; i--) {
                for (int j = 0; j < tailleX; j++) {

                    int num=atoi(grille[j][i]);
                    if(num>=0) printf(" ");

                    if (strcasecmp(grille[j][i], "-2")!=0) {

                        if(strcasecmp(grille[j][i], "#1")==0) strcpy(grille[j][i],"\x1B[35m#");
                        else if(strcasecmp(grille[j][i], "#2")==0) strcpy(grille[j][i],"\x1B[34m#");
                        printf("%s",grille[j][i]);

                    } else printf("  ");
                }
                printf("\n");
            }
        }
    }
}