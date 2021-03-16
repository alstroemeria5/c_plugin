#include <assert.h>
#include <stdlib.h>
#include "dll.h"
#include "stack_queue.h"
DLL_PUBLIC queue_DEF* queue_alloc_init()
{
	queue_DEF* ptr_queue=malloc(sizeof(queue_DEF));
	ptr_queue->front=NULL;
	ptr_queue->rear=NULL;
	return ptr_queue;
}
DLL_PUBLIC void queue_free(queue_DEF** ptr_queue)
{
	assert((ptr_queue!=NULL)&&((*ptr_queue)!=NULL));
	node_DEF* ptr_front=(*ptr_queue)->front;
	node_DEF* ptr_temp;
	while(ptr_front!=NULL){
		ptr_temp=ptr_front;
		ptr_front=ptr_front->next;
		node_free(&ptr_temp);
	}
	free(*ptr_queue);
	*ptr_queue=NULL;
}
DLL_PUBLIC void enqueue(int data,queue_DEF* ptr_queue)
{
	assert(ptr_queue!=NULL);
	node_DEF** front=&(ptr_queue->front);
	node_DEF** rear=&(ptr_queue->rear);
	node_DEF* new_node=node_alloc_init(data,NULL,NULL);
	if((*rear)==NULL){
		*front=new_node;
	}
	else{
		(*rear)->next=new_node;
		new_node->previous=(*rear);
	}
	*rear=new_node;
	return;
}
DLL_PUBLIC int dequeue(queue_DEF* ptr_queue)
{
	assert(ptr_queue!=NULL);
	int temp;
	node_DEF* ptr_temp;
	node_DEF** front=&(ptr_queue->front);
	node_DEF** rear=&(ptr_queue->rear);
	if(*front==NULL){
		return queue_empty;
	}
	if((*front==*rear)){
		temp=(*front)->data;
		node_free(front);
		*front=NULL;
		*rear=NULL;
		return temp;
	}
	ptr_temp=*front;
	*front=(*front)->next;
	(*front)->previous=NULL;
	temp=ptr_temp->data;
	node_free(&ptr_temp);
	return temp;
}
DLL_PUBLIC bool is_queue_empty(queue_DEF* ptr_queue)
{
	assert(ptr_queue!=NULL);
	if(ptr_queue->front==NULL){
		return true; 
	}
	else{
		return false;
	}
}
DLL_PUBLIC stack_DEF* stack_alloc_init()
{
	stack_DEF* ptr_stack=malloc(sizeof(queue_DEF));
	ptr_stack->front=NULL;
	ptr_stack->rear=NULL;
	return ptr_stack;
}
DLL_PUBLIC void stack_free(queue_DEF** ptr_stack)
{
	assert((ptr_stack!=NULL)&&((*ptr_stack)!=NULL));
	node_DEF* ptr_front=(*ptr_stack)->front;
	node_DEF* ptr_temp;
	while(ptr_front!=NULL){
		ptr_temp=ptr_front;
		ptr_front=ptr_front->next;
		node_free(&ptr_temp);
	}
	free(*ptr_stack);
	*ptr_stack=NULL;
}


DLL_PUBLIC void push(int data,queue_DEF* ptr_stack)
{
	assert(ptr_stack!=NULL);
	node_DEF** front=&(ptr_stack->front);
	node_DEF** rear=&(ptr_stack->rear);
	node_DEF* new_node=node_alloc_init(data,NULL,NULL);
	if((*front)==NULL){
		*front=new_node;
	}
	else{
		(*rear)->next=new_node;
		new_node->previous=(*rear);
	}
	*rear=new_node;
	return;
}
DLL_PUBLIC int top(stack_DEF* ptr_stack)
{
	assert(ptr_stack!=NULL);
	int temp;
	node_DEF* ptr_temp;
	node_DEF** front=&(ptr_stack->front);
	node_DEF** rear=&(ptr_stack->rear);
	if(*front==NULL){
		return stack_empty;
	}
	if((*front==*rear)&&(*front!=NULL)){
		temp=(*rear)->data;
		node_free(rear);
		*front=NULL;
		*rear=NULL;
		return temp;
	}
	ptr_temp=*rear;
	*rear=(*rear)->previous;
	(*rear)->next=NULL;
	temp=ptr_temp->data;
	node_free(&ptr_temp);
	return temp;
}
DLL_PUBLIC bool is_stack_empty(stack_DEF* ptr_stack)
{
	assert(ptr_stack!=NULL);
	if(ptr_stack->rear==NULL){
		return true; 
	}
	else{
		return false;
	}
}
DLL_PUBLIC node_DEF* node_alloc_init(int data,node_DEF* next,node_DEF* previous)
{
	node_DEF* ptr_node=malloc(sizeof(node_DEF));
	ptr_node->data=data;
	ptr_node->next=next;
	ptr_node->previous;
	return ptr_node;
}
DLL_PUBLIC void node_free(node_DEF** ptr_node)
{
	assert((ptr_node!=NULL)||((*ptr_node)!=NULL));
	free(*ptr_node);
	*ptr_node=NULL;
	return;
}

