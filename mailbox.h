/* 
 * File:   mailbox.h
 * Author: whitewizard
 *
 * Created on 3 dicembre 2010, 10.24
 */

#ifndef _MAILBOX_H
#define	_MAILBOX_H

#include "chnls.h"
#include "clisrv.h"

#define MAX_MAILBOX_SET 10

typedef struct{
    long int tskId;
    CHL_P inChl;
    CHL_P outChl;
}MAILBOX;
typedef MAILBOX* MAILBOX_P;

typedef struct{
    int regTsk;             //task nella mailbox
    CHL_INFO_P inInfo;      //canale di input
    CHL_INFO_P outInfo;     //canale di output
    MAILBOX_P boxSet[MAX_MAILBOX_SET];  //il set di mailbox
}MAILBOX_SET;
typedef MAILBOX_SET* MAILBOX_SET_P;

MAILBOX_P newMailBox(long int tskId,CHL_P in,CHL_P out);
void sendMail(void *mail,MAILBOX_P mb);
void readMail(void *mail,MAILBOX_P mb);
MAILBOX_SET_P newMailBoxSet(int maxbox,CHL_INFO_P inInfo,CHL_INFO_P outInfo);
int getIndexById(long int id,MAILBOX_SET_P mbs);
RRCHL_P regTsk(long int id,MAILBOX_SET_P mbs);
int unRegTsk(long int id,MAILBOX_P mbs);
int sendMailBox(long int id,void *mail,MAILBOX_SET_P mbs);
int readMailBox(long int id,void *mail,MAILBOX_SET_P mbs);



#endif	/* _MAILBOX_H */

