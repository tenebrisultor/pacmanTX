/* 
 * File:   worm.h
 * Author: whitewizard
 *
 * Created on 16 dicembre 2010, 17.51
 */

#ifndef _WORM_H
#define	_WORM_H

#include "gameobj.h"

typedef struct{
    GAMEOBJ obj;
}WORM;
typedef WORM* WORM_P;

//extern GAMEFIELD_P gf;

WORM_P newWorm(int x,int y,char icon,int color);
void *worm(void *args);

#endif	/* _WORM_H */

