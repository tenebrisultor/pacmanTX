/* 
 * File:   shdadt.h
 * Author: whitewizard
 *
 * Created on 3 settembre 2010, 12.35
 * header di funzioni per la creazione e gestione di strutture astratte
 * condivise. Viene fornita un implementazione di un buffer circolare che può
 * essere condiviso tra più processi.
 */

#ifndef _SHDADT_H
#define	_SHDADT_H

#include "locks.h"
#include "adt.h"

typedef struct{
    MEMSEG_P bff;       //buffer di memoria (un buffer è un segmento di memoria)
    int first;          //putnatore logico prima posizione libera
    int last;           //puntatore lofico ultima posizione
    LOCK_P mtx;         //mutex mutua esclusione
    LOCK_P empty;       //semaforo locazioni vuote del buffer
    LOCK_P full;        //semaforo locazioni occupate del buffer
}SHD_CBFF;              //definizione di tipo buffer circolare condiviso
typedef SHD_CBFF* SHD_CBFF_P;

/*
 * newShdCbff() : allocazione e inizializzazione della memoria per una struttura
 * SHD_CBFF.
 *  - size : la dimensione unitaria di una locazione
 *  - block : il numero di locazioni del buffer circolare
 *  - flag  : per la gestione delle SYSV
 */
SHD_CBFF_P newShdCbff(SEGMDL mdl,int size,int block);

/*
 * writeCbff() : scrive un elemento nel buffer circolare
 *  - obj : l'oggetto da scrivere nel buffer
 *  - cbff : il buffer
 */
void writeCbff(void *obj,SHD_CBFF_P cbff);

/*
 * readCbff() : legge un elemento dal buffer circolare
 *  - obj : l'oggetto da leggere
 *  - cbff : il buffer circolare
 */
void readCbff(void *obj,SHD_CBFF_P cbff);

/*
 * freeCbff() : libera la memoria occupata
 */
void freeCbff(SHD_CBFF_P  cbff);

#endif	/* _SHDADT_H */

