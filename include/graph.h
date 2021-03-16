#ifndef _GRAPH_H
#define _GRAPH_H
#ifndef _MATRIX_H
#include "matrix.h"
#endif
#define vert_in_edge 2
#define graph_debug(filedescriptor,format,...) fprintf(filedescriptor,"[filename:%s,line:%d]		"format,__FILE__,__LINE__,__VA_ARGS__);
#define visited 1
#define queue_empty -1
#ifndef __BOOLEAN__
#define __BOOLEAN__
#define bool int
#define true 1
#define false 0
#endif 

typedef struct graph graph_DEF;
typedef struct vertex vertex_DEF;
typedef struct node node_DEF;
typedef struct queue_stack queue_DEF;
typedef struct queue_stack stack_DEF;
struct graph{
	int num_vertex;
	vertex_DEF* array;
};
struct vertex{
		int data;
		vertex_DEF* next;		
};
extern two_d_Matrix_DEF* adjacency_mat_to_edge_alloc_init(two_d_Matrix_DEF* two_d_mat);
extern two_d_Matrix_DEF* edge_to_adjacency_mat_alloc_init(two_d_Matrix_DEF* edge);
extern void two_d_Matrix_out_deg_array(two_d_Matrix_DEF* ptr_two_d_Matrix,int* out_deg_array);
extern two_d_Matrix_DEF* two_d_Matrix_A_Atranspose(two_d_Matrix_DEF* ptr_two_d_Matrix);
extern graph_DEF* graph_alloc_init(two_d_Matrix_DEF* adjacency_mat);
extern void graph_print(graph_DEF* ptr_graph);
extern void graph_free(graph_DEF** ptr_graph);
extern int* graph_topological_sort(graph_DEF* ptr_graph);

extern int* graph_indegree(graph_DEF* ptr_graph);
extern void __graph_indegree(int vertex,bool* visit,vertex_DEF* array,int* indegree);
extern void graph_dfs(graph_DEF* ptr_graph);
extern void graph_dfs_print(graph_DEF* ptr_graph);
extern void graph_bfs_print(graph_DEF* ptr_graph);
extern void __graph_bfs_print(int vertex,int* visit,vertex_DEF* array);
extern void __graph_dfs_print(int vertex,int* visit,vertex_DEF* array);
#endif 
