
#ifndef _STACK_QUEUE_H

#define _STACK_QUEUE_H
#define queue_empty -1
#define stack_empty -1
#ifndef __BOOLEAN__
#define __BOOLEAN__
#define bool int
#define true 1
#define false 0
#endif 


typedef struct node node_DEF;
typedef struct queue_stack queue_DEF;
typedef struct queue_stack stack_DEF;
struct node{
		int data;
		node_DEF* next;
		node_DEF* previous;
};
struct queue_stack{
		node_DEF* front;
		node_DEF* rear;
};
#ifdef __cplusplus
extern "c" {
#endif
extern queue_DEF* queue_alloc_init();
extern void queue_free(queue_DEF** ptr_queue);

extern void enqueue(int data,queue_DEF* ptr_queue);

extern int dequeue(queue_DEF* ptr_queue);
extern bool is_queue_empty(queue_DEF* ptr_queue);
extern stack_DEF* stack_alloc_init();
extern void stack_free(queue_DEF** ptr_stack);

extern void push(int data,queue_DEF* ptr_stack);
extern bool is_stack_empty(stack_DEF* ptr_stack);

extern node_DEF* node_alloc_init(int data,node_DEF* next,node_DEF* previous);
extern void node_free(node_DEF** ptr_node);
extern int top(stack_DEF* ptr_stack);
#ifdef _cplusplus
}
#endif
#endif
