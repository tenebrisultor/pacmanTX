/*myipc.c*/
#include "myipc.h"
#include "common.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>

struct sembuf sem_lock = {0,-1,SEM_UNDO};   //struttura per il lock dei semafori
struct sembuf sem_ulock = {0,1,SEM_UNDO};   //struttura per l'unlock dei semafori


int newSem(int nsems,int val){
    SEMUN sunion;       //la struttura per la manipolazione del semaforo
    int id;             //l'id del semaforo

    if((id=semget(IPC_PRIVATE,nsems,IPC_CREAT|0666))==-1)  //creo i semafori
        return id;

    sunion.val = val;                   //inizializzo il semaforo
    if(semctl(id,0,SETVAL,sunion)==-1)  //errori durante l'inizializzazione?
            return -1;                  //restituisce valore sentinella
    return id;                          //restituisco l'id del semaforo
}

int semFind(key_t key){return semget(key,1,0);}
int semRead(SEMID id){ return semctl(id,0,GETVAL);}
int semLock(SEMID id){return semop(id,&sem_lock,1);}
int semULock(SEMID id){return semop(id,&sem_ulock,1);}
int semRemove(SEMID id){return semctl(id,0,IPC_RMID);}

SEMSYSV_P newSemSysV(int value){
    SEMSYSV_P sem = NULL;

    if(!ALLOC(sem,SEMSYSV_P,SEMSYSV))   //alloco la memoria per la struttura
        exit(EXIT_FAILURE);             //altrimenti termino
    sem->id = newSem(1,value);          //creao il semaforo

    return sem;                         //restituisce il semaforo
}

SEMSYSV_P newMtxSysV(){return newSemSysV(1);}

int lockSysV(SEMSYSV_P sem){return semLock(sem->id);}
int unLockSysV(SEMSYSV_P sem){return semULock(sem->id);}

SHM_P newShm(int size,int block,SHM_FLAGS flg){
    SHM_P shm = NULL;

    if(!ALLOC(shm,SHM_P,SHM))   //alloco lo spazio in memoria per SHM
        exit(EXIT_FAILURE);     //se errori termino
    //shm->key = IPC_PRIVATE;
    shm->size = size;           //inizializzo dimension
    shm->block = block;         //inizializzo blocchi
    shm->flg = flg;             //inizializzo flag

    //alloco la memoria condivisa di dimensione size*block
    if((shm->id=shmget(IPC_PRIVATE,shm->size*shm->block,IPC_CREAT | shm->flg))<0)
        return shm;

    //attacco il riferimento di memoria alla memoria appena creata
    if((shm->shm=(void*)shmat(shm->id,NULL,0))<0)        
        return shm;    

    return shm;
}

void clearShm(SHM_P shm){

    shmdt(shm->shm);
    shmctl(shm->id,IPC_RMID,NULL);
    free(shm);
}
