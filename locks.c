/*lock.c*/
#include "locks.h"
#include "common.h"

#include <stdlib.h>

LOCKDVC_P newLockDvc(LOCK_TYPE type,int val){
    LOCKDVC_P dvc = NULL;
    pthread_mutexattr_t attr;

    if(!ALLOC(dvc,LOCKDVC_P,LOCKDVC))
        exit(EXIT_FAILURE);

    switch(type){
        case PMTX:
            pthread_mutexattr_init(&attr);
            pthread_mutex_init(&dvc->pmtx,&attr);
            break;
        case SYSVMTX:
            dvc->sem = newMtxSysV();
            break;
        case SYSVSEM:
            dvc->sem = newSemSysV(val);
            break;
        default:
            break;
    }

    return dvc;
}

LOCK_P newLock(LOCK_TYPE type,int val){
    LOCK_P lock = NULL;

    if(!ALLOC(lock,LOCK_P,LOCK))
        exit(EXIT_FAILURE);
    lock->type = type;
    lock->dvc = newLockDvc(type,val);

    return lock;
}

void lock(LOCK_P lock){

    switch(lock->type){
        case PMTX:
            pthread_mutex_lock(&lock->dvc->pmtx);
            break;
        case SYSVMTX:
        case SYSVSEM:
            lockSysV(lock->dvc->sem);
            break;
        default:
            break;
    }
}

void unlock(LOCK_P lock){

    switch(lock->type){
        case PMTX:
            pthread_mutex_unlock(&lock->dvc->pmtx);
            break;
        case SYSVMTX:
        case SYSVSEM:
            unLockSysV(lock->dvc->sem);
            break;
        default:
            break;
    }
}
void freeLock(LOCK_P lock);

RLOCK_P newRLock(int n){
    RLOCK_P resLock = NULL;

    if(!ALLOC(resLock,RLOCK_P,RLOCK))
        exit(EXIT_FAILURE);

    resLock->mtx = newLock(SYSVMTX,1);
    resLock->empty = newLock(SYSVSEM,n);
    resLock->full = newLock(SYSVSEM,0);

    return resLock;
}

void lockEmptyRes(RLOCK_P rLock){
    lock(rLock->empty);
    lock(rLock->mtx);
}

void lockFullRes(RLOCK_P rLock){
    lock(rLock->full);
    lock(rLock->mtx);
}

void unLockEmptyRes(RLOCK_P rLock){
    unlock(rLock->mtx);
    unlock(rLock->empty);
}

void unLockFullRes(RLOCK_P rLock){
    unlock(rLock->mtx);
    unlock(rLock->full);

}





void freeRsrcLock(RLOCK_P rLock){

}
