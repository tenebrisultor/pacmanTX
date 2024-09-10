/*ghost.h*/
#include "ghost.h"
#include "common.h"

#include <stdlib.h>

GHOST_P newGhost(int x,int y,char icon,int color){
    GHOST_P ght = NULL;

    if(!ALLOC(ght,GHOST_P,GHOST))
        exit(EXIT_FAILURE);

    //ght->obj = newGameObj(x,y,icon,color);
    setGameObj(x,y,icon,color,&ght->obj);

    return ght;
}

void *ghost(void *args){

    RMTOBJ_P rObj = (RMTOBJ_P)args;
    GHOST_P ght = (GHOST_P)rObj->obj;
    RRCHL_P rr = rObj->rr;

    int action;

    ght->obj.dir = rand()%4;   //determina una nuova direzione casuale
    while(1){
        //se a destra o a sinistra c'è un incrocio
        if(!IS_WALL(lookLeft(&ght->obj)) || !IS_WALL(lookRight(&ght->obj)))
            newDir(&ght->obj);   //determina una nuova direzione

        moveObj(&ght->obj);      //si muove nella direzione scelta
        eat(&ght->obj,gf);       //mangia ciò che si trova nella nuova direzione

        send(rr->reqChl,&ght->obj);  //invia le suee coordinate
        //receive(rr->repChl,dummy->obj);
        usleep(ONE_SEC/4);
    }
    
}
