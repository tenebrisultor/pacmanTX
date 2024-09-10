/*
 * collman.h
 */
#include "collman.h"
#include "chnls.h"
#include "task.h"
#include "graph.h"

#include "pacman.h"
#include "ghost.h"
#include "worm.h"

#include <curses.h>

void *collHndl(void *args){

    int i;
    WINDOW *gameWnd;
    WINDOW *outWnd;
    PACMAN_P pac;    
    GHOST_P ght[GHOSTS];
    RMTOBJ_P ghtRmt[GHOSTS];
    TASK_P pacTsk;
    TASK_P wrmTsk;
    TASKGRP_P ghtGrp;
    GAMEOBJ tmp;
    CHL_P in;

    //initGraph();

    //gf = loadGameField("level2.txt");    
    wdrawMaze(gf->gameWnd,gf);
    //outWnd = newwin(10,10,0,0);
    //wprintw(outWnd,"Messaggio");
    //wrefresh(outWnd);

    in = newChl(CHL_MODE,sizeof(GAMEOBJ),10);
    pac = newPacman(DEF_PAC_X,DEF_PAC_Y,'@',PAC_COLOR,0,0);
    wdrawObj(gf->gameWnd,&pac->obj);
    
    for(i=0;i<GHOSTS;i++){
        ght[i] = newGhost(DEF_GHOST_X+i,DEF_GHOST_Y,'H',0);
        ghtRmt[i] = newRmtObj(ght[i],newRRChl(in,NULL));
    }
    ghtGrp = newTskGrp(GHOSTS,TASK_MODE,(void*)ghtRmt,ghost);
    tskGrpBuilder(ghtGrp);

    pacTsk = newTask(TASK_MODE,newRmtObj(pac,newRRChl(in,NULL)),pacman);
    tskBuilder(pacTsk);
    

    while(1){
        receive(in,&tmp);
        wdrawObj(gf->gameWnd,&tmp);
    }

    waitTask(pacTsk);
    waitTskGrp(ghtGrp);
    
    //endGraph();
}


void *drawMazeTest(void *args){

    WINDOW *mainWind;    

    initGraph();
    gf = loadGameField("level0.txt");
    wdrawMaze(gf->gameWnd,gf);

    while(1){        
    }

    endGraph();
}