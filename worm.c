/*
 * worm.c
 */
#include "worm.h"
#include "common.h"

#include <stdlib.h>
#include <curses.h>

WORM_P newWorm(int x,int y,char icon,int color){
    WORM_P w = NULL;

    if(!ALLOC(w,WORM_P,WORM))
        exit(EXIT_FAILURE);
    setGameObj(x,y,icon,color,&w->obj);

    return w;
}

void *worm(void *args){
    RMTOBJ_P rObj = (RMTOBJ_P)args;
    WORM_P w = (WORM_P)rObj->obj;
    RRCHL_P rr = rObj->rr;

    long int key,old;

    key = old = KEY_LEFT;

    while(1){
        key = getch();
        if(key==ERR) key = old;
        else old = key;

        switch(key){
            case KEY_UP:
                w->obj.dir = NORD;
                break;
            case KEY_DOWN:
                w->obj.dir = SUD;
                break;
            case KEY_LEFT:
                w->obj.dir = OVEST;
                break;
            case KEY_RIGHT:
                w->obj.dir = EST;
                break;
            case SPACEBAR:
                break;
        }

        if(!IS_WALL(lookAhead(&w->obj)))
            moveObj(&w->obj);
        send(rr->reqChl,&w->obj);
        usleep(ONE_SEC/2);
    }
}
