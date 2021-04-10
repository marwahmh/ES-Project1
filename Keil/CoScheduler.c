#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CoScheduler.h>
#include <stm32l4xx_it.h>


#define TRUE 1

//typedef struct t Task;
//typedef struct n node;
//typedef struct q Queue;


int count = 0;



Queue* ReadyQueue;
Queue* DelayedQueue;

//void QueTask(Task);
//void task1(void);
//void DecrementDelayed();
//void setTimeout(int );


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
	//Task temp_task;
	if (ReadyQueue->queue_head != 0) {
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
	else
	{
		printf("IDLE");
	}
}

void QueDelayedTask(Task task, int delay)
{

	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = task;
	current_node->delay = delay;
	current_node->next_node = NULL;

	/*Delayed queue is sorted ascendingly according to delay time*/
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

	//DecrementDelayed();

}

int tickPassed =0;

int deduct_amount=0;

void DecrementDelayed()
{
	//tickPassed=0;

//	node* start = DelayedQueue->queue_head;

//	 /*if 50 msec passed*/
//	//setTimeout(50);
//	//while(count<=3)  /*to simulate the tick period "3 counts = 1 tick" */
//	//{
//	if(tickPassed>=50){
//		//tickPassed=0;
//		deduct_amount=tickPassed/50;
//		tickPassed %= 50;;
//		int c=0;
//		while (start != NULL) /*decrement delay of all tasks in the delayed queue*/
//		{
//			while(c<deduct_amount){
//			start->delay -= 1; /*decrement the delay*/
//			c++;
//			}
//			if (start->delay <= 0) /*if the task expires*/
//			{
//				QueTask(start->task);
//				DelayedQueue->queue_head = DelayedQueue->queue_head->next_node;
//			}
//		//	if (start->next_node != NULL) {
//				start = start->next_node; /*move to next task in the queue*/
//		//	}
//		}
//	}
//	//}

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

//void task1() {
//	printf("this is task 1 :) \n");
//	ReRunMe(3);
//}

//void task2() {
//	printf("this is task 2 hellooo \n");
//	ReRunMe(5);

//}

//void task3() {
//	printf("this is task 3 hiii \n");
//}

void Init()
{
	/*allocate memory,initialize */
	ReadyQueue = (Queue *)malloc(sizeof(Queue));
	DelayedQueue = (Queue *)malloc(sizeof(Queue));

	ReadyQueue->type = 'R';
	DelayedQueue->type = 'D';

	//initialize the queue
	ReadyQueue->queue_head = 0;
	DelayedQueue->queue_head = 0;

}

