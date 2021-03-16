/*
 * cstring.h
 *
 *  Created on: Aug 28, 2020
 *      Author: eric
 */


#ifndef _CSTRING_H
#define _CSTRING_H
#ifndef _PTHREAD_H
#include <pthread.h>
#endif
#define TO_STRING(val) #val
typedef struct cstring{
	unsigned int len;
	char* string;

} cstring_t;
#ifdef __cplusplus
extern "c" {
#endif
extern pthread_mutex_t cstring_mutex;

extern cstring_t* cstring_alloc_init(char* s);
extern cstring_t* cstring_cat(cstring_t* s1,const cstring_t* s2);
extern cstring_t* cstring_ncat(cstring_t* s1,const cstring_t* s2,size_t n);
extern cstring_t* cstring_cpy(cstring_t* s1,const cstring_t* s2);
extern cstring_t* cstring_ncpy(cstring_t* s1,const cstring_t* s2,size_t count);
extern void cstring_free(cstring_t** str);
#ifdef __cplusplus
}
#endif
#endif /* CSTRING_H_ */
