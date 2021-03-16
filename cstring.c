/*
 * cstring.c
 *
 *  Created on: Aug 29, 2020
 *      Author: eric
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "cstring.h"
#include "dll.h"

pthread_mutex_t cstring_mutex = PTHREAD_MUTEX_INITIALIZER;

DLL_PUBLIC cstring_t* cstring_alloc_init(char* s)
{
	pthread_mutex_lock(&cstring_mutex);
	cstring_t* this=malloc(sizeof(cstring_t));
	if(!this){
		return NULL;
	}
	this->string=malloc((strlen(s)+1)*sizeof(char));
	if(!this->string){
		printf("Allocation of string failed.\n");
		return NULL;
	}

	strcpy(this->string,s);
	this->len=strlen(this->string);
	pthread_mutex_unlock( &cstring_mutex);
	return this;
}
DLL_PUBLIC cstring_t* cstring_cat(cstring_t* s1,const cstring_t* s2)
{
	pthread_mutex_lock(&cstring_mutex);
	char* str=realloc(s1->string,(s1->len+s2->len+1)*sizeof(char));
	if(!str){
		return NULL;
	}
	strcat(s1->string,s2->string);
	s1->len=strlen(s1->string);
	pthread_mutex_unlock( &cstring_mutex);
	return s1;
}
DLL_PUBLIC cstring_t* cstring_ncat(cstring_t* s1,const cstring_t* s2,size_t n)
{
		pthread_mutex_lock(&cstring_mutex);
		char* str=realloc(s1,(s1->len+n+1)*sizeof(char));
		if(!str){
			return NULL;
		}
		strncat(s1->string,s2->string,n);
		s1->len=strlen(s1->string);
		pthread_mutex_unlock( &cstring_mutex);
		return s1;
}
DLL_PUBLIC cstring_t* cstring_cpy(cstring_t* s1,const cstring_t* s2)
{
	pthread_mutex_lock(&cstring_mutex);
	if(s1->len<s2->len){
		s1->string=realloc(s1,(s2->len+1)*sizeof(char));
		strcpy(s1->string,s2->string);
		s1->len=strlen(s1->string);
	}
	else{
		strcpy(s1->string,s2->string);
		s1->len=strlen(s1->string);
	}
	pthread_mutex_unlock( &cstring_mutex);
	return s1;
}
DLL_PUBLIC cstring_t* cstring_ncpy(cstring_t* s1,const cstring_t* s2,size_t count)
{
	pthread_mutex_lock(&cstring_mutex);
	if(s1==NULL||s2==NULL){
		return NULL;
	}
	strncpy(s1->string,s2->string,count);
	s1->len=strlen(s1->string);
	pthread_mutex_unlock( &cstring_mutex);
	return s1;
}
DLL_PUBLIC void cstring_free(cstring_t** str){
	assert((str!=NULL)&&(*str!=NULL));
	pthread_mutex_lock(&cstring_mutex);
	if(!(*str)->string){
		free(*str);
		return;
	}
	free((*str)->string);
	free(*str);
	*str=NULL;
	pthread_mutex_unlock( &cstring_mutex);
	return;
}

