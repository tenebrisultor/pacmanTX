/*adt.c*/
#include "adt.h"
#include "common.h"
#include <stdlib.h>

CBFF_P newCBff(SEGMDL mdl,int size,int block){
    CBFF_P cbff = NULL;

    if(!ALLOC(cbff,CBFF_P,CBFF))
        exit(EXIT_FAILURE);
    cbff->bff = newMemSeg(mdl,size,block);
    cbff->first = cbff->last = 0;

    return cbff;
}

void wtCBff(void *obj,CBFF_P cbff){

    typedef struct{
        char tmp[cbff->bff->size * cbff->bff->block];
    }TMP;
    TMP *tmp = (TMP*)obj;
    TMP *bff;

    switch(cbff->bff->model){
        case SHDBFF:
            break;
        case SYSVBFF:
            break;
        default:
            break;
    }

    bff[cbff->last] = *tmp;                 //copio l'oggetto nel buffer
    cbff->last =                            //aggiorno il puntatore logico
            (cbff->last+cbff->bff->size)%
            (cbff->bff->size*cbff->bff->block);

    
}

void rdCBff(void *obj,CBFF_P cbff){

    typedef struct{
        char tmp[cbff->bff->size * cbff->bff->block];
    }TMP;
    TMP *tmp = (TMP*)obj;
    TMP *bff;

    switch(cbff->bff->model){
        case SHDBFF:
            break;
        case SYSVBFF:
            break;
        default:
            break;
    }

    switch(cbff->bff->model){
        case SHDBFF:
            break;
        case SYSVBFF:
            break;
        default:
            break;
    }

    *tmp=bff[cbff->first];                  //leggo l'oggetto
    cbff->first =                           //aggiorno il puntatore logico
            (cbff->first+cbff->bff->size)%
            (cbff->bff->size*cbff->bff->block);

}
