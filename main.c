#include <stdio.h>
#include <string.h>

typedef struct t Task;
typedef struct n node;
typedef struct q Queue;

Queue* RQ;
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
	node** queue_head; /*the queue is an array of tasks, each has a function pointer and a priority*/
}Queue;

void QueTask(Task);
void task1(void);


void Init()
{

}

// Function to push according to priority
void QueTask(Task task)
{
	// Create new Node
	//Node* temp = newNode(d, p);

	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = task;

	node* start = *(RQ->queue_head);
	//Node* start = (*head);

	if ((*RQ->queue_head)->task.priority > task.priority) /*head has greater priority than current*/
	{
		// Insert New Node before head
		current_node->next_node = (*(RQ->queue_head));
		(*(RQ->queue_head)) = current_node;
	}
	else
	{
		while (start->next_node != NULL && start->next_node->task.priority < task.priority) /*traverse till find the  right position*/
		{
			start = start->next_node;
		}

		/*at end or middle*/
		current_node->next_node= start->next_node;
		start->next_node = current_node;
	}
}


//void QueTask(Task task) /*function that queues a task in ready queue based on priority*/
//{
//	if (RQ->type == 'R') /*the ready queue*/
//	{
//		node* current_node;
//		current_node = (node*)malloc(sizeof(node));
//
//		current_node->task = task;
//		if (RQ->queue_head == 0) /*if queue is empty*/
//		{
//			RQ->queue_head->task = task;
//			RQ->queue_head->next_node = NULL;
//		}
//		
//		else
//		{
//			node* temp = RQ->queue_head;
//			node* temp1 = RQ->queue_head+1;
//			//for (int i = 0; i < size(RQ->queue_head); i++)
//			while(temp1->next_node != NULL)
//			{
//				if (temp1->task.priority < task.priority)  /*if our priority is higher*/
//				{
//					temp->next_node = current_node;
//					current_node->next_node = temp1;
//					//RQ->queue_head[i].next_node = RQ->queue_head[i];
//				}
//
//
//
//			}
//		}
//	}
//}
//

void task1() {
	printf("HIiii \n");
}

void task2() {
	printf("KKKKKK \n");
}

void task3() {
	printf("qqqqqq \n");
}

int main()

{
	Task A;
	A.priority = 1;
	A.func_ptr = task1;
	A.Task_name = "Task 1";

	Task B;
	B.priority = 3;
	B.func_ptr = task2;
	B.Task_name = "Task 2";

	Task C;
	C.priority = 2;
	C.func_ptr = task3;
	C.Task_name = "Task 3";

	//A.func_ptr(); //runs the function

	RQ = (Queue *) malloc(sizeof(Queue));
	DelayedQueue = (Queue *)malloc(sizeof(Queue));


	RQ->type = 'R';
	DelayedQueue->type = 'D';

	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = A;
	current_node->next_node = NULL;

	RQ->queue_head = current_node;
	//(*(RQ->queue_head))->task = A;
	QueTask(B);
	//printf('\n');
	

	QueTask(C);

	printf((*(RQ->queue_head))->task.Task_name);
	(*(RQ->queue_head))->task.func_ptr();
	//printf('\n');
	/*
	node* current_node;
	current_node = (node*)malloc(sizeof(node));
	current_node->task = A;
	current_node->next_node = NULL;

	RQ->queue_head= current_node;



	printf(RQ->queue_head->task.Task_name);
	RQ->queue_head->task.func_ptr();
	printf('\n');



	printf(RQ->queue_head->task.Task_name);
	RQ->queue_head->task.func_ptr();
	*/
	system("pause");
	return 0;

}
