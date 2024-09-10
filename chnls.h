/* 
 * File:   chnls.h
 * Author: whitewizard
 *
 * Created on 6 novembre 2010, 20.20
 */

#ifndef _CHNLS_H
#define	_CHNLS_H

#include "shdadt.h"
//#include "clisrv.h"

#define PIPE_FAILED -1
#define PIPE_SIZE 2
#define READ_END 0
#define WRITE_END 1

#define DEF_CHL_MODE
#ifdef DEF_CHL_MODE
#define CHL_MODE PIPE_CHL
#else
#define CHL_MODE SHD_CHL
#endif

#define PIPE_SEND(p,obj,size) (write(p[WRITE_END],obj,size))
#define PIPE_RECEIVE(p,obj,size) (read(p[READ_END],obj,size))

typedef enum{PIPE_CHL,  //canale che fa uso di pipe
        SHM_CHL,        //canale che fa uso di memoria condivisa
        SYSV_SHM_CHL     //canale che fa uso di memoria condivisa tramite SYSV
}CHL_TYPE;

typedef struct{
    CHL_TYPE type;  //tipo del canale
    int size;       //dimensione unitaria del canale
    int block;      //numero di blocchi del canale
}CHL_INFO;          //informazioni sul canale
typedef CHL_INFO* CHL_INFO_P;

typedef struct{
    int fd[PIPE_SIZE];
}PIPE;
typedef PIPE* PIPE_P;

typedef union{
    PIPE_P pipe;            //pipe
    SHD_CBFF_P cbff;        //buffer circolare
}CHLDVC;                    //dispositivo di canale
typedef CHLDVC* CHLDVC_P;   //puntatore a dispositivo di canale

typedef struct{
    CHL_TYPE type;
    int size;               //dimensione unitaria del buffer
    int block;              //numero di blocchi del buffer
    CHLDVC_P dvc;
}CHL;                       //canale di comunicazione
typedef CHL* CHL_P;         //puntatore a canale

typedef struct{
    CHL_P in;
    CHL_P out;
}DPLX_CHL;
typedef DPLX_CHL* DPLX_CHL_P;

PIPE_P newPipe();
CHLDVC_P newChlDvc(CHL_TYPE type,int size,int block);
CHL_P newChl(CHL_TYPE type, int size,int block);
CHL_INFO_P newChlInfo(CHL_TYPE type,int size,int block);
CHL_P newChlByInfo(CHL_INFO_P inf);
void setDplxChl(CHL_P in,CHL_P out,DPLX_CHL_P dplx);
void send(CHL_P chl,void *obj);
void receive(CHL_P chl,void *obj);
void freePipe(PIPE_P p);


#endif	/* _CHNLS_H */

