/* 
 * File:   task.h
 * Author: whitewizard
 *
 * Created on 6 novembre 2010, 19.55
 */

#ifndef _TASK_H
#define	_TASK_H

#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#include "chnls.h"

//#define VFORK_MODE
#define FORK_FAILED -1
#define CHILD 0
#define MAX_TASK_GRP 10

typedef enum{PROCESS,THREAD}TASK_TYPE;
typedef enum{PROCESS_MODE, THREAD_MODE}TASK_MODE;

#define DEF_TASK_MODE
#ifdef DEF_TASK_MODE
#define TASK_MODE PROCESS_MODE
#else
#define TASK_MODE THREAD_MODE
#endif

typedef union{
    pid_t pid;
    pthread_t tid;
}TASK_ID;

typedef struct{
    CHL_P in;
    CHL_P out;
    void *args;
}TSKPRM;
typedef TSKPRM* TSKPRM_P;

typedef struct{
    TASK_ID id;
    TASK_TYPE type;
    void *args;
    void *(*hndl)(void *args);
}TASK;
typedef TASK* TASK_P;

typedef struct{
    int gCount;
    TASK_TYPE gType;
    void **args;
    void *(*hndl)(void *args);
    TASK_P tasks[MAX_TASK_GRP];
}TASKGRP;
typedef TASKGRP* TASKGRP_P;

TSKPRM_P newTskPrm(CHL_P in,CHL_P out,void *args);
long int getIdOf(TASK_P tsk);
TASK_P newTask(TASK_TYPE type,void *args,void *(*hndl)(void *args));
TASKGRP_P newTskGrp(int gCnt,TASK_TYPE type,void **args,void*(*hndl)(void*args));

void tskBuilder(TASK_P tsk);
void tskGrpBuilder(TASKGRP_P tGrp);
void srandTask(char *rnddvc);
void prcBuilder(TASK_P tsk);
void thdBuilder(TASK_P tsk);
long int getIdOf(TASK_P tsk);
long int getTskId(void);
void killTask(TASK_P tsk,int sig);
void waitTask(TASK_P tsk);
void waitTskGrp(TASKGRP_P tGrp);

#endif	/* _TASK_H */

