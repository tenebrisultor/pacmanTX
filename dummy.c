/*dummy.c*/
#include "dummy.h"
#include "common.h"
#include <stdlib.h>

DUMMY_P newDummy(int x,int y,int icon,int color){
    DUMMY_P dummy = NULL;

    if(!ALLOC(dummy,DUMMY_P,DUMMY))
        exit(EXIT_FAILURE);
    dummy->obj = newGameObj(x,y,icon,color);

    return dummy;
}

void *dummy(void *args){

    RMTOBJ_P rmtObj = (RMTOBJ_P)args;
    DUMMY_P dummy = (DUMMY_P)rmtObj->obj;
    RRCHL_P rr = rmtObj->rr;
    int action;

    dummy->obj->dir = rand()%4;
    while(1){        
        if(IS_WALL(lookAhead(dummy->obj)))
            dummy->obj->dir = rand()%4;
        else{            
            moveObj(dummy->obj);
            eat(dummy->obj,gf);
        }

        send(rr->reqChl,dummy->obj);
        receive(rr->repChl,dummy->obj);
        
        usleep(ONE_SEC/4);
    }
}

void *dummy2(void *args){

    RMTOBJ_P rmtObj = (RMTOBJ_P)args;
    DUMMY_P dummy = (DUMMY_P)rmtObj->obj;
    RRCHL_P rr = rmtObj->rr;
    int action;

    dummy->obj->dir = rand()%4;
    while(1){
        if(!IS_WALL(lookLeft(dummy->obj)) || !IS_WALL(lookRight(dummy->obj)))
            newDir(dummy->obj);
        
        moveObj(dummy->obj);
        eat(dummy->obj,gf);        

        send(rr->reqChl,dummy->obj);
        //receive(rr->repChl,dummy->obj);

        usleep(ONE_SEC/4);
    }

}

void *dummy3(void *args){
}