/* 
 * File:   ghost.h
 * Author: whitewizard
 *
 * Created on 13 dicembre 2010, 19.59
 */

#ifndef _GHOST_H
#define	_GHOST_H

#include "gameobj.h"
#include "gamefield.h"

#define GHOSTS 4
#define DEF_GHOST_X 16
#define DEF_GHOST_Y 12

//extern GAMEFIELD_P gf;

typedef struct{
    GAMEOBJ obj;
}GHOST;
typedef GHOST* GHOST_P;

typedef struct{
    COORD pos;
    RRCHL_P rr;
}GHOST_PARAM;
typedef GHOST_PARAM* GHOST_PARAM_P;

GHOST_P newGhost(int x,int y,char icon,int color);
void *ghost(void *args);



#endif	/* _GHOST_H */

