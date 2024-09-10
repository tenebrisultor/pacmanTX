/* 
 * File:   adt.h
 * Author: whitewizard
 *
 * Created on 16 novembre 2010, 19.40
 * Abstract Data Type : definizione di strutture astratte per la manipolazione
 * dei dati
 */

#ifndef _ADT_H
#define	_ADT_H

#include "memseg.h"

typedef struct{
    MEMSEG_P bff;         //segmento di memoria che implementa il buffer
    int first;          //puntatore logico prima posizione libera del buffer
    int last;           //puntatore logico ultima posizione del buffer;
}CBFF;
typedef CBFF* CBFF_P;

CBFF_P newCBff();

#endif	/* _ADT_H */

