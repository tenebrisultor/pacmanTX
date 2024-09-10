/*mailbox.c*/
#include "mailbox.h"
#include "common.h"

#include <stdlib.h>

MAILBOX_P newMailBox(long int tskId,CHL_P in,CHL_P out){
    MAILBOX_P mb = NULL;

    if(!ALLOC(mb,MAILBOX_P,MAILBOX))
        exit(EXIT_FAILURE);

    mb->tskId = tskId;
    mb->inChl = in;
    mb->outChl = out;

    return mb;
}

void sendMail(void *mail,MAILBOX_P mb){send(mb->outChl,mail);}
void readMail(void *mail,MAILBOX_P mb){receive(mb->inChl,mail);}

MAILBOX_SET_P newMailBoxSet(int maxbox,CHL_INFO_P inInfo,CHL_INFO_P outInfo){
    MAILBOX_SET_P mbs = NULL;
    
    if(!ALLOC(mbs,MAILBOX_SET_P,MAILBOX_SET))
        exit(EXIT_FAILURE);
    mbs->inInfo = inInfo;
    mbs->outInfo = outInfo;
    mbs->regTsk = 0;
    
    return mbs;
}

int getIndexById(long int id,MAILBOX_SET_P mbs){
    int i = 0;

    //se non ci sono task registrati
    if(mbs->regTsk==0)
        return -1;      //restituisci valore sentinella

    //fino a quando ci sono elementi da scandire o il task non è registrato
    while(i<mbs->regTsk && mbs->boxSet[i]->tskId!=id)
        i++;                                            //scandisci la lista

    return i;                                           //restituisci l'indice
}

RRCHL_P regTsk(long int id,MAILBOX_SET_P mbs){

    if(mbs->regTsk<=MAX_MAILBOX_SET){
        if(mbs->regTsk<=MAX_MAILBOX_SET){
            mbs->boxSet[mbs->regTsk]->tskId = id;
            mbs->boxSet[mbs->regTsk]->inChl = newChlByInfo(mbs->inInfo);
            mbs->boxSet[mbs->regTsk]->outChl = newChlByInfo(mbs->outInfo);
            return newRRChl(mbs->boxSet[mbs->regTsk]->inChl,
                mbs->boxSet[mbs->regTsk]->outChl);
        }
    }

    return NULL;
}
int unRegTsk(long int id,MAILBOX_P mbs){
}
int sendMailBox(long int id,void *mail,MAILBOX_SET_P mbs){

    int idx = getIndexById(id,mbs);

    if(idx !=-1){
        sendMail(mail,mbs->boxSet[idx]);
    }
}

int readMailBox(long int id,void *mail,MAILBOX_SET_P mbs){

    int idx = getIndexById(id,mbs);

    if(idx !=-1){
        readMail(mail,mbs->boxSet[idx]);
    }
}
