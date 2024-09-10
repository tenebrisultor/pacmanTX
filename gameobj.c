/*gameobj.c*/
#include "gameobj.h"
#include "common.h"

#include <stdlib.h>

GAMEOBJ_P newGameObj(int x,int y,char icon,int color){
    GAMEOBJ_P obj = NULL;

    if(!ALLOC(obj,GAMEOBJ_P,GAMEOBJ))
        exit(EXIT_FAILURE);

    setGameObj(x,y,icon,color,obj);

    return obj;
}

void setGameObj(int x,int y,char icon,int color,GAMEOBJ_P obj){
    setCoord(x,y,&obj->cur);    
    obj->icon = icon;
    obj->color = color;
    obj->eat = ' ';
}

char lookAhead(GAMEOBJ_P obj){

    char charAt;
    
    switch(obj->dir){
        case NORD:
            charAt = getAt(obj->cur.x,obj->cur.y-1,gf);
            break;
        case SUD:
            charAt = getAt(obj->cur.x,obj->cur.y+1,gf);
            break;
        case OVEST:
            charAt = getAt(obj->cur.x-1,obj->cur.y,gf);
            break;
        case EST:
            charAt = getAt(obj->cur.x+1,obj->cur.y,gf);
            break;
    }

    return charAt;
}

char lookLeft(GAMEOBJ_P obj){

    char charAt;

    switch(obj->dir){
        case NORD:
            charAt = getAt(obj->cur.x-1,obj->cur.y,gf);
            break;
        case SUD:
            charAt = getAt(obj->cur.x+1,obj->cur.y,gf);
            break;
        case OVEST:
            charAt = getAt(obj->cur.x,obj->cur.y+1,gf);
            break;
        case EST:
            charAt = getAt(obj->cur.x,obj->cur.y-1,gf);
            break;
    }

    return charAt;

}

char lookRight(GAMEOBJ_P obj){

    char charAt;

    switch(obj->dir){
        case NORD:
            charAt = getAt(obj->cur.x+1,obj->cur.y,gf);
            break;
        case SUD:
            charAt = getAt(obj->cur.x-1,obj->cur.y,gf);
            break;
        case OVEST:
            charAt = getAt(obj->cur.x,obj->cur.y-1,gf);
            break;
        case EST:
            charAt = getAt(obj->cur.x,obj->cur.y+1,gf);
            break;
    }

    return charAt;

}

void moveObj(GAMEOBJ_P obj){

    SAVE_CUR(obj);
    switch(obj->dir){
        case NORD:            
            obj->cur.y--;
            break;
        case SUD:            
            obj->cur.y++;
            break;
        case OVEST:
            obj->cur.x--;
            break;
        case EST:            
            obj->cur.x++;
            break;        
        default:
            break;
    }
}

int checkCollision(GAMEOBJ_P obj1,GAMEOBJ_P obj2){
    int i;
    DIRECT toward = obj1->dir;

    for(i=0;i<4;i++){
        obj1->dir = i;
        lookAhead(obj1)==obj2->icon;
        return 1;
    }
    return 0;
}

void eat(GAMEOBJ_P obj,GAMEFIELD_P gf){
    obj->eat = getAt(obj->cur.x,obj->cur.y,gf);
}

void wdrawObj(WINDOW *wnd,GAMEOBJ_P obj){
    int objColor;

    wputPixel(wnd,&obj->cur,obj->icon,obj->color);
    wrefresh(wnd);
    switch(obj->eat){
        case PILL_ICON:
            objColor = 1;
            break;
        case POWER_PILL_ICON:
            objColor = 2;
            break;
        default:
            break;
    }
    wputPixel(wnd,&obj->old,obj->eat,objColor);
    wrefresh(wnd);
}

DIRECT getRevDir(DIRECT dir){

    switch(dir){
        case NORD:
            return SUD;
            break;
        case SUD:
            return NORD;
            break;
        case OVEST:
            return EST;
            break;
        case EST:
            return OVEST;
            break;
    }
}

void newDir(GAMEOBJ_P obj){
    int aviable[3];
    int wayCount = 0;
    DIRECT toward = obj->dir;
    int i;

    for(i=0;i<4;i++){
        if(getRevDir(toward)==i)
            continue;
        obj->dir = i;
      if(!IS_WALL(lookAhead(obj)))
            aviable[wayCount++] = i;
    }

    if(wayCount==0)
        obj->dir = getRevDir(toward);
    else
        obj->dir = aviable[rand()%wayCount];

}
