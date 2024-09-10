/* 
 * File:   segmem.h
 * Author: whitewizard
 *
 * Created on 17 novembre 2010, 7.42
 * libreria per la manipolazione di segmenti di memoria. L'allocazione della
 * memoria viene gestita secondo due modelli : tramite SYSV e allocazione
 * dinamica tramite malloc
 */

#ifndef _SEGMEM_H
#define	_SEGMEM_H

#include "myipc.h"

typedef enum{SHDBFF,    //segmento di memoria tramite allocazione dinamica
        SYSVBFF         //segmento di memoria tramite primitive SYSV
}SEGMDL;                //modello del segmento

typedef union{
    void* bff;          //buffer per l'allocazione dinamica
    SHM_P shm;          //memoria condivisa per le SYSV
}MEMDVC;                //dispositivo che implementa la memoria

typedef struct{
    MEMDVC mdvc;        //dispositivo di memoria
    SEGMDL model;       //modello del segmento di memoria
    int size;           //dimensione unitaria del segmento
    int block;          //numero  di blocchi del segmento
}MEMSEG;                //segmento di memoria
typedef MEMSEG* MEMSEG_P;

MEMSEG_P newMemSeg(SEGMDL mdl,int size,int block);
void freeMemSeg(MEMSEG_P seg);

#endif	/* _SEGMEM_H */
