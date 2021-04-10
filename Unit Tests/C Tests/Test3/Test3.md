# Test 3:Attempting to input an invalid priority number

We're trying here to give TaskA an invalid priority number, to test the program since the schedueler supports 8 priority levels.  

## Tasks Definition:
void task1() {
    printf("Task A \n");
    ReRunMe(3);
}

void task2() {
    printf("Task B \n");
    ReRunMe(5);
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
    A.priority = 10;
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
