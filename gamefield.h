/* 
 * File:   gamefield.h
 * Author: whitewizard
 *
 * Created on 20 novembre 2010, 13.33
 */

#ifndef _GAMEFIELD_H
#define	_GAMEFIELD_H

#include "chnls.h"
#include "graph.h"
#include <stdio.h>
#include <curses.h>

#define WALL_ICON '#'
#define PILL_ICON '.'
#define POWER_PILL_ICON '+'
#define WALL_COLOR 0

#define IS_WALL(c) (c==WALL_ICON)

//typedef enum{WALL,PILL,POWER_PILL}STATIC_OBJ;

typedef struct{
    int row;            //numero di righe del campo da gioco
    int cols;           //numero di colonne del campo da gioco
    char **maze;        //il labirinto
    int pillCnt;        //contatore delle pillole
    int powerCnt;       //contatore dei power_pill
    WINDOW *gameWnd;    //finestra che visualizza il labirinto
}GAMEFIELD;
typedef GAMEFIELD* GAMEFIELD_P;

typedef enum{getAt_,setAt_}GF_REQ_TYPE;     //gamefiled request

typedef union{
    GF_REQ_TYPE type;
    long int from;
    long int to;
    COORD pos;
    char charAt;
}GF_REQ;
typedef GF_REQ* GF_REQ_P;

typedef struct{
    long int from;
    long int to;
    char charAt;
}GF_REP;
typedef GF_REP* GF_REP_P;

GAMEFIELD_P loadGameField(char *fname);
GAMEFIELD_P newGameField(int x,int y);
void loadMaze(FILE *fp,GAMEFIELD_P gf);
void wdrawMaze(WINDOW* wnd,GAMEFIELD_P gf);

char getAt(int x,int y,GAMEFIELD_P gf);
char rmGetAt(int x,int y,CHL_P reqChl,CHL_P repChl);
void setAt(int x,int y,char ch,GAMEFIELD_P gf);
void rmSetAt(int x, int y,char ch,CHL_P chl);

void *gameFldSrv(void *args);

#endif	/* _GAMEFIELD_H */

