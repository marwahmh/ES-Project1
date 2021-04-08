#include <stdio.h>
#include <string.h>

typedef struct t Task;
typedef struct n node;
typedef struct q Queue;

Queue* ReadyQueue;
Queue* DelayedQueue;

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
void task1(void);


Task running_task;

// Function to push according to priority
void QueTask(Task task)
{
	if (task.priority <= 8)
	{
		// Create new Node

		node* current_node;
		current_node = (node*)malloc(sizeof(node));
		current_node->task = task;
		current_node->delay = 0; /*ready task*/
		current_node->next_node = NULL;

		node* start = ReadyQueue->queue_head;
		if (ReadyQueue->queue_head == 0) /*first node*/
		{
			ReadyQueue->queue_head = current_node;
		}
		else if (ReadyQueue->queue_head->task.priority < task.priority) /*head has less priority than current*/
		{
			// Insert New Node before head
			current_node->next_node = ReadyQueue->queue_head;
			ReadyQueue->queue_head = current_node;
		}
		else
		{
			while (start->next_node != NULL && start->next_node->task.priority > task.priority) /*traverse till find the  right position*/
			{
				start = start->next_node;
			}

			/*at end or middle*/
			current_node->next_node = start->next_node;
			start->next_node = current_node;
		}
	}
	else
	{
		printf(task.Task_name);
		printf( " has priority greater than 8");
	}
}

void Dispatch()
{
	void(*func_ptr)(void);
	//Task temp_task;
	running_task = ReadyQueue->queue_head->task;

	//func_ptr = ReadyQueue->queue_head->task.func_ptr;
	if (ReadyQueue->queue_head->next_node != NULL) {
		ReadyQueue->queue_head = ReadyQueue->queue_head->next_node;
	}
	else
	{
		ReadyQueue->queue_head = 0;
	}
	running_task.func_ptr();
}

void QueDelayedTask(Task task, int delay)
{

	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = task;
	current_node->delay = delay;
	current_node->next_node = NULL;

	/*Delayed queue is sorted ascendingly*/
	node* start = DelayedQueue->queue_head;
	if (DelayedQueue->queue_head == 0) /*first node*/
	{
		DelayedQueue->queue_head = current_node;
	}
	else if (DelayedQueue->queue_head->delay > delay) /*head has greater delay than current*/
	{
		// Insert New Node before head
		current_node->next_node = DelayedQueue->queue_head;
		DelayedQueue->queue_head = current_node;
	}
	else
	{
		while (start->next_node != NULL && start->next_node->delay < delay) /*traverse till find the  right position*/
		{
			start = start->next_node;
		}

		/*at end or middle*/
		current_node->next_node = start->next_node;
		start->next_node = current_node;
	}


}

void ReRunMe(int delay)
{
	if (delay == 0)
	{
		QueTask(running_task);
	}
	else if (delay > 0) /*enqueue in DelayedQueue based on delay time*/
	{
		QueDelayedTask(running_task, delay);
	}
	else
	{
		printf("Delay is invalid !");
	}
}

void task1() {
	printf("this is task 1 :) \n");
	ReRunMe(0);
}

void task2() {
	printf("this is task 2 hellooo \n");
}

void task3() {
	printf("this is task 3 hiii \n");
}

void Init()
{
	/*allocate memory,initialize */
	ReadyQueue = (Queue *)malloc(sizeof(Queue));
	DelayedQueue = (Queue *)malloc(sizeof(Queue));

	ReadyQueue->type = 'R';
	DelayedQueue->type = 'D';

	//initialize the queue
	ReadyQueue->queue_head = 0;
}

int main()

{
	Task A;
	A.priority = 1;
	A.func_ptr = task1;
	A.Task_name = "Task A";

	Task B;
	B.priority = 2;
	B.func_ptr = task2;
	B.Task_name = "Task B";

	Task C;
	C.priority = 3;
	C.func_ptr = task3;
	C.Task_name = "Task C";

	Init();

	QueTask(A);

	//printf(ReadyQueue->queue_head->task.Task_name);
	//ReadyQueue->queue_head->task.func_ptr();

	QueTask(B);

	//printf(ReadyQueue->queue_head->task.Task_name);
	//ReadyQueue->queue_head->task.func_ptr();

	QueTask(C);

	Dispatch(); 
	Dispatch();
	Dispatch();
	Dispatch(); /*task 1 should run again*/

	//printf(ReadyQueue->queue_head->task.Task_name);
	//ReadyQueue->queue_head->task.func_ptr();

	system("pause");
	return 0;

}
