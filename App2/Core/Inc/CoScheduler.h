
#ifndef __COSCHEDULER_H
#define __COSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct t Task;
	typedef struct n node;
	typedef struct q Queue;
	
	typedef struct t
{
	char* Task_name;
	int priority;
	void(*func_ptr)(void); /*pointer to the function (the task) */
}Task;

typedef struct n
{
	Task task;
	int delay;
	node *next_node;
}node;

typedef struct q
{
	char type; /* D for delay , R for ready*/
	node* queue_head; /*the queue is an array of tasks, each has a function pointer and a priority*/
}Queue;


	void QueTask(Task);
	void Dispatch();
	void QueDelayedTask(Task , int);
	void DecrementDelayed();
	void ReRunMe(int);
	void Init();


#ifdef __cplusplus
}
#endif

#endif 
