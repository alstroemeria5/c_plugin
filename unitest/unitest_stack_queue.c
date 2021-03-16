#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include "stack_queue.h"

int main(int argc,char* argv[])
{	
	
	queue_DEF* ptr_queue=queue_alloc_init();
	malloc_stats();
	for(int i=0;i<1000000;i++){
		enqueue(i,ptr_queue);
	}
	fprintf(stdout,"Successful enqueue!");
	for(int i=0;i<1002;i++){
		fprintf(stdout,"dequeue: %d\n",dequeue(ptr_queue));
	}
	fprintf(stdout,"Successful dequeue\n");
	if((ptr_queue->front==NULL)&&(ptr_queue->rear==NULL)){
		fprintf(stdout,"queue completely correct behaviour\n");
	}
	queue_free(&ptr_queue);
		fprintf(stdout,"Successful queue free!\n");
	stack_DEF* ptr_stack=stack_alloc_init();
	for(int i=0;i<1000000;i++){
		push(i,ptr_stack);
	}
	fprintf(stdout,"Successful push!");
	for(int i=0;i<100000;i++){
		fprintf(stdout,"top: %d\n",top(ptr_stack));
	}
	fprintf(stdout,"Successful top!");
	if((ptr_stack->front==NULL)&&(ptr_stack->rear==NULL)){
		fprintf(stdout,"stack completely correct behaviour\n");
	}
	
	stack_free(&ptr_stack);
		fprintf(stdout,"Successful stack free!\n");
	malloc_stats();
	return 0;
}
