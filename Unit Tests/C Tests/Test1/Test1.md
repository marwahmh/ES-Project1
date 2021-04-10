# Test 1: Using ReRunMe(0) 

Task A here is the task with the highest priority, and will use ReRunMe with 0 sleeping time. This will lead to the blocking of tasks B and C, since A will always have the priority to execute.

## Tasks Definition:
void task1() {
    printf("Task A: I am the boss now \n");
    ReRunMe(0);
}

void task2() {
    printf("Task B \n");
}

void task3() {
    printf("Task C \n");
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
    A.priority = 3;
    A.func_ptr = task1;
    A.Task_name = "Task A";

    Task B;
    B.priority = 2;
    B.func_ptr = task2;
    B.Task_name = "Task B";

    Task C;
    C.priority = 1;
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
