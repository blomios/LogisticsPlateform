#include "main.h"

void Pportique(int semnum) {

    data.sem_oper_P.sem_num = semnum;
    data.sem_oper_P.sem_op  = -1 ;
    data.sem_oper_P.sem_flg = 0 ;
    semop(data.sem_id, &(data.sem_oper_P), 1);
}

void Vportique(int semnum) {

    data.sem_oper_V.sem_num = semnum;
    data.sem_oper_V.sem_op  = 1 ;
    data.sem_oper_V.sem_flg  = 0 ;
    semop(data.sem_id, &(data.sem_oper_V), 1);
}

void Pdisplayer(int semnum) {

    data.sem_oper_Pdisplayer.sem_num = semnum;
    data.sem_oper_Pdisplayer.sem_op  = -1 ;
    data.sem_oper_Pdisplayer.sem_flg = 0 ;
    semop(data.semDisplayer_id, &(data.sem_oper_Pdisplayer), 1);
}

void Vdisplayer(int semnum) {

    data.sem_oper_Vdisplayer.sem_num = semnum;
    data.sem_oper_Vdisplayer.sem_op  = 1 ;
    data.sem_oper_Vdisplayer.sem_flg  = 0 ;
    semop(data.semDisplayer_id, &(data.sem_oper_Vdisplayer), 1);
}

void Pcontenaire(int semnum) {

    data.sem_oper_Pcontenaire.sem_num = semnum;
    data.sem_oper_Pcontenaire.sem_op  = -1 ;
    data.sem_oper_Pcontenaire.sem_flg = 0 ;
    semop(data.semContenaire_id, &(data.sem_oper_Pcontenaire), 1);
}

void Vcontenaire(int semnum) {

    data.sem_oper_Vcontenaire.sem_num = semnum;
    data.sem_oper_Vcontenaire.sem_op  = 1 ;
    data.sem_oper_Vcontenaire.sem_flg  = 0 ;
    semop(data.semContenaire_id, &(data.sem_oper_Vcontenaire), 1);
}

void Pposy(int semnum) {

    data.sem_oper_Pposy.sem_num = semnum;
    data.sem_oper_Pposy.sem_op  = -1 ;
    data.sem_oper_Pposy.sem_flg = 0 ;
    semop(data.semPosy_id, &(data.sem_oper_Pposy), 1);
}

void Vposy(int semnum) {

    data.sem_oper_Vposy.sem_num = semnum;
    data.sem_oper_Vposy.sem_op  = 1 ;
    data.sem_oper_Vposy.sem_flg  = 0 ;
    semop(data.semPosy_id, &(data.sem_oper_Vposy), 1);
}