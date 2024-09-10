/* 
 * File:   mailboxserver.h
 * Author: whitewizard
 *
 * Created on 14 dicembre 2010, 17.20
 */

#ifndef _MAILBOXSERVER_H
#define	_MAILBOXSERVER_H

#include "clisrv.h"

#define MAX_TASK 10

typedef enum{reg_task,  //richiesta di registrazione di un task
        unreg_task,     //richiesta di cancellazione di un task
        get_chl         //richiesta dei canali di comunicazione di un task
}chlswtch_req_type;

typedef struct{
    long int mit;       //mittende della richiesta
    long int dst;       //destinatario della richiesta
}chlswtch_req;

typedef struct{
    RRCHL_P rr;
}chlswtch_rep;

void *mailboxserver(void *args);

#endif	/* _CHLSWITCHER_H */

