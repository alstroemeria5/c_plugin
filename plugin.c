/*
 * plugin.c
 *
 *  Created on: Feb 27, 2021
 *      Author: eric
 */

#include <dlfcn.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "plugin.h"
#include "dll.h"

void plugin_init(char* directory_path,char* name,int order,plugin_DEF* target){
	char* libname=malloc((strlen(directory_path)+strlen(name)+LIB_NAME_EXTENSION)*sizeof(char));
	strcpy(libname,directory_path);
	strcat(libname,LIB_PREFIX);
	libname=strcat(libname,name);
	libname=strcat(libname,LIB_SUFFIX);
	target->lib=dlopen(libname,RTLD_LAZY);
	target->name=malloc((strlen(name)+1)*sizeof(char));
	target->static_order=order;
	strcpy(target->name,name);
	if(!target->lib){
#ifdef DEBUG
		plugin_debug(stderr,"%s\n",dlerror());
#endif
		target->validity=enum_dll_unable_to_open;
		target->func=NULL;
		free(libname);
		return;
	}
	target->func=(func_DEF)(dlsym(target->lib,name));
	if(!target->func){
		target->validity=enum_dll_unable_to_find_symbol;
#ifdef DEBUG
		plugin_debug(stderr,"%s\n",dlerror());
#endif
		free(libname);
		return;
	}
	target->validity=enum_dll_success;
	free(libname);
	return;

}
plugin_node_DEF* plugin_node_alloc_init(char* directory_name,char* name,int order)
{
	plugin_node_DEF* target=malloc(sizeof(plugin_node_DEF));
#ifdef MEMORY_LEAK
	plugin_debug(stderr,"plugin_node be allocated and its address to be %p.\n" ,target);
#endif
	plugin_init(directory_name,name,order,&target->plugin);
	target->next=NULL;
	target->previous=NULL;
	return target;
}
DLL_PUBLIC void plugin_node_insert_to_list(plugin_node_DEF* target,plugin_linked_list_DEF* list)
{
	if(list->head==NULL&&list->tail==NULL){
		
		list->head=target;
		list->head->next=NULL;
		list->head->previous=NULL;
		list->tail=target;
		list->tail->next=NULL;
		list->tail->previous=NULL;
		list->number_of_node=1;
		return;
	}
#if 0
	for(plugin_node_DEF* temp=list->head;temp!=NULL;temp=temp->next){
			if(!strcmp(temp->plugin.name,target->plugin.name)){
				return;
			}
	}
#endif
	target->previous=list->tail;
	target->next=NULL;
	target->previous->next=target;
	list->tail=target;
	list->number_of_node++;
	return;
}
DLL_PUBLIC void plugin_node_alloc_init_insert_to_list(char* directory_name,char* name,int order,plugin_linked_list_DEF* list)
{
	plugin_node_insert_to_list(plugin_node_alloc_init(directory_name,name,order),list);
}

DLL_PUBLIC void plugin_node_free(plugin_node_DEF** ptr_plugin_node)
{
	assert((ptr_plugin_node!=NULL)&&(*ptr_plugin_node!=NULL));
	if((*ptr_plugin_node)->plugin.lib){
		dlclose((*ptr_plugin_node)->plugin.lib);	
	}
	else{
		;
	}
	free((*ptr_plugin_node)->plugin.name);
	free((*ptr_plugin_node));
#ifdef	MEMORY_LEAK 
		plugin_debug(stdout,"plugin_node address %p now is being freed.\n",*ptr_plugin_node);
#endif
	*ptr_plugin_node=NULL;
	return;
}
DLL_PUBLIC void plugin_node_all_free_from_list(plugin_linked_list_DEF* list)
{
	if(list->head==NULL&&list->tail==NULL){
		return;
	}
	plugin_node_DEF* tail=list->tail;
	plugin_node_DEF* temp_node;
	while(tail!=NULL){
		temp_node=tail;
		tail=tail->previous;
		plugin_node_free(&temp_node);		
	}	
	
}
DLL_PUBLIC plugin_linked_list_DEF* plugin_linked_list_alloc_init()
{
	plugin_linked_list_DEF* temp_list=malloc(sizeof(plugin_linked_list_DEF));
	temp_list->head=NULL;
	temp_list->tail=NULL;
	return temp_list;
}
DLL_PUBLIC void plugin_linked_list_nullify(plugin_linked_list_DEF* ptr_plugin_list)
{
#ifdef DEBUG
	plugin_debug(stderr,"%s\n","Beware it may loss track of the nodes belonging to this plugin linked list");
#endif
	ptr_plugin_list->head=NULL;
	ptr_plugin_list->tail=NULL;
	ptr_plugin_list->number_of_node=0;
	return;
}
DLL_PUBLIC void plugin_linked_list_free(plugin_linked_list_DEF** list)
{
	assert((list!=NULL)&&(*list!=NULL));
	plugin_node_all_free_from_list(*list);
	free(*list);
	*list=NULL;
	return;
}

