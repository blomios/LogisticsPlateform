#include "main.h"

InfoToMove getMove(int idTransporteur){

    InfoToMove move;

    for(int i=0; i<getNbContenaires(identificationTab[idTransporteur].type); i++){

        Pcontenaire(idTransporteur*data.nbMaxCont+i);

        if(identificationTab[idTransporteur].listeContenaires[i].idDestination!=identificationTab[idTransporteur].idDestination && identificationTab[idTransporteur].listeContenaires[i].idDestination!=-1){

            for(int j=0; j<data.nbTotalId; j++){

                if(identificationTab[j].idTransporteur!=idTransporteur && identificationTab[idTransporteur].listeContenaires[i].idDestination==identificationTab[j].idDestination){

                    for(int k=0; k<getNbContenaires(identificationTab[j].type); k++){

                        Pcontenaire(j*data.nbMaxCont+k);

                        if(identificationTab[j].listeContenaires[k].idDestination==-1){
                            move.idTransporteurDestinataire=j;
                            move.idEmplacementDestinataire=k;
                            move.idCallerTransporteur=idTransporteur;
                            move.idContenaireToMove=i;
                            return move;
                        }

                        Vcontenaire(j*data.nbMaxCont+k);
                    }
                }
            }
        }

        Vcontenaire(idTransporteur*data.nbMaxCont+i);
    }

    move.idTransporteurDestinataire=-1;
    move.idEmplacementDestinataire=-1;
    move.idCallerTransporteur=-1;
    move.idContenaireToMove=-1;
    return move;
}

