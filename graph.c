#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "stack_queue.h"
#include "matrix.h"
#include "graph.h"
#include "dll.h"
DLL_PUBLIC two_d_Matrix_DEF* adjacency_mat_to_edge_alloc_init(two_d_Matrix_DEF* two_d_mat)
{
	int row=two_d_mat->row;
	int column=two_d_mat->column;
	int counter=0;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(i==j){
				continue;
			}
			if(two_d_mat->ptr_to_matrix[i][j]==1){
				counter++;
			}
		}
	}
	two_d_Matrix_DEF* two_d_edge=two_d_Matrix_alloc_init(counter,vert_in_edge);
	counter=0;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(i==j){
				continue;
			}
			if(two_d_mat->ptr_to_matrix[i][j]==1){
				two_d_Matrix_set_number(two_d_edge,counter,0,i);
				two_d_Matrix_set_number(two_d_edge,counter,1,j);
				counter++;
			}
		}
	}
	return two_d_edge;
}
DLL_PUBLIC two_d_Matrix_DEF* edge_to_adjacency_mat_alloc_init(two_d_Matrix_DEF* edge)
{
	int first=INT_MIN;
	int second=INT_MIN;
	int row=edge->row;
	int column=edge->column;
	int max=INT_MIN;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			max=(max<edge->ptr_to_matrix[i][j])? edge->ptr_to_matrix[i][j]:max; 
		}
	}
	two_d_Matrix_DEF* two_d_adjacency=two_d_Matrix_alloc_init(max+1,max+1);
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(j==0){
				first=edge->ptr_to_matrix[i][j];
			}
			if(j==1){
				second=edge->ptr_to_matrix[i][j];
				two_d_Matrix_set_number(two_d_adjacency,first,second,1);
			}
		}
	}
	return two_d_adjacency;
}
DLL_PUBLIC void two_d_Matrix_out_deg_array(two_d_Matrix_DEF* ptr_two_d_Matrix,int* out_deg_array)
{
	int column=ptr_two_d_Matrix->column;
	int row=ptr_two_d_Matrix->row;
	for(int i=0;i<row;i++){
		int temp=0;
		for(int j=0;j<column;j++){
			temp+=ptr_two_d_Matrix->ptr_to_matrix[i][j];
		}
		out_deg_array[i]=temp;
	}
	return;
}
DLL_PUBLIC two_d_Matrix_DEF* two_d_Matrix_A_Atranspose(two_d_Matrix_DEF* ptr_two_d_Matrix)
{
	two_d_Matrix_DEF* matrix_transpose=two_d_Matrix_transpose(ptr_two_d_Matrix);
	two_d_Matrix_DEF* matrix_multiplication=two_d_Matrix_multiply(ptr_two_d_Matrix,matrix_transpose);
	two_d_Matrix_free(&matrix_transpose);
	return matrix_multiplication;
	
}

DLL_PUBLIC graph_DEF* graph_alloc_init(two_d_Matrix_DEF* adjacency_mat)
{
	assert(adjacency_mat!=NULL);
	if(adjacency_mat->column!=adjacency_mat->column){
#ifdef DEBUG
	graph_debug(stderr,"Provided adjacency matrix is not dimensionally corresponding%s.\n","")
#endif
		return NULL;
	}
	int num_vertex=adjacency_mat->row;
	graph_DEF* ptr_graph=malloc(sizeof(graph_DEF));
	ptr_graph->num_vertex=adjacency_mat->row;
	ptr_graph->array=malloc(sizeof(vertex_DEF)*num_vertex);
	for(int i=0;i<num_vertex;i++){
		ptr_graph->array[i].data=i;
		ptr_graph->array[i].next=NULL;
	}
	for(int i=0;i<num_vertex;i++){
		for(int j=0;j<num_vertex;j++){
			if(i==j){
				continue;
			}
			if(adjacency_mat->ptr_to_matrix[i][j]==1){
				vertex_DEF* new_node=malloc(sizeof(vertex_DEF));
				new_node->data=j;
				new_node->next=NULL;
				vertex_DEF* ptr_temp=&ptr_graph->array[i];
				while(ptr_temp->next!=NULL){
					ptr_temp=ptr_temp->next;
				}
				ptr_temp->next=new_node;
			}
		}
	}
	return ptr_graph;
}
DLL_PUBLIC void graph_print(graph_DEF* ptr_graph)
{	
	vertex_DEF* ptr_temp;
	int num_vertex=ptr_graph->num_vertex;
	vertex_DEF *array=ptr_graph->array;
	for(int i=0;i<num_vertex;i++){
		ptr_temp=array[i].next;
		if(ptr_temp!=NULL){
			fprintf(stdout,"Vertex:%d =>",array[i].data);
			while(ptr_temp!=NULL){
				
				fprintf(stdout,"V%d ",ptr_temp->data);
				ptr_temp=ptr_temp->next;
			}
			fprintf(stdout,"\n");
		}
	}
}

