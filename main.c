#include <stdio.h>
#include <string.h>


typedef struct {
	char* Task_name;
	int priority;
	void(*func_ptr)(void);
}Task;

typedef struct {
	char type; /* D for delay , R for ready*/
	struct Task* queue; /*the queue is an array of tasks, each has a function pointer and a priority*/
}Queue;

void QueTask(Queue *, Task);

void QueTask(Queue * RQ, Task task)
{

}


void task1(void);


void task1() {
	printf("HIiii \n");
}

int main()

{
	Task A;
	A.priority = 3;
	A.func_ptr = task1;
	A.Task_name = "Task 1";

	A.func_ptr(); //runs the function

	Queue ReadyQueue;
	ReadyQueue.type = 'R';


	system("pause");
	return 0;

}
