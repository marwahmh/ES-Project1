#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CoScheduler.h>
#include <stm32l4xx_it.h>


#define TRUE 1


int count = 0;


Queue* ReadyQueue;
Queue* DelayedQueue;


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

}
node* temp3;
void Dispatch()
{
	if (ReadyQueue->queue_head != 0) {
		running_task = ReadyQueue->queue_head->task;

		if (ReadyQueue->queue_head->next_node != NULL) {
			temp3=ReadyQueue->queue_head;
			ReadyQueue->queue_head = ReadyQueue->queue_head->next_node;
			free(temp3);
		}
		else
		{
			free(ReadyQueue->queue_head);
			ReadyQueue->queue_head = 0;
			
		}
		running_task.func_ptr();
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


}

int tickPassed =0;

int deduct_amount=0;

void ReRunMe(int delay)
{
	if (delay <= 0)
	{
		QueTask(running_task);
	}
	else if (delay > 0) /*enqueue in DelayedQueue based on delay time*/
	{
		QueDelayedTask(running_task, delay);
	}

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
	DelayedQueue->queue_head = 0;

}

