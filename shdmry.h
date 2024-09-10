/* 
 * File:   shdmry.h
 * Author: whitewizard
 *
 * Created on 16 novembre 2010, 19.59
 * gestione della memoria consivisa secondo due modelli SYSV e buffer condiviso
 */

#ifndef _SHDMRY_H
#define	_SHDMRY_H

#include "locks.h"

typedef enum{MALLOC_MODEL,SYSV_MODEL}MEMMDL;

typedef struct{
    void *bff;          //puntatore a alla memoria condivisa
    MEMMDL mdl;         //modello di memoria utilizzato
    int size;           //dimensione unitaria della memoria
    int block;          //numero di blocchi del segmento di memoria
}MSGM;                  //segmento di memoria
typedef MSGM* MSGM_P;   //puntatore al segmento di memoria

/*Crea un segmento di memoria utilizzando o le primitive SYSV o un buffer 
 condiviso*/
MSGM_P newMSgm(MEMMDL mdl,int size,int block);
void freeMSgm(MSGM_P sgm);


#endif	/* _SHDMRY_H */

