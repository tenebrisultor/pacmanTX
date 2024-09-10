/* 
 * File:   clisrv.h
 * Author: whitewizard
 *
 * Created on 23 novembre 2010, 14.00
 */

#ifndef _CLISRV_H
#define	_CLISRV_H

#include "chnls.h"

typedef struct{
    CHL_P reqChl;
    CHL_P repChl;
}RRCHL;
typedef RRCHL* RRCHL_P;

typedef struct{
    void *obj;
    RRCHL_P rr;
}RMTOBJ;
typedef RMTOBJ* RMTOBJ_P;

typedef struct{
    long int tskId;
    int type;
}SRVREQ;
typedef SRVREQ* SRVREQ_P;

void setSrvReq(long int tskId,int type,SRVREQ_P req);
void sendReq(SRVREQ_P req,CHL_P reqChl);
RRCHL_P newRRChl(CHL_P req,CHL_P rep);
RMTOBJ_P newRmtObj(void *obj,RRCHL_P rr);
void setRRChl(CHL_P req,CHL_P rep,RRCHL_P rr);

#endif	/* _CLISRV_H */

