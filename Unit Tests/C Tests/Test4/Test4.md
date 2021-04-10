# Test 4: Testing with 4 Tasks (A, B, C, D) - Scalability Test

## Tasks Definition:
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
