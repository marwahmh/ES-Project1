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
	node *next_node;
}node;

typedef struct q
{
	char type; /* D for delay , R for ready*/
	node* queue_head; /*the queue is an array of tasks, each has a function pointer and a priority*/
}Queue;

void QueTask(Task);
void task1(void);



// Function to push according to priority
void QueTask(Task task)
{
	// Create new Node

	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = task;

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
		current_node->next_node= start->next_node;
		start->next_node = current_node;
	}
}



void task1() {
	printf("HIiii \n");
}

void task2() {
	printf("KKKKKK \n");
}

void task3() {
	printf("qqqqqq \n");
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
	B.priority = 3;
	B.func_ptr = task2;
	B.Task_name = "Task B";

	Task C;
	C.priority = 2;
	C.func_ptr = task3;
	C.Task_name = "Task C";



	QueTask(A);

	printf(ReadyQueue->queue_head->task.Task_name);
	ReadyQueue->queue_head->task.func_ptr();

	QueTask(B);

	printf(ReadyQueue->queue_head->task.Task_name);
	ReadyQueue->queue_head->task.func_ptr();

	QueTask(C);

	printf(ReadyQueue->queue_head->task.Task_name);
	ReadyQueue->queue_head->task.func_ptr();

	system("pause");
	return 0;

}
