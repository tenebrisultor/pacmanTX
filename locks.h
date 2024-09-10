/* 
 * File:   locks.h
 * Author: whitewizard
 *
 * Created on 3 settembre 2010, 11.52
 * astrazione del concetto di lucchetto. Implementazione generalizzata che fa
 * uso di pthread_mutex sysv_mutex sysv_sem
 */

#ifndef _LOCKS_H
#define	_LOCKS_H

#include <pthread.h>

#include "myipc.h"

typedef enum {PMTX,SYSVMTX,SYSVSEM}LOCK_TYPE;   //nuovo tipo : lucchetto

typedef union{
    pthread_mutex_t pmtx;       //mutex di tipo pthread
    SEMSYSV_P sem;              //semaforo sysv
}LOCKDVC;                       //dispositivo di lock
typedef LOCKDVC* LOCKDVC_P;     //puntatore a dispositivo di lock

typedef struct{
    LOCK_TYPE type;             //tipo del lucchetto implementato dal dispositivo
    LOCKDVC_P dvc;              //dispositivo che implementa il lucchetto
}LOCK;                          //tipo di dato : lucchetto
typedef LOCK* LOCK_P;

typedef struct{
    LOCK_P mtx;                 //mutex per la mutua esclusione
    LOCK_P empty;               //semaforo per le posizioni libere
    LOCK_P full;                //lock per le posizioni occupate
}RLOCK;                         //lock per risorse aggregate
typedef RLOCK* RLOCK_P;         //puntatore al lock di risorse

LOCKDVC_P newLockDvc(LOCK_TYPE type,int val);
LOCK_P newLock(LOCK_TYPE type,int val);
void lock(LOCK_P lock);
void unlock(LOCK_P lock);
void freeLock(LOCK_P lock);
RLOCK_P newRLock(int n);
void lockEmptyRes(RLOCK_P rLock);
void lockFullRes(RLOCK_P rLock);
void unLockEmptyRes(RLOCK_P rLock);
void unLockFullRes(RLOCK_P rLock);
void freeRsrcLock(RLOCK_P r);

#endif	/* _LOCKS_H */

