/*shdadt.c*/
#include "shdadt.h"
#include "common.h"
#include "myipc.h"

#include <stdlib.h>

SHD_CBFF_P newShdCbff(SEGMDL mdl,int size,int block){
    SHD_CBFF_P sCbff = NULL;

    if(!ALLOC(sCbff,SHD_CBFF_P,SHD_CBFF))    //errore durante l'allocazione?
        exit(EXIT_FAILURE);                     //termino

    sCbff->bff = newMemSeg(mdl,size,block);     //alloco il segmento di memoria
    sCbff->first = sCbff->last = 0;
    sCbff->mtx = newLock(SYSVMTX,1);            //inizializzo il mutex
    sCbff->empty = newLock(SYSVSEM,block);      //inizializzo il semaforo
    sCbff->full = newLock(SYSVSEM,0);           //inizializzo il semaforo

    return sCbff;                               //restituisco il buffer circolare
}

void wtSCbff(void *obj,SHD_CBFF_P sCbff){

    typedef struct{                         //supporto per la scrittura dati void
        char tmp[sCbff->bff->size * sCbff->bff->block];
    }TMP;
    TMP* tmp = (TMP*)obj;                   //riferimento all'oggetto da scrivere
    TMP* bff;                               //riferimento al buffer

    switch(sCbff->bff->model){
        case SHDBFF:
            bff = (TMP*)sCbff->bff->mdvc.bff;
            break;
        case SYSVBFF:
            bff = (TMP*)sCbff->bff->mdvc.shm->shm;
            break;
        default:
            break;
    }

    lock(sCbff->empty);                      //lock posizioni libere
    lock(sCbff->mtx);                        //mutua esclusione
    bff[sCbff->last] = *tmp;                 //copio l'oggetto nel buffer
    sCbff->last =                            //aggiorno il puntatore logico
        (sCbff->last+sCbff->bff->size)%
        (sCbff->bff->size*sCbff->bff->block);
    unlock(sCbff->mtx);                      //escludo la mutua esclusione
    unlock(sCbff->full);                     //sblocco le posizioni piene
}

void rdSCbff(void *obj,SHD_CBFF_P sCbff){

    typedef struct{                         //supporto lettura dati void
        char tmp[sCbff->bff->size*sCbff->bff->block];
    }TMP;    
    TMP* tmp = (TMP*)obj;                   //riferimento all'oggetto
    TMP* bff;                               //riferimento al buffer

    switch(sCbff->bff->model){
        case SHDBFF:
            bff = (TMP*)sCbff->bff->mdvc.bff;
            break;
        case SYSVBFF:
            bff = (TMP*)sCbff->bff->mdvc.shm->shm;
            break;
        default:
            break;
    }

    lock(sCbff->full);                       //lock posizioni piene
    lock(sCbff->mtx);                        //mutua esclusione
    *tmp=bff[sCbff->first];                  //leggo l'oggetto
    sCbff->first =                           //aggiorno il puntatore logico
        (sCbff->first+sCbff->bff->size)%
        (sCbff->bff->size*sCbff->bff->block);
    unlock(sCbff->mtx);                      //escludo la mutua esclusione
    unlock(sCbff->empty);                    //sblocco le posizioni piene
}

void freeCbff(SHD_CBFF_P  cbff){
}