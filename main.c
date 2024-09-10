/* 
 * File:   main.c
 * Author: whitewizard
 *
 * Created on 16 dicembre 2010, 17.27
 */

#include <stdio.h>
#include <stdlib.h>

#include "collman.h"
#include "task.h"
#include "graph.h"
#include "gamefield.h"

GAMEFIELD_P gf;

/*
 * 
 */
int main(int argc, char** argv) {

    TASK_P tsk = newTask(TASK_MODE,NULL,collHndl);

    initGraph();    
    gf = loadGameField("level2.txt");
    //wdrawMaze(stdscr,gf);
    printw("This is a String");
    refresh();
    //tskBuilder(tsk);
    while(1){
    }
    waitTask(tsk);
    endGraph();
    
    return (EXIT_SUCCESS);
}

