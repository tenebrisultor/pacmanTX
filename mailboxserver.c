/*mailboxserver.c*/
#include "mailboxserver.h"
#include "mailbox.h"
#include "clisrv.h"
#include "chnls.h"

void *mailboxserver(void *args){
    RMTOBJ_P rObj = (RMTOBJ_P)args;
    MAILBOX_SET_P mbs = (MAILBOX_SET_P)rObj->obj;
    RRCHL_P rr = rObj->rr;

    while(1){

    }
}


