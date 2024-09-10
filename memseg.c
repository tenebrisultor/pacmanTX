/*
 * segmem.c
 * libreria per la manipolazione di segmenti di memoria. L'allocazione della
 * memoria viene gestita secondo due modelli : tramite SYSV e allocazione
 * dinamica tramite malloc
 */
#include "memseg.h"
#include "common.h"

#include <stdlib.h>

MEMSEG_P newMemSeg(SEGMDL mdl,int size,int block){
    MEMSEG_P seg = NULL;

    if(!ALLOC(seg,MEMSEG_P,MEMSEG))
        exit(EXIT_FAILURE);

    seg->model = mdl;
    seg->size = size;
    seg->block = block;

    switch(seg->model){
        case SHDBFF:
            if(!NALLOC(seg->mdvc.bff,void*,size,block))
                exit(EXIT_FAILURE);
            break;
        case SYSVBFF:
            if(!(seg->mdvc.shm=newShm(size,block,0666)))
                exit(EXIT_FAILURE);
            break;
        default:
            break;
    }

    return seg;
}

void freeMemSeg(MEMSEG_P seg){

    switch(seg->model){
        case SHDBFF:
            free(seg->mdvc.bff);
            break;
        case SYSVBFF:
            //freeShm(seg->bff);
            break;
        default:
            break;

    }
}