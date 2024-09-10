/* 
 * File:   myipc.h
 * Author: whitewizard
 *
 * Created on 3 settembre 2010, 12.15
 * funzioni di utilità per la comunicazione interprocesso usando SYSV
 */

#ifndef _MYIPC_H
#define	_MYIPC_H

#include <sys/types.h>

typedef enum{BFF,SHD_BFF}MEM_MODEL; //modello di memoria condivisa

typedef union{          //struttura dati di supporto operazioni semaforo
    int val;            //il valore del semaforo
    struct semid_ds *bf;
    unsigned short *array;
    struct seminfo *__bff;
}SEMUN;

typedef int SEMID;      //nuovo tipo : id di semaforo
typedef struct{
    key_t key;          //la chiave d'accesso al semaforo
    SEMID id;           //l'id del semaforo
}SEMSYSV;               //nuovo tipo : semaforo SysV
typedef SEMSYSV* SEMSYSV_P;

typedef int SHMID;      //nuovo tipo : id memoria condivisa
typedef int SHM_FLAGS;  //nuovo tipo : flag memoria condivisa
typedef void* SHMB;     //nuovo tipo : buffer condiviso

typedef struct{
    key_t key;          //chiave d'accesso al segmento
    SHMID id;           //identificativo del segmento
    SHM_FLAGS flg;      //flags
    int size;           //dimensione unitaria del segmento di memoria condivisa
    int block;          //numero di blocchi del segmento di memoria condivisa
    SHMB shm;           //puntatore al segmento di memoria condivisa
}SHM;                   //nuovo tipo Shared Memory
typedef SHM* SHM_P;     //puntatore alla memoria condivisa

/*
 * newSem() : crea un semaforo
 *      key : la chiave d'acceso al semaforo
 *      nsems : il numero di semafori da creare
 *      val : il valore iniziale del semaforo
 */
int newSem(int nsems,int val);

/*
 * semFind() : trova un semaforo specificato tramite la sua chiave
 *      key : la chiave del semaforo
 */
int semFind(key_t key);

/*
 * semRead() : legge il valore del semaforo specificato dall'id
 *      id : l'id del semaforo
 */
int semRead(SEMID id);

/*
 * semLock() : esegue un lock sul semaforo
 *      id : l'id del semaforo sul quale effetturare il lock
 */
int semLock(SEMID id);

/*
 * semULock() : esegue un unlock sul semaforo
 *      id : l'id del semaforo
 */
int semULock(SEMID id);

/*
 * semRemove() : elimina dal sistema il semaforo
 *      id : l'id del semaforo
 */
int semRemove(SEMID id);

/*
 * newSemSysV() : crea un semaforo SysV
 *      key : la chiave d'accesso al semaforo
 *      value : il valore iniziale del semaforo
 */
SEMSYSV_P newSemSysV(int value);

/*
 * newMtxSysV() : crea un mutex SysV
 *      key : la chiave l'accesso al mutex
 */
SEMSYSV_P newMtxSysV();

/*
 * lockSysV() : esegue un lock sul semaforo
 *      sem : il semaforo sul quale eseguire il lock
 */
int lockSysV(SEMSYSV_P sem);

/*
 * unlockSysV() : esegue un unlock sul semaforo
 *      sem : il semaforo sul quale eseguire un unlock
 */
int unLockSysV(SEMSYSV_P sem);

/*
 * newShm() : creazione di un segmento di memoria condiviso tramite SysV
 *      key : la chiave d'accesso del segmento di memoria
 *      size : la dimensione unitaria sel segmento di memoria
 *      block : il numero di blocchi di dimensione size
 *      flg : flag per la manipolazione del segmento
 */
SHM_P newShm(int size,int block,SHM_FLAGS flg);

/*
 * clearShm() : libera la memoria occupata ed elimina ils egmento di memoria
 *              condiviso tramite SysV
 *      shm : la struttura che contiene la memoria condivisa
 */
void clearShm(SHM_P shm);

#endif	/* _MYIPC_H */

