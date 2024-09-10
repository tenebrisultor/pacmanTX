/*chnls.c*/
#include "chnls.h"

#include "common.h"
#include "clisrv.h"

#include <stdlib.h>

PIPE_P newPipe(){
    PIPE_P pp = NULL;

    if(!ALLOC(pp,PIPE_P,PIPE))
        exit(EXIT_FAILURE);

    if(pipe(pp->fd)==PIPE_FAILED)
        exit(EXIT_FAILURE);

    return pp;
}

CHLDVC_P newChlDvc(CHL_TYPE type,int size,int block){
    CHLDVC_P dvc = NULL;

    if(!ALLOC(dvc,CHLDVC_P,CHLDVC))
        exit(EXIT_FAILURE);

    switch(type){
        case PIPE_CHL:
            dvc->pipe = newPipe();
            break;
        case SHM_CHL:
            dvc->cbff = newShdCbff(SHDBFF,size,block);
            break;
        case SYSV_SHM_CHL:
            dvc->cbff = newShdCbff(SYSVBFF,size,block);
            break;
        default:
            break;
    }

    return dvc;
}

CHL_P newChl(CHL_TYPE type, int size,int block){
    CHL_P chl = NULL;

    if(!ALLOC(chl,CHL_P,CHL))
        exit(EXIT_FAILURE);

    chl->type = type;
    chl->size = size;
    chl->block = block;
    chl->dvc = newChlDvc(type,size,block);

    return chl;
}

CHL_INFO_P newChlInfo(CHL_TYPE type,int size,int block){
    CHL_INFO_P inf = NULL;

    if(!ALLOC(inf,CHL_INFO_P,CHL_INFO))
        exit(EXIT_FAILURE);
    inf->type = type;
    inf->size = size;
    inf->block = block;

    return inf;
}

CHL_P newChlByInfo(CHL_INFO_P inf){return newChl(inf->type,inf->size,inf->block);}

void setDplxChl(CHL_P in,CHL_P out,DPLX_CHL_P dplx){
    dplx->in = in;
    dplx->out = out;
}
void send(CHL_P chl,void *obj){

    switch(chl->type){
        case PIPE_CHL:
            PIPE_SEND(chl->dvc->pipe->fd,obj,chl->size);
            break;
        case SHM_CHL:
        case SYSV_SHM_CHL:
            wtSCbff(obj,chl->dvc->cbff);
            break;
        default:
            break;
    }
}
void receive(CHL_P chl,void *obj){

    switch(chl->type){
        case PIPE_CHL:
            PIPE_RECEIVE(chl->dvc->pipe->fd,obj,chl->size);
            break;
        case SHM_CHL:
        case SYSV_SHM_CHL:
            rdSCbff(obj,chl->dvc->cbff);
            break;
        default:
            break;
    }
}

void freePipe(PIPE_P p){
    close(p->fd[READ_END]);
    close(p->fd[WRITE_END]);
    free(p);
}
