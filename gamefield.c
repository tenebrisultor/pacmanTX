/*gamefield.c*/
#include "gamefield.h"
#include "common.h"
#include "clisrv.h"

#include <stdlib.h>

GAMEFIELD_P loadGameField(char *fname){
    FILE *fp;
    int i,j;
    GAMEFIELD_P gf = NULL;

    if(!(fp=fopen(fname,"r"))) exit(EXIT_FAILURE);

    fscanf(fp,"%d%d",&i,&j);
    gf = newGameField(i,j);
    loadMaze(fp,gf);
    fclose(fp);

    return gf;
}

GAMEFIELD_P newGameField(int row,int col){
    GAMEFIELD_P gf = NULL;

    if(!ALLOC(gf,GAMEFIELD_P,GAMEFIELD)) exit(EXIT_FAILURE);

    gf->row = row;
    gf->cols = col;
    gf->pillCnt = 0;
    gf->powerCnt = 0;
    gf->gameWnd = newwin(gf->row,gf->cols,(LINES-gf->row)/2,(COLS-gf->cols)/2);

    return gf;

}

void loadMaze(FILE *fp,GAMEFIELD_P gf){

    int i,j;

    if(!NALLOC(gf->maze,char**,char*,gf->row))
        exit(EXIT_FAILURE);
    for(i=0;i<gf->row;i++){
        if(!NALLOC(gf->maze[i],char*,char,gf->cols))
            exit(EXIT_FAILURE);
        for(j=0;j<gf->cols;j++){
            fscanf(fp,"%c",&gf->maze[i][j]);
            switch(gf->maze[i][j]){
                case PILL_ICON:
                    gf->pillCnt++;
                    break;
                case POWER_PILL_ICON:
                    gf->powerCnt++;
                    break;
                default:
                    break;
            }
        }
    }
}

void wdrawMaze(WINDOW* wnd,GAMEFIELD_P gf){
    int i,j;
    char ch;

    #ifdef COLOR_MODE
    wattron(wnd,A_STANDOUT | COLOR_PAIR(WALL_COLOR));
    #endif

    for(i=0;i<gf->row;i++){
        for(j=0;j<gf->cols;j++){
            ch = gf->maze[i][j];
            mvwaddch(wnd,i,j,ch);            
        }
    }    
    wrefresh(wnd);
    #ifdef COLOR_MODE
    wattroff(wnd,A_STANDOUT | COLOR_PAIR(WALL_COLOR));
    #endif
    
}

char getAt(int x,int y,GAMEFIELD_P gf){return gf->maze[y][x];}

char rmGetAt(int x,int y,CHL_P reqChl,CHL_P  repChl){
    GF_REQ req;
    GF_REP rep;

    req.from = getTskId();
    setCoord(x,y,&req.pos);
    req.type = getAt_;
    send(reqChl,&req);

    receive(repChl,&rep);

    printf("From Server %c\n",rep.charAt);

    return rep.charAt;
}

void setAt(int x,int y,char ch,GAMEFIELD_P gf){gf->maze[y][x] = ch;}

void rmSetAt(int x, int y,char ch,CHL_P chl){
    GF_REQ req;

    setCoord(x,y,&req.pos);
    req.charAt = ch;
    req.type = setAt_;

    send(chl,&req);
}

void *gameFldSrv(void *args){
    RMTOBJ_P rObj = (RMTOBJ_P)args;
    char charAt;

    GF_REQ req;
    GF_REP rep;

    rep.from = getTskId();
    while(1){
        receive(rObj->rr->reqChl,&req);
        printf("Request from %ld\n",req.from);
        switch(req.type){
            case getAt_:
                rep.charAt = getAt(req.pos.x,req.pos.y,
                        ((GAMEFIELD_P)rObj->obj));
                rep.to = req.from;
                send(rObj->rr->repChl,&rep);
                break;
            case setAt_:
                setAt(req.pos.x,req.pos.x,req.charAt,((GAMEFIELD_P)rObj->obj));
                break;
            default:
                printf("Request not supported\n");
                break;
        }
    }
}
