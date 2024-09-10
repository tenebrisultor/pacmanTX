/* 
 * File:   gameobj.h
 * Author: whitewizard
 *
 * Created on 20 novembre 2010, 13.21
 */

#ifndef _GAMEOBJ_H
#define	_GAMEOBJ_H

#include "graph.h"
#include "gamefield.h"
#include "clisrv.h"

#include "common.h"

#define MOVE_NORD(obj)  (obj->pxl->pos->y--)
#define MOVE_SUD(obj)   (obj->pxl->pos->y++)
#define MOVE_OVEST(obj) (obj->pxl->pos->x--)
#define MOVE_EST(obj)   (obj->pxl->pos->x++)

#define LOOK_UP(obj)    (getAt(obj->pxl->pos->x,obj->pxl->pos->y--))
#define LOOK_DOWN(obj)  (getAt(obj->pxl->pos->x,obj->pxl->pos->y++))
#define LOOK_LEFT(obj)  (getAt(obj->pxl->pos->x--,obj->pxl->pos->y))
#define LOOK_RIGHT(obj) (getAt(obj->pxl->pos->x++,obj->pxl->pos->y))

#define SAVE_CUR(obj) (setCoord(obj->cur.x,obj->cur.y,&obj->old))
#define BACK_OLD(obj) (setCoord(obj->old.x,obj->old.y,&obj->cur))
#define SET_DIR(obj,d) (obj.dir = d)

#define SPACEBAR 32

typedef enum{NORD,SUD,OVEST,EST}DIRECT;
typedef enum{UP,DOWN,LEFT,RIGHT}KEYS;
typedef enum{MOVE,CHANGE_DIR}ACTION;

typedef struct{
    int objId;
    COORD cur;
    COORD old;
    char icon;
    int color;
    char eat;
    DIRECT dir;
    ACTION action;
}GAMEOBJ;
typedef GAMEOBJ* GAMEOBJ_P;

extern GAMEFIELD_P gf;
static int objCount = 0;

GAMEOBJ_P newGameObj(int x,int y,char icon,int color);
void setGameObj(int x,int y,char icon,int color,GAMEOBJ_P obj);
char lookAhead(GAMEOBJ_P obj);
char lookLeft(GAMEOBJ_P obj);
char lookRight(GAMEOBJ_P obj);
DIRECT getRevDir(DIRECT dir);
void newDir(GAMEOBJ_P obj);
void moveObj(GAMEOBJ_P obj);
int checkCollision(GAMEOBJ_P obj1,GAMEOBJ_P obj2);
void eat(GAMEOBJ_P obj,GAMEFIELD_P gf);
void wdrawObj(WINDOW *wnd,GAMEOBJ_P obj);
#endif	/* _GAMEOBJ_H */

