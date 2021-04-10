#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1

typedef struct t Task;
typedef struct n node;
typedef struct q Queue;

Queue* ReadyQueue;
Queue* DelayedQueue;

int count = 0;


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
void DecrementDelayed();
void setTimeout(int );


Task running_task;

//
//void setTimeout(int milliseconds)
//{
//    /*If milliseconds is less or equal to 0*/
//    /*will be simple return from function without throw error*/
//    if (milliseconds <= 0) {
//        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
//        return;
//    }
//
//    // a current time of milliseconds
//    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
//
//    // needed count milliseconds of return from this timeout
//    int end = milliseconds_since + milliseconds;
//
//    // wait while until needed time comes
//    do {
//        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
//    } while (milliseconds_since <= end);
//}
//

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
        printf( " has priority greater than 8. Invalid!! \n");
        exit(0);
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
        printf("IDLE \n");
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

void DecrementDelayed()
{
    node* start = DelayedQueue->queue_head;

     /*if 50 msec passed*/
    //setTimeout(50);
    while(count<=3)  /*to simulate the tick period "3 counts = 1 tick" */
    {
        while (start != NULL && count==3) /*decrement delay of all tasks in the delayed queue*/
        {
            start->delay -= 1; /*decrement the delay*/
            if (start->delay == 0) /*if the task expires*/
            {
                QueTask(start->task);
                DelayedQueue->queue_head = DelayedQueue->queue_head->next_node;
            }
        //    if (start->next_node != NULL) {
                start = start->next_node; /*move to next task in the queue*/
        //    }
        }
        count++;
    }
    count = 0;

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
    printf("Task A \n");
}

void task2() {
    printf("Task B \n");
    ReRunMe(5);
}

void task3() {
    printf("Task C \n");
    ReRunMe(6);
}

void task4() {
    printf("Task D \n");
    ReRunMe(2);
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

int main()

{
    Task A;
    A.priority = 4;
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

    Task D;
    D.priority = 1;
    D.func_ptr = task4;
    D.Task_name = "Task C";
    
    Init();

    QueTask(A);

    //printf(ReadyQueue->queue_head->task.Task_name);
    //ReadyQueue->queue_head->task.func_ptr();

    QueTask(B);

    //printf(ReadyQueue->queue_head->task.Task_name);
    //ReadyQueue->queue_head->task.func_ptr();

    QueTask(C);
    QueTask(D);

    while (TRUE) {
        Dispatch();
        DecrementDelayed();
    }

    //Dispatch(); /*task 1 should run again*/

    //printf(ReadyQueue->queue_head->task.Task_name);
    //ReadyQueue->queue_head->task.func_ptr();

    //system("pause");
    return 0;
}
