/* 
 * File:   pacman.h
 * Author: whitewizard
 *
 * Created on 16 dicembre 2010, 9.36
 */

#ifndef _PACMAN_H
#define	_PACMAN_H

#include "gameobj.h"

#define DEF_PAC_X 20
#define DEF_PAC_Y 22
#define PAC_COLOR 1

typedef struct{
    int lives;
    int shots;
    int shotted;
}PACPARAM;
typedef PACPARAM* PACPARAM_P;

typedef struct{
    GAMEOBJ obj;    
}PACMAN;
typedef PACMAN* PACMAN_P;

extern GAMEFIELD_P gf;

void *setPParam(int l,int s,PACPARAM_P p);
PACMAN_P newPacman(int x,int y,char icon,int color,int l,int s);
void *pacman(void *args);
void *pacman2(void *args);
void switchKey(PACMAN_P pac,int key);
void *keyHndl(void *args);
int getNextKey(void);


#endif	/* _PACMAN_H */

