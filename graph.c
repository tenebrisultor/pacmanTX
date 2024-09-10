/*graph.c*/
#include "graph.h"
#include "common.h"
#include "gamefield.h"
#include <stdlib.h>

COORD_P newCoord(int x,int y){
    COORD_P crd = NULL;

    if(!ALLOC(crd,COORD_P,COORD)) exit(EXIT_FAILURE);
    setCoord(x,y,crd);

    return crd;
}

void setCoord(int x,int y,COORD_P c){
    c->x = x;
    c->y = y;
}

PIXEL_P newPixel(int x,int y,char ch,int color){
    PIXEL_P pxl = NULL;

    if(!ALLOC(pxl,PIXEL_P,PIXEL)) exit(EXIT_FAILURE);

    pxl->ch = ch;
    pxl->color = color;
    pxl->pos = newCoord(x,y);

    return pxl;

}
void setPixel(int x,int y,char ch,int color,PIXEL_P pxl){

    setCoord(x,y,pxl->pos);
    pxl->ch = ch;
    pxl->color = color;
}

void initGraph(){

    if(!(initscr())){
        fprintf(stderr,"Errore durante l'inizializzazione delle curses");
        fprintf(stderr,"Premere un tasto per terminare...");
        exit(EXIT_FAILURE);
    }
    #ifdef COLOR_MODE
    initColors();
    #endif
    curs_set(0);
    noecho();
    cbreak();
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
    
    clear();
}

void initColors(){

    if(has_colors()){
        if(start_color()!=ERR){
            init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLUE);        //muro
            init_pair(COLOR_WHITE,COLOR_WHITE,COLOR_BLACK);     //pillola normale
            init_pair(COLOR_MAGENTA,COLOR_MAGENTA,COLOR_BLACK); //power pill
            init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);   //pacman
            init_pair(COLOR_RED,COLOR_RED,COLOR_BLACK);         //shot
            init_pair(COLOR_GREEN,COLOR_GREEN,COLOR_BLACK);     //ghost
            init_pair(COLOR_YELLOW,COLOR_BLUE,COLOR_YELLOW);
            init_pair(COLOR_RED,COLOR_BLUE,COLOR_YELLOW);
            init_pair(COLOR_WHITE,COLOR_BLUE,COLOR_YELLOW);
            init_pair(COLOR_MAGENTA,COLOR_BLUE,COLOR_YELLOW);
            init_pair(COLOR_RED,COLOR_BLUE,COLOR_GREEN);     //sfondo
        }else{
            printw("Errore durante l'inizializzazione dei colori\n");
            refresh(),
            sleep(3);
            exit(EXIT_FAILURE);
        }
    }else{
        printw("Il terminale non supporta i colori");
        refresh();
        sleep(3);
    }
}

void wputPixel(WINDOW *wnd,COORD_P pos,char icon,int color){

    #ifdef COLOR_MODE
    wattron(wnd,A_STANDOUT | COLOR_PAIR(color));
    #endif

    mvwaddch(wnd,pos->y,pos->x,icon);    

    #ifdef COLOR_MODE
    wattroff(wnd,A_STANDOUT | COLOR_PAIR(color));
    #endif

}

void freeCoord(COORD_P crd){free(crd);}

void freePixel(PIXEL_P pxl){
    freeCoord(pxl->pos);
    free(pxl);
}

RECTANGLE_P newRectangle(int width,int height,int startx,int starty,int border){
    RECTANGLE_P rect = NULL;

    if(!ALLOC(rect,RECTANGLE_P,RECTANGLE))
        exit(EXIT_FAILURE);
    rect->width = width;
    rect->height = height;
    rect->startX = startx;
    rect->startY = starty;
    rect->border = border;

    return rect;
}

RECTANGLE_P getScreenInfo(){

    int maxX,maxY;
    getmaxyx(stdscr,maxY,maxX);

    return newRectangle(maxY,maxX,0,0,0);
}

void setRectangle(RECTANGLE_P inf,int width,int height,int startX,int startY,
    int border){

        inf->width = width;
        inf->height = height;
        inf->startX = startX;
        inf->startY = startY;
        inf->border = border;
}

WINDOW* newWindow(RECTANGLE_P inf){
    WINDOW* win = NULL;

    win = newwin(inf->height,inf->width,inf->startY,inf->startX);
    if(inf->border)
        box(win,0,0);

    return win;
}

WINDOW* newWindow2(int height,int width,WINDPOS pos){

    int startX,startY;
    WINDOW* win = NULL;
    

}

void endGraph(void){
    endwin();
}
