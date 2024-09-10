/*
 * shdmry.c
 * gestione della memoria consivisa secondo due modelli SYSV e buffer condiviso
 */
#include "shdmry.h"
#include "common.h"
#include "myipc.h"

#include <stdlib.h>

MSGM_P newMemSgm(MEMMDL mdl,int size,int block){
    MSGM_P sgm = NULL;

    if(!ALLOC(sgm,MSGM_P,sizeof(MSGM_P)))
        exit(EXIT_FAILURE);
    sgm->size = size;
    sgm->block = block;

    switch(mdl){
        case MALLOC_MODEL:
            if(!NALLOC(sgm->bff,MSGM_P,size,block))
                exit(EXIT_FAILURE);
            break;
        case SYSV_MODEL:
            if(!(sgm->bff=newShm(size,block,0666)))
                exit(EXIT_FAILURE);
            break;
        default:
            break;
    }

    return sgm;
}

void freeMSgm(MSGM_P sgm){}
