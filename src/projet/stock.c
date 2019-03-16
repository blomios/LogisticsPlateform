#include "main.h"

int emptyStockSpace(){

    for(int contenaireStockSpace=0; contenaireStockSpace<NBSTOCK; contenaireStockSpace++){
        Pcontenaire(data.nbTotalId*data.nbMaxCont+contenaireStockSpace);
        //printf(" data : %d\n", identificationTab[data.nbTotalId].listeContenaires[contenaireStockSpace]);
        if(identificationTab[data.nbTotalId].listeContenaires[contenaireStockSpace].idDestination==-1) return contenaireStockSpace;
        else{
            Vcontenaire(data.nbTotalId*data.nbMaxCont+contenaireStockSpace);
        }
    }
    return -1;
}

void initStockSpace(){

    for(int i=0; i<NBSTOCK;i++){
        setPosContenaire(data.nbTotalId,i);
    }

    if(!fork()){

        for(;;){

            Pportique(portiqueTab[0].semToCall);

            InfoToMove move=getMove(data.nbTotalId);

            if(move.idTransporteurDestinataire!=-1 && move.idEmplacementDestinataire!=-1 && move.idContenaireToMove!=-1){
                //printf("stockSpace: %d\n", identificationTab[data.nbTotalId].listeContenaires[move.idContenaireToMove]);
                portiqueTab[0].infoToMoveContenaire=move;
                Vportique(portiqueTab[0].semToStart);
            }

            else{
                //On laisse les transporteurs accéder au portique

                Vportique(6);
            }
        }
    }

    if(!fork()){

        for(;;){
            Pportique(portiqueTab[1].semToCall);

            InfoToMove move=getMove(data.nbTotalId);

            if(move.idTransporteurDestinataire!=-1 && move.idEmplacementDestinataire!=-1 && move.idContenaireToMove!=-1){
                //printf("pas la %d    %d   %d\n",move.idTransporteurDestinataire, move.idEmplacementDestinataire, move.idContenaireToMove);
                portiqueTab[1].infoToMoveContenaire=move;
                Vportique(portiqueTab[1].semToStart);
            }

            else{
                //On laisse les transporteurs accéder au portique
                Vportique(7);
            }
        }

    }
}