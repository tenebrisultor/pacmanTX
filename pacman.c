/*
 * pacman.c
 */
#include "pacman.h"
#include "common.h"
#include "clisrv.h"
#include "task.h"
#include "ghost.h"

#include <stdlib.h>
#include <curses.h>

void *setPParam(int l,int s,PACPARAM_P p){
    p->lives = l;
    p->shots = s;
}

PACMAN_P newPacman(int x,int y,char icon,int color,int l,int s){
    PACMAN_P pac = NULL;

    if(!ALLOC(pac,PACMAN_P,PACMAN))
        exit(EXIT_FAILURE);

    //pac->obj = newGameObj(x,y,icon,color);
    setGameObj(x,y,icon,color,&pac->obj);
    //setPParam(l,s,&pac->prm);

    return pac;
}

void *pacman(void *args){

    int key,old;
    RMTOBJ_P rObj = (RMTOBJ_P)args;
    PACMAN_P pac = (PACMAN_P)rObj->obj;
    RRCHL_P rr = rObj->rr;    
    key = old = KEY_LEFT;
    while(1){
        key = getch();
        if(key==ERR) key = old;
        else if(key!=SPACEBAR)
                old = key;
        switchKey(pac,key);

        if(!IS_WALL(lookAhead(&pac->obj)))
            moveObj(&pac->obj);
        
        send(rr->reqChl,&pac->obj);
        usleep(ONE_SEC/4);
    }
}

void *pacman2(void *args){
    RMTOBJ_P rObj = (RMTOBJ_P)args;
    PACMAN_P pac = (PACMAN_P)rObj->obj;
    RRCHL_P rr = rObj->rr;
    int key,old;

    CHL_P keyChl = newChl(CHL_MODE,sizeof(int),10);
    TASK_P keyTsk = newTask(TASK_MODE,keyChl,keyHndl);

    tskBuilder(keyTsk);

    key = old = KEY_LEFT;
    while(1){
        receive(keyChl,&key);
        switchKey(pac,key);

        if(!IS_WALL(lookAhead(&pac->obj)))
            moveObj(&pac->obj);
        
        usleep(ONE_SEC/2);
    }
}

void switchKey(PACMAN_P pac,int key){
    switch(key){
            case KEY_UP:
                SET_DIR(pac->obj,NORD);
                break;
            case KEY_DOWN:
                SET_DIR(pac->obj,SUD);
                break;
            case KEY_LEFT:
                SET_DIR(pac->obj,OVEST);
                break;
            case KEY_RIGHT:
                SET_DIR(pac->obj,EST);
                break;
            case SPACEBAR :
                //pac->prm.shotted = 1;
                break;
            default:
                break;
        }
}

void *keyHndl(void *args){
    int key = KEY_LEFT;
    int old = key;
    CHL_P chl = (CHL_P)args;

    while(1){
        while((key=getch())!=ERR){
            old = key;
            send(chl,&key);
        }
        key = old;
        send(chl,&key);
        usleep(ONE_SEC/2);
    }
}

int getNextKey(void){
    int key = KEY_LEFT;
    int old = key;

    key = getch();
    if(key==ERR)
        key = old;
    else
        old = key;

    return key;
}