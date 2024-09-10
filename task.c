/*taskc.c*/
#include "task.h"

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

TSKPRM_P newTskPrm(CHL_P in,CHL_P out,void *args){
    TSKPRM_P tskPrm = NULL;

    if(!ALLOC(tskPrm,TSKPRM_P,TSKPRM))
        exit(EXIT_FAILURE);

    tskPrm->in = in;
    tskPrm->out = out;
    tskPrm->args = args;

    return tskPrm;
}

TASK_P newTask(TASK_TYPE type,void *args,void *(*hndl)(void *args)){
    TASK_P tsk = NULL;

    if(!ALLOC(tsk,TASK_P,TASK))
        exit(EXIT_FAILURE);
    tsk->type = type;
    tsk->args = args;
    tsk->hndl = hndl;

    return tsk;
}

TASKGRP_P newTskGrp(int gCnt,TASK_TYPE type,void **args,void*(*hndl)(void*args)){
    TASKGRP_P tGrp = NULL;
    int i;

    if(!ALLOC(tGrp,TASKGRP_P,TASKGRP))
        exit(EXIT_FAILURE);

    tGrp->gCount = gCnt;
    tGrp->gType = type;
    tGrp->args = args;
    tGrp->hndl = hndl;

    for(i=0;i<gCnt;i++)
        tGrp->tasks[i] = newTask(type,args[i],hndl);

    return tGrp;
}

void tskBuilder(TASK_P tsk){

    switch(tsk->type){
        case PROCESS:           
            prcBuilder(tsk);
            break;
        case THREAD:            
            thdBuilder(tsk);
            break;
        default:
            break;
    }
}

void tskGrpBuilder(TASKGRP_P tGrp){
    int i;

    for(i=0;i<tGrp->gCount;i++)
        tskBuilder(tGrp->tasks[i]);
}

void srandTask(char *rnddvc){
    int fd,seed;

    fd = open(rnddvc,O_RDONLY);
    read(fd,&seed,sizeof(int));
    close(fd);
    srand(seed);

}

void prcBuilder(TASK_P tsk){

    #ifdef VFORK_MODE
    tsk->id.pid = vfork();
    #else
    tsk->id.pid = fork();
    #endif

    switch(tsk->id.pid){
        case FORK_FAILED:            
            exit(EXIT_FAILURE);
            break;
        case CHILD:
            srandTask("/dev/urandom");
            tsk->hndl(tsk->args);            
            _exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

void thdBuilder(TASK_P tsk){
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tsk->id.tid, &attr, tsk->hndl, tsk->args);
}

long int getIdOf(TASK_P tsk){

    long int id;

    switch(tsk->type){
        case PROCESS:
            id = tsk->id.pid;
            break;
        case THREAD:
            id = tsk->id.tid;
            break;
        default:
            break;
    }

    return id;
}

long int getTskId(void){
    long int id;
    if(TASK_MODE == PROCESS_MODE)
         id = getpid();
    else
        id = pthread_self();

    return id;
}

void killTask(TASK_P tsk,int sig){

    switch(tsk->type){
        case PROCESS:
            kill(getIdOf(tsk),sig);
            break;
        case THREAD:
            pthread_kill(getIdOf(tsk),sig);
            break;
        default:
            break;
    }
}

void waitTask(TASK_P tsk){

    switch(tsk->type){
        case PROCESS:
            waitpid(getIdOf(tsk),NULL,0);
            break;
        case THREAD:
            pthread_join(getIdOf(tsk),NULL);
            break;
        default:
            break;
    }
}

void waitTskGrp(TASKGRP_P tGrp){
    int i;

    for(i=0;i<tGrp->gCount;i++)
        waitTask(tGrp->tasks[i]);
}