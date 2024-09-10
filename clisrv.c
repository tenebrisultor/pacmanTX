/*clisrv.c*/
#include "clisrv.h"
#include "common.h"

#include <stdlib.h>

RRCHL_P newRRChl(CHL_P req,CHL_P rep){
    RRCHL_P rr = NULL;

    if(!ALLOC(rr,RRCHL_P,RRCHL))
        exit(EXIT_FAILURE);

    rr->reqChl = req;
    rr->repChl = rep;

    return rr;
}

RMTOBJ_P newRmtObj(void *obj,RRCHL_P rr){
    RMTOBJ_P rObj = NULL;

    if(!ALLOC(rObj,RMTOBJ_P,RMTOBJ))
        exit(EXIT_FAILURE);

    rObj->obj = obj;
    rObj->rr = rr;

    return rObj;
}

void setSrvReq(long int tskId,int type,SRVREQ_P req){

    req->tskId = tskId;
    req->type = type;

}
void sendReq(SRVREQ_P req,CHL_P reqChl){    
    send(reqChl,&req);
}

void setRRChl(CHL_P req,CHL_P rep,RRCHL_P rr){
    rr->reqChl = req;
    rr->repChl = rep;
}
