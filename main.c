/*
 * main.c
 *
 *  Created on: Feb 27, 2021
 *      Author: eric
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "plugin.h"
#include "plugin_rb.h"
#include "matrix.h"
#include "plugin_graph.h"
#include "graph.h"
#include "cstring.h"
#include "stack_queue.h"
char* lib[5]={"gcd","add","substract","multiply","modular"};
int order[5]={2,3,1,0,4};
/*char* lib[4]={"gcd","add","substract","multiply"};
int order[4]={2,3,1,0};*/

int main(int argc,char* argv[])
{
	
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_DEF",sizeof(plugin_DEF));
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_node_DEF",sizeof(plugin_node_DEF));
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_linked_list_DEF",sizeof(plugin_linked_list_DEF));
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_node_graph_DEF",sizeof(plugin_node_graph_DEF));
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_rb_node_DEF",sizeof(plugin_rb_node_DEF));
	plugin_debug(stdout,"sizeof(%s):%ld\n","plugin_rb_tree_DEF",sizeof(plugin_rb_tree_DEF));
	
	int a=12745;
	int b=13680;
	plugin_linked_list_DEF* lib_list=plugin_linked_list_alloc_init();
	malloc_stats();
#ifdef rb
	plugin_rb_tree_DEF* ptr_rb_tree=plugin_rb_tree_alloc_init();
#endif
	for(int i=0;i<5;i++){
		plugin_node_alloc_init_insert_to_list("/home/eric/Code/plugin/lib/",lib[i],order[i],lib_list);
	}
	for(plugin_node_DEF* temp=lib_list->head;temp!=NULL;temp=temp->next){	
		
		if(temp->plugin.validity==enum_dll_unable_to_open){
			continue;
		}
		if(temp->plugin.validity==enum_dll_unable_to_find_symbol){
			continue;
		}
		else{
			plugin_debug(stdout,"function %s result in %d\n",temp->plugin.name,temp->plugin.func(a,b));
		}
#ifdef rb
		plugin_rb_tree_node_insert(ptr_rb_tree,&temp->plugin);
#endif
	}
	plugin_rb_tree_inorder_traversal(ptr_rb_tree);
	plugin_rb_tree_replace_plugin_rb_linked_list_inorder(ptr_rb_tree,lib_list);
	plugin_rb_tree_free(&ptr_rb_tree);
	//plugin_linked_list_free(&lib_list);
	/*plugin_debug(stderr,"mess with free pointer:%p and its data structure:%s\n",lib_list,lib_list->head->plugin.name);*/
#ifdef rb
#if 0
	plugin_rb_tree_inorder_traversal(ptr_rb_tree);
	plugin_rb_tree_replace_plugin_rb_linked_list_inorder(ptr_rb_tree,lib_list);
	for(plugin_node_DEF* temp=lib_list->head;temp!=NULL;temp=temp->next){	
		
		if(temp->plugin.validity==enum_dll_unable_to_open){
			continue;
		}
		if(temp->plugin.validity==enum_dll_unable_to_find_symbol){
			continue;
		}
		else{
			plugin_debug(stdout,"function %s result in %d\n",temp->plugin.name,temp->plugin.func(a,b));
		}

	}
	plugin_rb_tree_free(ptr_rb_tree);
	plugin_debug(stderr,"number of element in list:%d\n",lib_list->number_of_node);
#endif
#endif
#if 0
	two_d_Matrix_DEF* two_d_array_one=two_d_Matrix_alloc_init(4,4);
	two_d_Matrix_DEF* two_d_array_two=two_d_Matrix_alloc_init(3,7);
	two_d_Matrix_DEF* two_d_Matrix_temp=two_d_Matrix_alloc_init(4,4);
	int temp_matrix[4][4]={{0,1,1,0},{0,0,0,1},{0,0,0,1},{0,0,0,0}};
	two_dimension_matrix_free(two_d_Matrix_temp->ptr_to_matrix,two_d_Matrix_temp->row);
	two_d_Matrix_temp->ptr_to_matrix=(int**)temp_matrix;
	two_d_Matrix_cpy(two_d_array_one,two_d_Matrix_temp);
	free(two_d_Matrix_temp);

	
	two_d_Matrix_DEF* two_d_araay_answer=two_d_Matrix_multiply(two_d_array_one,two_d_array_two);
	matrix_error();
	two_d_Matrix_free(two_d_array_one);
	two_d_Matrix_free(two_d_array_two);
	two_d_Matrix_free(two_d_araay_answer);
#endif

	printf("==========following is graph test==========\n");
	int temp_matrix[5][5]={{0,1,1,1,0},{0,0,1,1,0},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,0,0}};
	//int temp_matrix[4][4]={{0,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}};
	two_d_Matrix_DEF* target_matrix=two_d_Matrix_alloc_init(5,5);
	two_d_Matrix_cpy_c_array(target_matrix,target_matrix->column,temp_matrix);
	two_d_Matrix_print(target_matrix);
	plugin_node_graph_DEF* target_graph=plugin_node_graph_alloc_init();
	graph_DEF* ptr_graph=graph_alloc_init(target_matrix);
	graph_print(ptr_graph);
	graph_dfs_print(ptr_graph);
	//graph_bfs_print(ptr_graph);
	int* indegree=graph_indegree(ptr_graph);
	for(int i=0;i<ptr_graph->num_vertex;i++){
		fprintf(stdout,"indegree of %d is %d\n",i,indegree[i]);
	}
	free(indegree);
	int* topological_sort=graph_topological_sort(ptr_graph);
	for(int i=0;i<ptr_graph->num_vertex;i++){
		fprintf(stdout,"[V%d] ",topological_sort[i]);
	}
	fprintf(stdout,"\n");
	free(topological_sort);
	graph_free(&ptr_graph);
	target_graph->number_of_node=target_matrix->row;
	target_graph->ptr_adjacency_matrix=target_matrix;
	target_graph->edge_matrix=adjacency_mat_to_edge_alloc_init(target_matrix);
	target_graph->ptr_plugin_list=lib_list;
	target_graph->ptr_plugin_node_first_entry=NULL;
	two_d_Matrix_DEF* temp_adjacency=edge_to_adjacency_mat_alloc_init(target_graph->edge_matrix);
	plugin_debug(stdout,"two matrix %s and %s are %s\n",TO_STRING(temp_adjacency),TO_STRING(target_graph->ptr_adjacency_matrix),two_d_Matrix_comparison(temp_adjacency,target_graph->ptr_adjacency_matrix)? "equivalent":"different");
	two_d_Matrix_print(target_graph->edge_matrix);
	two_d_Matrix_print(temp_adjacency);
	plugin_node_graph_topological_sort(target_graph);
	plugin_graph_free(&target_graph);
	two_d_Matrix_free(&temp_adjacency);
	queue_DEF* ptr_queue=queue_alloc_init();
	enqueue(1,ptr_queue);
	enqueue(2,ptr_queue);
	printf("queue is %s\n",is_queue_empty(ptr_queue)?"empty":"filled");
	printf("dequeue: %d\n",dequeue(ptr_queue));
	printf("dequeue: %d\n",dequeue(ptr_queue));
	printf("%p\n",ptr_queue->front);
	printf("%p\n",ptr_queue->rear);
	queue_free(&ptr_queue);
	stack_DEF* ptr_stack=stack_alloc_init();
	push(1,ptr_stack);
	push(2,ptr_stack);
	printf("top is %d\n",top(ptr_stack));
	printf("top is %d\n",top(ptr_stack));
	stack_free(&ptr_stack);
	//malloc_stats();
	//malloc_info(0, stdout);
}

