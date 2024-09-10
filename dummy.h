/* 
 * File:   dummy.h
 * Author: whitewizard
 *
 * Created on 25 novembre 2010, 15.35
 */

#ifndef _DUMMY_H
#define	_DUMMY_H

#include "gameobj.h"

typedef struct{
    GAMEOBJ_P obj;
}DUMMY;
typedef DUMMY* DUMMY_P;

DUMMY_P newDummy(int x,int y,int icon,int color);

void *dummy(void *args);
void *dummy2(void *args);

#endif	/* _DUMMY_H */

