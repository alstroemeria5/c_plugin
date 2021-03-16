#ifndef _PLUGIN_GRAPH_H
#define _PLUGIN_GRAPH_H
#ifndef _PLUGIN_H
#include "plugin.h"
#endif
#ifndef _MATRIX_H
#include "matrix.h"
#endif


#ifndef _STDIO_H
#include <stdio.h>
#endif


#define true 1
#define false 0
#define bool int
#define plugin_graph_debug(filedescriptor,format,...) fprintf(filedescriptor,"[filename:%s,line:%d]		"format,__FILE__,__LINE__,__VA_ARGS__);

typedef struct plugin_node_graph plugin_node_graph_DEF;
struct plugin_node_graph{
	two_d_Matrix_DEF* ptr_adjacency_matrix;
	two_d_Matrix_DEF* edge_matrix;
	plugin_linked_list_DEF* ptr_plugin_list;
	plugin_node_DEF** ptr_plugin_node_first_entry;
	
	int number_of_node;
};
#ifdef __cplusplus
extern "c" {
#endif
extern plugin_node_graph_DEF* plugin_node_graph_alloc_init();
extern void plugin_node_graph_topological_sort(plugin_node_graph_DEF* ptr_plugin_node_graph);
extern void plugin_graph_free(plugin_node_graph_DEF** ptr_plugin_node_graph);
#ifdef __cplusplus
}
#endif
#endif