DLL_PUBLIC void graph_free(graph_DEF** ptr_graph)
{
	int num_vertex=(*ptr_graph)->num_vertex;
	for(int i=0;i<num_vertex;i++){
		vertex_DEF* ptr_vertex=&((*ptr_graph)->array[i]);
		vertex_DEF* ptr_temp;
		vertex_DEF* ptr_head=ptr_vertex->next;
		while(ptr_head!=NULL){
			ptr_temp=ptr_head;
			ptr_head=ptr_head->next;
			free(ptr_temp);		
		}
	}
	free((*ptr_graph)->array);
	free(*ptr_graph);
	*ptr_graph=NULL;
	return;
}
DLL_PUBLIC int* graph_topological_sort(graph_DEF* ptr_graph)
{
	int	num_vertex=ptr_graph->num_vertex;
	int* indegree=graph_indegree(ptr_graph);
	queue_DEF* topoqueue=queue_alloc_init();
	int vertex;
	int* topological_sort=malloc(sizeof(int)*num_vertex);
	vertex_DEF* array=ptr_graph->array;
	vertex_DEF* ptr_vertex;
	for(int i=0;i<num_vertex;i++){
		if(indegree[i]==0)
		enqueue(i,topoqueue);
	}
	int counter=0;
	while(!is_queue_empty(topoqueue)){
		vertex=dequeue(topoqueue);
		topological_sort[counter++]=vertex;
		ptr_vertex=array[vertex].next;
		while(ptr_vertex!=NULL){
			vertex=ptr_vertex->data;
			indegree[vertex]--;
			if(indegree[vertex]==0){
				enqueue(vertex,topoqueue);
			}
			ptr_vertex=ptr_vertex->next;
		}
	}
	for(int i=0;i<num_vertex;i++){
		if(indegree[i]!=0){
			goto cyclic_operation;
		}
	}
	queue_free(&topoqueue);
	free(indegree);
		
	return topological_sort;
cyclic_operation:
	queue_free(&topoqueue);
	free(indegree);
	free(topological_sort);
	return NULL;
}
int* graph_indegree(graph_DEF* ptr_graph)
{
	int num_vertex=ptr_graph->num_vertex;
	bool *visit=calloc(num_vertex,sizeof(int));
	int* indegree=calloc(num_vertex,sizeof(int));
	vertex_DEF* array=ptr_graph->array;
	for(int i=0;i<num_vertex;i++){
		if(visit[i]!=visited){
			__graph_indegree(i,visit,array,indegree);
		}
	}
	free(visit);
	return indegree;
}
void __graph_indegree(int vertex,bool* visit,vertex_DEF* array,int* indegree)
{	
	visit[vertex]=visited;
	vertex_DEF* ptr_vertex=array[vertex].next;
	while(ptr_vertex!=NULL){
		indegree[ptr_vertex->data]++;
		if(visit[ptr_vertex->data]!=visited){
			
			__graph_indegree(ptr_vertex->data,visit,array,indegree);
		}
		ptr_vertex=ptr_vertex->next;
	}
}
DLL_PUBLIC void graph_dfs_print(graph_DEF* ptr_graph)
{
	int num_vertex=ptr_graph->num_vertex;
	bool *visit=calloc(num_vertex,sizeof(int));
	vertex_DEF* array=ptr_graph->array;
	fprintf(stdout,"Start graph depth first search:\n");
	for(int i=0;i<num_vertex;i++){
		if(visit[i]!=visited){
			__graph_dfs_print(i,visit,array);
		}
	}
	fprintf(stdout,"\n");
	fprintf(stdout,"end of graph depth first search\n");
	free(visit);
	return;
}
DLL_LOCAL void __graph_dfs_print(int vertex,bool* visit,vertex_DEF* array)
{
	visit[vertex]=visited;
	fprintf(stdout,"[V%d] ",vertex);
	vertex_DEF* ptr_vertex=array[vertex].next;
	while(ptr_vertex!=NULL){
		if(visit[ptr_vertex->data]!=visited){
			__graph_dfs_print(ptr_vertex->data,visit,array);
		}
		ptr_vertex=ptr_vertex->next;
	}
}
DLL_PUBLIC void graph_bfs_print(graph_DEF* ptr_graph)
{
	int num_vertex=ptr_graph->num_vertex;
	bool *visit=calloc(num_vertex,sizeof(int));
	vertex_DEF* array=ptr_graph->array;
	fprintf(stdout,"Start graph breath first search:\n");
	__graph_bfs_print(2,visit,array);
	fprintf(stdout,"\n");
	free(visit);
	return;	
}
DLL_LOCAL void __graph_bfs_print(int vertex,bool* visit,vertex_DEF* array)
{
	queue_DEF* ptr_queue=queue_alloc_init();
	vertex_DEF* ptr_vertex=NULL;
	enqueue(vertex,ptr_queue);
	visit[vertex]=visited;
	fprintf(stdout,"[V%d] ",vertex);
	while(!is_queue_empty(ptr_queue)){
		vertex=dequeue(ptr_queue);
		ptr_vertex=array[vertex].next;
		while(ptr_vertex!=NULL){
			if(visit[ptr_vertex->data]!=visited){
				enqueue(ptr_vertex->data,ptr_queue);
				visit[ptr_vertex->data]=visited;
				fprintf(stdout,"[V%d] ",ptr_vertex->data);
			}
			ptr_vertex=ptr_vertex->next;
		}
	}
	queue_free(&ptr_queue);
	return;
}

