/* 
 * File:   common.h
 * Author: whitewizard
 *
 * Created on 6 novembre 2010, 19.53
 */

#ifndef _COMMON_H
#define	_COMMON_H

//#define DEBUG

#define ONE_SEC 1000000

#define NALLOC(p,type,size,n) (p=(type)malloc(sizeof(size)*n))
#define ALLOC(p,type,size) NALLOC(p,type,size,1)

#endif	/* _COMMON_H */

