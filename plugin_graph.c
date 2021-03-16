#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "plugin_graph.h"
#include "dll.h"
#include "graph.h"
DLL_PUBLIC plugin_node_graph_DEF* plugin_node_graph_alloc_init()
{
	plugin_node_graph_DEF* ptr_plugin_node_graph=malloc(sizeof(plugin_node_graph_DEF));
#ifdef DEBUG
	plugin_graph_debug(stdout,"plugin_node_graph being allocated at address %p\n",ptr_plugin_node_graph);
#endif
	return ptr_plugin_node_graph;
}

DLL_PUBLIC void plugin_node_graph_topological_sort(plugin_node_graph_DEF* ptr_plugin_node_graph)
{	
	graph_DEF* ptr_graph=graph_alloc_init(ptr_plugin_node_graph->ptr_adjacency_matrix);
	int number_of_node=ptr_graph->num_vertex;
	int* queue=graph_topological_sort(ptr_graph);
#ifdef DEBUG
	for(int i=0;i<number_of_node;i++){
		plugin_graph_debug(stdout,"node number:%d\n",queue[i]);
	}
#endif
	ptr_plugin_node_graph->ptr_plugin_node_first_entry=malloc(sizeof(plugin_node_DEF*)*number_of_node);
	for(int i=0;i<number_of_node;i++){
		int count=0;
		plugin_node_DEF* ptr_plugin_node=ptr_plugin_node_graph->ptr_plugin_list->head;
		while(count<queue[i]){
			ptr_plugin_node=ptr_plugin_node->next;
			count++;
		}
		ptr_plugin_node_graph->ptr_plugin_node_first_entry[i]=ptr_plugin_node;
	}
	
#ifdef DEBUG
	for(int i=0;i<number_of_node;i++){
		plugin_graph_debug(stdout,"name:%s\n",ptr_plugin_node_graph->ptr_plugin_node_first_entry[i]->plugin.name);
	}
	plugin_linked_list_nullify(ptr_plugin_node_graph->ptr_plugin_list);
	for(int i=0;i<number_of_node;i++){
		plugin_node_insert_to_list(ptr_plugin_node_graph->ptr_plugin_node_first_entry[i],ptr_plugin_node_graph->ptr_plugin_list);
	}
#endif
	graph_free(&ptr_graph);
	free(queue);
}
DLL_PUBLIC void plugin_graph_free(plugin_node_graph_DEF** ptr_plugin_node_graph)
{
	assert((ptr_plugin_node_graph!=NULL)&&(*ptr_plugin_node_graph!=NULL));
	if((*ptr_plugin_node_graph)->ptr_adjacency_matrix){
		two_d_Matrix_free(&((*ptr_plugin_node_graph)->ptr_adjacency_matrix));
	}
	if((*ptr_plugin_node_graph)->ptr_plugin_list){
		plugin_linked_list_free(&((*ptr_plugin_node_graph)->ptr_plugin_list));
	}
	if((*ptr_plugin_node_graph)->ptr_plugin_node_first_entry){
		free((*ptr_plugin_node_graph)->ptr_plugin_node_first_entry);
	}
	if((*ptr_plugin_node_graph)->edge_matrix){
		two_d_Matrix_free(&((*ptr_plugin_node_graph)->edge_matrix));
	}
#ifdef DEBUG
	plugin_graph_debug(stdout,"plugin_node_graph being freed at address %p\n",*ptr_plugin_node_graph);
#endif
	free(*ptr_plugin_node_graph);
	*ptr_plugin_node_graph=NULL;
	return;
}