int getRotationCamion(){

    for(int i=0; i<data.nbTotalId; i++){
        for(int j=0; j<getNbContenaires(identificationTab[i].type); j++){

            /*if(identificationTab[i].listeContenaires[j].idDestination != identificationTab[i].idDestination){
                for(int k=0; k < data.maxCam; k++){
                    if()
                }
            }*/

            if(identificationTab[i].listeContenaires[j].idDestination==-1){
                for(int k=0; k < data.maxCam; k++){
                    if(camionWaiting[k].listeContenaires[0].idDestination==identificationTab[i].idDestination){
                        displayInfo("rotation Camion option 1");
                        //printf("%d ,  %d\n",camionWaiting[k].listeContenaires[0].idDestination, identificationTab[i].listeContenaires[0].idDestination);
                        if(i==data.maxPen+data.maxTrain){
                            if(data.maxCam==1){
                                return -1;
                            }
                            else{
                                rotationTransporteurs(data.maxPen+data.maxTrain+1,k);
                            }
                        }
                        else{
                            rotationTransporteurs(data.maxPen+data.maxTrain,k);
                        }

                        //printf("%d , %d \n",camionWaiting[k].listeContenaires[0].idDestination, identificationTab[i].listeContenaires[0].idDestination);
                        Pportique(5);
                        for (int i = 0; i < sharedData->nbProcessBloque; i++) {
                            Vportique(4);
                        }
                        sharedData->nbProcessBloque = 0;
                        Vportique(5);
                        sleep(1);
                        Vdisplayer(0);
                        return 1;
                    }
                }
            }
            else{
                if(identificationTab[i].listeContenaires[j].idDestination!=identificationTab[i].idDestination){
                    for(int k=0; k < data.maxCam; k++){
                        if(camionWaiting[k].idDestination==identificationTab[i].listeContenaires[j].idDestination && camionWaiting[k].listeContenaires[0].idDestination==-1){
                            displayInfo("rotation camion option 2");
                            if(i==data.maxPen+data.maxTrain){
                                if(data.maxCam==1){
                                    return -1;
                                }
                                else{
                                    rotationTransporteurs(data.maxPen+data.maxTrain+1,k);
                                }
                            }
                            else{
                                rotationTransporteurs(data.maxPen+data.maxTrain,k);
                            }
                            Pportique(5);
                            for (int i = 0; i < sharedData->nbProcessBloque; i++) {
                                Vportique(4);
                            }
                            sharedData->nbProcessBloque = 0;
                            Vportique(5);
                            sleep(1);
                            Vdisplayer(0);
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return -1;
}

void godLike(){

    if(!fork()){
        for(;;){
            Pportique(8);
            Pportique(5);
            if(sharedData->nbProcessBloque==data.nbTotalId*2){
                Vportique(5);

                int rotation=getRotationCamion();

                if(rotation==-1) {

                    if (sharedData->mod == 0) {
                        displayInfo("Godlike");

                        int optionChoosen = 0;

                        char a = 92;
                        //printf(" ########################################################################\n\n\n");
                        //printf(" \n _____           _ _     _ _        \n|  __ %c         | | |   (_) |    \n| |  %c/ ___   __| | |    _| | _____ \n| | __ / _ %c / _` | |   | | |/ / _ %c \n| |_%c %c (_) | (_| | |___| |   <  __/  \n %c____/%c___/ %c__,_%c_____/_|_|%c_%c___|  \n",a,a,a,a,a,a,a,a,a,a,a,a);
                        //printf(" \n\n\n########################################################################\n\n\n");

                        //printf("Blockage détécté! quelle action voulez-vous effectuer? \n");
                        //printf("0- Laisser partir le transporteur le plus rempli en dechargeant les contenaires qui ne partent pas pour sa direction\n");
                        //printf("1- Laisser l'IA essayer de trouver une solution\n");
                        //scanf("%d",&(optionChoosen));
                        optionChoosen = 0;
                        if (optionChoosen == 0) {


                            //############################On regarde dans las camions en attente############################
                            //On cherche le(s) transporteur(s) qui a le plus de contenaire lui appartenant

                            int tabStep1[data.nbTotalId];

                            for (int i = 0; i < data.nbTotalId; i++) {
                                tabStep1[i] = -1;
                            }

                            int best = 0;
                            int increment = 0;

                            for (int i = 0; i < data.nbTotalId; i++) {
                                int nbContenaires = 0;
                                for (int j = 0; j < getNbContenaires(identificationTab[i].type); j++) {
                                    if (identificationTab[i].listeContenaires[j].idDestination ==
                                        identificationTab[i].idDestination) {
                                        nbContenaires++;
                                    }
                                }
                                if (nbContenaires > best) {
                                    for (int i = 0; i < data.nbTotalId; i++) {
                                        tabStep1[i] = -1;
                                    }
                                    tabStep1[0] = i;
                                    best = nbContenaires;
                                    increment = 1;
                                } else if (nbContenaires == best) {
                                    tabStep1[increment] = i;
                                    increment++;
                                }
                            }

                            //printf("fin step 1 %d\n", tabStep1[0]);

                            int bestTrans = tabStep1[0];

                            if (increment > 1) {

                                //On choisi le transporteur qui a le plus grand ratio nbContMax/nbEmplacementsVides
                                int i = 0;
                                int best = 0;

                                while (tabStep1[i] != -1 && i < data.nbTotalId) {
                                    int nbVides;
                                    for (int j = 0; j < getNbContenaires(identificationTab[tabStep1[i]].type); j++) {
                                        if (identificationTab[tabStep1[i]].listeContenaires[j].idDestination == -1) {
                                            nbVides++;
                                        }
                                    }
                                    if ((nbVides / getNbContenaires(identificationTab[tabStep1[i]].type)) > best) {
                                        bestTrans = i;
                                    }
                                    i++;
                                }
                            } else {
                                //on choisi le prmeier transporteur de la liste
                                bestTrans = tabStep1[0];
                            }

                            //printf("fin stap 2  %d\n", bestTrans);

                            //On lance deux processus(pour les deux portiques) qui vont permettrent de vider le transporteur des contenaires qui ne vont pas a sa destination vers l'espace de stockage
                            if (!fork()) {
                                //portique 1
                                InfoToMove move;
                                move.idTransporteurDestinataire = data.nbTotalId;
                                move.idCallerTransporteur = bestTrans;


                                for (int cont = 0; cont < getNbContenaires(identificationTab[bestTrans].type); cont++) {

                                    if (identificationTab[bestTrans].listeContenaires[cont].idDestination != -1 &&
                                        identificationTab[bestTrans].listeContenaires[cont].idDestination !=
                                        identificationTab[bestTrans].idDestination) {

                                        Pportique(6);
                                        //printf("p1\n");
                                        move.idContenaireToMove = cont;
                                        move.idEmplacementDestinataire = emptyStockSpace();
                                        portiqueTab[0].infoToMoveContenaire = move;
                                        //printf("p1 semStart : %d\n", portiqueTab[0].semToStart);
                                        Vportique(portiqueTab[0].semToStart);

                                    }
                                }

                                exit(0);
                            }

                            if (!fork()) {
                                //portique 2
                                InfoToMove move;
                                move.idTransporteurDestinataire = data.nbTotalId;
                                move.idCallerTransporteur = bestTrans;


                                for (int cont = 0; cont < getNbContenaires(identificationTab[bestTrans].type); cont++) {

                                    if (identificationTab[bestTrans].listeContenaires[cont].idDestination != -1 &&
                                        identificationTab[bestTrans].listeContenaires[cont].idDestination !=
                                        identificationTab[bestTrans].idDestination) {

                                        Pportique(7);
                                        //printf("p2\n");

                                        /*int contenaireStockSpace=0;

                                        while(contenaireStockSpace<20 && identificationTab[data.nbTotalId].listeContenaires[contenaireStockSpace]!=-1){
                                            contenaireStockSpace++;
                                        }*/
                                        move.idContenaireToMove = cont;
                                        move.idEmplacementDestinataire = emptyStockSpace();
                                        portiqueTab[1].infoToMoveContenaire = move;
                                        //printf("p2 semStart : %d\n", portiqueTab[1].semToStart);
                                        Vportique(portiqueTab[1].semToStart);
                                    }
                                }

                                exit(0);
                            }

                            for (int stop = 0; stop < 2; stop++) {
                                wait(0);
                            }

                            //printf("godLikeClose\n");
                            //printf("trans qui part: %d\n", bestTrans);
                            fairePartirTransporteur(bestTrans);
                            Pportique(5);
                            for (int i = 0; i < sharedData->nbProcessBloque; i++) {
                                Vportique(4);
                            }
                            sharedData->nbProcessBloque = 0;
                            Vportique(5);
                        }

                    } else {
                        displayInfo("On ne peut pas faire mieux");
                    }
                }
            }
            else{
                Vportique(5);
            }

        }
    }
}

/* creation du processus Peniche */
void peniche(int newId, int semWaitResumeTest){

    if (!fork()) {

        initNouveauTransport(newId, PENICHE, semWaitResumeTest);

        for(int i=0; i<1; i++) wait(0); //on attend que les processus fils soient finis
        exit(0);
    }
}

/* creation du processus Train */
void train(int newId, int semWaitResumeTest){

    if (!fork()) {

        //connection au segment partagé du tableau de pointeurs de transporteurs

//###################################initialisation du transporteur###########################################################################################
        initNouveauTransport(newId, TRAIN, semWaitResumeTest);

//#############################################################################################################################################################


        for(int i=0; i<2; i++) wait(0);

        exit(0);
    }
}

/* creation du processus Train */
void camion(int newId, int semWaitResumeTest){

    if (!fork()) {

        //connection au segment partagé du tableau de pointeurs de transporteurs

//###################################initialisation du transporteur###########################################################################################

        initNouveauTransport(newId, CAMION, semWaitResumeTest);

//#############################################################################################################################################################

        for(int i=0; i<2; i++) wait(0);


        exit(0);
    }
}

int main(int argc, char *argv[])
{
    system("ipcrm -a");
    data.memSharedData = shmget(123456, sizeof(SharedData*), 0700 | IPC_CREAT);
    sharedData= (SharedData *) shmat(data.memSharedData, NULL,0);

    char affichage='n';
    char answere='n';


    printf("Voulez-vous lancer le jeu de test? (y/n) \n");
    scanf("%c",&answere);
    printf("\n");

    if(answere=='n'){
        sharedData->mod=0;
        printf("nombre maximal de peniches: \n");
        scanf("%d",&(data.maxPen));
        printf("\n");
        printf("nombre maximal de trains: \n");
        scanf("%d",&(data.maxTrain));
        printf("\n");
        printf("nombre maximal de camions: \n");
        scanf("%d",&(data.maxCam));
        printf("\n");
        printf("nombre de contenaires par peniche: \n");
        while(data.nbContPen<=0 || data.nbContPen>NBSTOCK){
            printf("Le nombre de conteniares doit etre compris entre 0 et %d\n",NBSTOCK);
            scanf("%d",&(data.nbContPen));
            printf("\n");
        }

        printf("nombre de contenaires par train: \n");
        while(data.nbContTrain<=0 || data.nbContTrain>NBSTOCK){
            printf("Le nombre de conteniares doit etre compris entre 0 et %d\n",NBSTOCK);
            scanf("%d",&(data.nbContTrain));
            printf("\n");
        }
        printf("nombre de contenaires par camion: \n");
        while(data.nbContCamion<=0 || data.nbContCamion>NBSTOCK){
            printf("Le nombre de conteniares doit etre compris entre 0 et %d\n",NBSTOCK);
            scanf("%d",&(data.nbContCamion));
            printf("\n");
        }
        printf("nombre de destinations possibles: \n");
        scanf("%d",&(data.nbDestinations));
        printf("\n");
    }
    else {
        sharedData->mod = 1;
        readFile();
    }
    printf("Voulez vous activer l'affichage avancé?(y/n) \n");
    scanf("%s",&(affichage));
    printf("\n");


    data.nbTotalId=data.maxCam+data.maxPen+data.maxTrain;

//##########################################Semaphores#########################################################




    data.nbTotalSem=11; //Le nombre total de semaphore correspond au nombre de portique x2 + 2

    if((data.sem_id = semget(123, data.nbTotalSem, IFLAGS)) > 0){
        ushort array[data.nbTotalSem];
        for(int i=0; i<data.nbTotalSem;i++){
            array[i]=0;
        }
        ctl_arg.array = array;
        semctl(data.sem_id, 0, SETALL, ctl_arg);
    }


//###################################################################################################################

    data.nbMaxCont=NBSTOCK;
    int nbMutex=data.nbMaxCont*(data.nbTotalId+1);


//################################memoire Partagée###################################################################

    /* création ou lien avec une identificationTab partagée */
    data.memid = shmget(1234, (data.nbTotalId+1)*sizeof(Transporteur*), 0700 | IPC_CREAT);
    data.memPortique = shmget(12345, 2*sizeof(Portique*), 0700 | IPC_CREAT);
    data.memCamionWaiting = shmget(21, data.maxCam*sizeof(Transporteur*), 0700 | IPC_CREAT);



    if((data.semContenaire_id = semget(1234567, nbMutex, IFLAGS)) > 0){
        ushort array[nbMutex];
        for(int i=0; i<nbMutex;i++){
            array[i]=1;
        }
        ctl_arg.array = array;
        semctl(data.semContenaire_id, 0, SETALL, ctl_arg);
    }

    if((data.semDisplayer_id = semget(12345678, 1, IFLAGS)) > 0){
        ushort array[1];
        for(int i=0; i<1;i++){
            array[i]=0;
        }
        ctl_arg.array = array;
        semctl(data.semDisplayer_id, 0, SETALL, ctl_arg);
    }

    if (data.memid == -1) {
        perror("shmget");
    }

    if (data.memPortique == -1) {
        perror("shmget");
    }

    if (data.memSharedData == -1) {
        perror("shmget");
    }
    /* montage en mémoire */
    identificationTab = (Transporteur *) shmat(data.memid, NULL, 0);
    portiqueTab= (Portique *) shmat(data.memPortique, NULL,0);
    camionWaiting=(Transporteur *) shmat(data.memCamionWaiting, NULL, 0);

    sharedData->nbProcessBloque=0;

//########################################################################################################################

//##############################################Initialisation du programme##############################################
    portiqueTab[0].idPortique=0;
    portiqueTab[0].semToCall=0;
    portiqueTab[0].semToStart=1;
    portiqueTab[0].semMove=9;

    portiqueTab[1].idPortique=1;
    portiqueTab[1].semToCall=2;
    portiqueTab[1].semToStart=3;
    portiqueTab[1].semMove=10;

    if((data.semPosy_id = semget(123456789, 3, IFLAGS)) > 0){
        ushort array[2];
        for(int i=0; i<3;i++){
            array[i]=1;
        }
        ctl_arg.array = array;
        semctl(data.semPosy_id, 0, SETALL, ctl_arg);
    }





    int id=0;
    //Initialisation des transporteurs
    for(int i=0; i<data.maxPen;i++){
        peniche(id, 4);
        id++;
    }
    for(int i=0; i<data.maxCam;i++){
        camion(id, 4);
        id++;
    }
    for(int i=0; i<data.maxTrain;i++){
        train(id, 4);
        id++;
    }
    for(int i=0; i<data.maxCam;i++){
        if(sharedData->mod==0){
            camionWaiting[i].idDestination=getIdDestination();
            camionWaiting[i].listeContenaires[0].idDestination=getIdDestination();
        }
        else{
            camionWaiting[i].idDestination=readGetWaitingIdDestination(i,sharedData->file);
            camionWaiting[i].listeContenaires[0].idDestination=readGetContenaireWaitingDestination(i,0,sharedData->file);
        }
        camionWaiting[i].listeContenaires[0].y=(i*2)+1;
        camionWaiting[i].listeContenaires[0].x=10;
        camionWaiting[i].idTransporteur=i;
        camionWaiting[i].type=CAMION;
    }



//######################################En mode jeux de test############################################################
    /*if(sharedData->mod==1){

        for(int i=0; i<data.nbTotalId; i++){
            //identificationTab[i].idDestination=readGetIdDestination(i,sharedData->file);

            printf("rzq %d", i);
            for(int j=0; j<getNbContenaires(identificationTab[i].type); j++){

                //identificationTab[i].listeContenaires[j].idDestination=readGetContenaireDestination(i,j,sharedData->file);
                printf("idT: %d  idC: %d   nbC:%d\n",i,j,getNbContenaires(identificationTab[i].type));
                printf("idT: %d  idC: %d   nbC:%d\n",i,j,getNbContenaires(identificationTab[i].type));
            }
        }
    }*/

    //#############################################################################################################################


    identificationTab[data.nbTotalId].idDestination=-1;
    identificationTab[data.nbTotalId].type=STOCK;
    identificationTab[data.nbTotalId].idTransporteur=data.nbTotalId;
    for(int i=0; i<NBSTOCK;i++){
        identificationTab[data.nbTotalId].listeContenaires[i].idDestination=-1;
    }

    initStockSpace();

    godLike();

    if(affichage=='y'){
        sharedData->vitessePortique=1000000;
    }
    else{
        sharedData->vitessePortique=100000;
    }

    if(affichage=='y') displayer();
    else displayer2();

    Vdisplayer(0);


    portique(1, 0, 0, 4);
    portique(3, 2, 1, 4);



    initPosPortique(0);
    initPosPortique(1);



    Vportique(0);
    Vportique(2);
    Vportique(5);

    for (int i=1; i<=data.nbTotalId; i++) wait(0);

    shmctl(data.memid,IPC_RMID,0);
    semctl(data.sem_id,0,IPC_RMID,0);
    return(0);
}
