/*
 * plugin.h
 *
 *  Created on: Feb 27, 2021
 *      Author: eric
 */

#ifndef _PLUGIN_H
#define _PLUGIN_H

#define plugin_debug(filedescriptor,format,...) fprintf(filedescriptor,"[filename:%s,line:%d]		"format,__FILE__,__LINE__,__VA_ARGS__);

#define LIB_NAME_EXTENSION	7
#define LIB_SUFFIX	".so"
#define LIB_PREFIX	"lib"
typedef struct plugin plugin_DEF;
typedef int (*func_DEF)(int,int);
typedef struct plugin_node plugin_node_DEF;
typedef struct plugin_linked_list plugin_linked_list_DEF;
enum dll_validity{	
	enum_dll_unable_to_open,
	enum_dll_unable_to_find_symbol,
	enum_dll_success
};
#ifndef __BOOLEAN__
#define __BOOLEAN__
#define bool int
#define true 1
#define false 0
#endif 

struct plugin{
	void* lib;
	func_DEF func;
	char* name;
	enum dll_validity validity;
	int static_order;
};

struct plugin_node{
	plugin_DEF plugin;
	struct plugin_node* next;
	struct plugin_node* previous;
};
struct plugin_linked_list{
	struct plugin_node* head;
	struct plugin_node* tail;
	int number_of_node;
};
#ifdef __cplusplus
extern "c" {
#endif
extern void plugin_init(char* directory_path,char* name,int order,plugin_DEF* target);
extern plugin_node_DEF* plugin_node_alloc_init(char* directory_name,char* name,int order);
extern void plugin_node_free(plugin_node_DEF** ptr_plugin_node);
extern void plugin_node_insert_to_list(plugin_node_DEF* target,plugin_linked_list_DEF* list);
extern void plugin_node_alloc_init_insert_to_list(char* directory_name,char* name,int order,plugin_linked_list_DEF* list);
extern void plugin_node_all_free_from_list(plugin_linked_list_DEF* list);
extern plugin_linked_list_DEF* plugin_linked_list_alloc_init();
extern void plugin_linked_list_nullify(plugin_linked_list_DEF* ptr_plugin_list);
extern void plugin_linked_list_free(plugin_linked_list_DEF** list);
#ifdef __cplusplus
}
#endif
#endif
