/* 
 * File:   graph.h
 * Author: whitewizard
 *
 * Created on 18 novembre 2010, 17.21
 */

#ifndef _GRAPH_H
#define	_GRAPH_H

#include "curses.h"
#include "chnls.h"

//#define COLOR_MODE

#define COORDCMP(a,b) (a->x==b->x && a->y==b->y)
#define GETX(c) (c.x)
#define GETY(c) (c.y)

#define putPixel(pxl) (wputPixel(stdscr,pxl->pos,pxl->ch,pxl->color))

typedef enum{TOP_LEFT,CENTER,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT}WINDPOS;

typedef struct{
    int x;
    int y;
}COORD;
typedef COORD* COORD_P;

typedef struct{
    COORD_P pos;
    char ch;
    int color;
}PIXEL;
typedef PIXEL* PIXEL_P;

typedef struct{
    int width;
    int height;
    int startX;
    int startY;
    int border;
}RECTANGLE;
typedef RECTANGLE* RECTANGLE_P;

typedef enum{CLRPAC,CLRSHT,CLRGHT,CLRWAL,CLRPOW}OBJCOL;

COORD_P newCoord(int x,int y);
void setCoord(int x,int y,COORD_P c);
PIXEL_P newPixel(int x,int y,char ch,int color);
void setPixel(int x,int y,char ch,int color,PIXEL_P p);
void wputPixel(WINDOW *wnd,COORD_P pos,char icon,int color);
RECTANGLE_P newRectangle(int width,int height,int startx,int starty,int border);
RECTANGLE_P getScreenInfo();

void freeCoord(COORD_P crd);
void freePixel(PIXEL_P pxl);

void setRectangle(RECTANGLE_P inf,int width,int height,int startX,int startY,
        int border);
WINDOW* newWindow(RECTANGLE_P inf);
WINDOW* newWindow2(int height,int width,WINDPOS pos);

void initGraph();
void initColors();
void endGraph(void);

#endif	/* _GRAPH_H */

