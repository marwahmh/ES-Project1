# Embedded Systems - Project1: Cooperative Scheduler
This project is done for the Embedded Systems Course in the American University in Cairo Spring 2021. 
Instructor: Dr. Mohamed Shalan 
Done By: Dareen Hussein (ID: 900170917), Marwa Sulaiman (ID: 900172284)

# The Cooperative Scheduler Logic:
There is a struct named "Task" which contains the task pointer, priority and task name. The scheduler has 2 Tasks queues; the readyQueue and the delayQueue. The tasks in the ready queue are sorted based on their priorities, when a dispatch is called, the task in the front of the queue will be popped and executed. The delay queue holds the tasks that are still sleeping, and sorts them based on their delay time. After each clock tick the delay time decrements in all tasks in the delayQueue, once one of these tasks have delay = 0, it'll be transfered from the delay queue to the ready queue to be then sorted based on its priority and later executes.

# Main Data Structure
Srtuct Task, it contains:
1. Function Pointer
2. Task Name
3. Task Priority

Struct Node, it contains:
1. The Task
2. Task Delay
3. Pointer to next node

Struct Queue, it contains:
1. Queue Type /*D for delay , R for ready*/
2. Pointer to the head of the Queue /*the queue is an array of tasks, each has a function pointer and a priority*/

# Main Functions
* void QueTask(Task task);
* void Dispatch()
* void QueDelayedTask(Task task, int delay)
* void DecrementDelayed();
* void ReRunMe(int delay)
* void Init()
* void task1();
* int main();
