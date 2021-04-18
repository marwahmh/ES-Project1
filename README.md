# Embedded Systems - Project1: Cooperative Scheduler
This project is done for the Embedded Systems Course in the American University in Cairo Spring 2021. <br/>
Instructor: Dr. Mohamed Shalan <br/>
Done By: Dareen Hussein (ID: 900170917), Marwa Sulaiman (ID: 900172284)

## The Cooperative Scheduler Logic:
There is a struct named "Task" which contains the task pointer, priority and task name. The scheduler has 2 Tasks queues; the readyQueue and the delayQueue. The tasks in the ready queue are sorted based on their priorities, when a dispatch is called, the task in the front of the queue will be popped and executed. The delay queue holds the tasks that are still sleeping, and sorts them based on their delay time. After each clock tick the delay time decrements in all tasks in the delayQueue, once one of these tasks have delay = 0, it'll be transfered from the delay queue to the ready queue to be then sorted based on its priority and later executes.

## Softwares and Languages Used:
* This project is developed using STM32CubeMX and Keil μVision to run on the Nucleo-32 board.
* The language used to develop the scheduler is C.
* Tera Term was used as an external source for data entry.

## Hardware Used:
* STM32 Nucleo-32 development board with STM32L432KC MCU.
* DS3221Tempreature Sensor.
* HC-sr04 Ultrasound Sensor.
* USB to TTL bridge.
* Buzzer.

## Main Data Structure:
Srtuct Task, it contains:
1. Function Pointer
2. Task Name
3. Task Priority

Struct Node, it contains:
1. The Task
2. Task Delay
3. Pointer to next node

Struct Queue, it contains:
1. Queue Type *(D for delay , R for ready)*
2. Pointer to the head of the Queue *(the queue is an array of tasks, each has a function pointer and a priority)*. Note: The queue is implemented using linked lists.

## Main Functions:
* void Systick Handler()
  * Gets called everytime the SysTick handler throws an interrupt. It also increments the counter variable. This variable is used to keep track of the cycles spent in a certain task function (that is essentially doing its job in time units more than a single systick and hence skipping cycles where the rest of the main program isn't doing its regular dispatching). The reason why we keep track of this is to later use it over the delay queue to decrement the tasks' delays since practically this is the amount of time they've been waiting for during the execution of a running task with a delay. Nevertheless, their delays also get decremented by 1 every tick = 50 ms.
* void QueTask(Task task)
  * This function enqeues a task using its function pointer into the main readyQueue. The requirements specification document states that the scheduler should handle up to 8 priority levels.
* void Dispatch()
  * This function gets called in our while(1) loop every time the SysTick throws an interrupt every 1 time unit. It checks if the ready queue is not empty. It then dequeues the highest priority task from the queue and executes it. It sets the timerFlag to zero so as to not dispatch again until the Systick timer raises the flag once more (i.e. the timer has counted 1 tick = 50ms). If the queue is empty it output "IDLE" to the user.
* void QueDelayedTask(Task task, int delay)
  * This function manages the process of adding delayed tasks to the delay queue and sort them ascendingly according to delay time. 
* void ReRunMe(int delay)
  * This function is used by tasks to rerun themselves periodically every specified delay time units. If the delay is 0, then this task is by definition ready and can be enqueued in the readyQueue. Otherwise, if the delay is greater than 0, then this task is by definition is to be enqueued in the delay queue using its delay values. If the delay option is set to 0 by the task within its function then this means that this task is always ready and will always remain in the main queue because it inserts itself everytime its executed in it through the rerun function.
* void Init()
  * This is the first function called in the main. Here, all the basic initialization (clock, UART, Systick, and interrupts) is done. Furthermore, the ready and delayed priority queues are instantiated besides there qeue heads are initialized.
* int main()
  * This is where the while(1) loop exists and where all of the functions are called.

# Unit Tests
## For the Compiled C file
### Test1: ReRunMe(0)
We have 3 Tasks (A,B,C). Task A here is the task with the highest priority, and will use ReRunMe with 0 delay time.<br/>
<img alt="Results1" src="https://user-images.githubusercontent.com/49562717/114270967-7733c300-9a0f-11eb-8dab-253760e5e88c.png" width="500" height="350"/>

### Test2: Scheduling of 3 Tasks
We have 3 Tasks (A,B,C). Task C has the highest priority then B then A. A reruns itself after 3 ticks, while B reruns itself after 5 ticks. The expected output is the execution of C->B->A then the readyQueue will be empty for 2 tickS then it will start executing A->B->A->B and so on. <br/>
<img alt="Results2" src="https://user-images.githubusercontent.com/49562717/114271055-d691d300-9a0f-11eb-90ff-66f23d28ea5a.png" width="500" height="350"/>

### Test3: Attempting to input an invalid priority number
We're trying here to give TaskA an invalid priority number, to test the program since the schedueler supports 8 priority levels.<br/>
<img alt="Results3" src="https://user-images.githubusercontent.com/49562717/114271157-4acc7680-9a10-11eb-85b4-79c095ba639d.png" width="500" height="350"/>

### Test4: Testing with 4 Tasks (A, B, C, D) - Scalability Test
<img width="443" alt="Table" src="https://user-images.githubusercontent.com/49562717/115131724-937cc480-9ffa-11eb-911f-13203cb643a6.png">

<img alt="Scalibility" src="https://user-images.githubusercontent.com/49562717/114271685-e959d700-9a12-11eb-9878-f37ea45ac2df.png" width="500" height="350"/>

<img alt="Results4" src="https://user-images.githubusercontent.com/49562717/114271174-5fa90a00-9a10-11eb-815f-60a17b33878a.png" width="500" height="350"/>

## For the Keil files
### Test: Scheduling of 3 Tasks with different delyas
<img width="478" alt="Table" src="https://user-images.githubusercontent.com/49562717/115131758-c1620900-9ffa-11eb-9c6a-b056878a4e4a.png">

Output: https://drive.google.com/file/d/1spVxLQkFRArvk3AICtrd3Z3w1sfNeTWR/view?usp=sharing


# Applications
We developed two applications each of which has its source code in its corresponding branch in branchs Application1 and Application2.

## Application1: Tempreature Sensor
### Objective
Read the ambient temperature using a sensor every 30 sec. Produce an alarm (LED flashing) when the temperature exceeds a threshold. 
### Main Functions
* setThreshold(): converts the user's input thershold from text to decimal.
* ReadTemp(): Transmits the addresses to the temperature registers and receives the current measured temperature through the I2C1 bus. Then, it converts it to text and transmits it through UART to the user. Lastly, ReRunMe is called for the task to run every 30 sec.
* compareToThreshold():Compares the measured temperature obtained from ReadTemp() to the decimal equivalent of the user inout threshold obtained by setThreshold(). If the measure temp is higher than the threshold, the function calls a task that toggles the LED 10 times.
* Note: the user input (threshold) is received through UART in the USART1_IRQHandler()

### Circuit connections

<p float="left">
<img src="https://user-images.githubusercontent.com/52168271/115127133-69b0a700-9fd4-11eb-9cc3-87745e85a2d2.png" width="500" height="350"/>
<img src="https://user-images.githubusercontent.com/52168271/115127091-09216a00-9fd4-11eb-82d2-8af8a71671a3.png" width="430" height="300"/>
</p>

As shown, UART1 is used and connected by the USB-To-TTL module to trnasmit and receive to/from the PC through pins PA9 and PA10, and I2C1 is used to connect the MCU with the Temperature sensor through pins PB6 and PB7. Also, the LED is configured internally through pin PB3. The MCU, the Temp. sensor and the USB-To-TTL module all share a common ground, and the sensor is powered by a 5V voltage supply.

## Demos
### Test1: Measured Temp. exceeded Threshold
Video link: https://drive.google.com/file/d/1FWX-p2BTqy-debhzp-NkHRv8ERniyLWN/view?usp=sharing

Note that it blinks each time the temperature is measured and is greater than the threshold. Also note that it reads the temperature every 30 sec.

### Test2: Measured Temp. below Threshold
Video link: https://drive.google.com/file/d/1lfV5HT0CyyDAeB_bXuu1N5zTFplMP_Ra/view?usp=sharing

Note that it does not blink.

## Application2: Parking Sensor
### Objective
Produce a sound that reflects how close is the car from the nearest object. A buzzer will be used
to produce beeps and the duration between the beeps reflects how far is the object.

### Main Functions
* void readData()
  * Gets called every tick to update the triggered pin and enable the HAL_TIM.
* void measureDist()
  * measures the distance aand produce the buzz sound delay accodringly. Note that it starts only when distance measured is less than 200 cm. 
* Since TIM1 channel 1 is used to capture the data (the echo), HAL_TIM_IC_CaptureCallback is modified to perform the function of obtaining the difference between the start and the end of the echo signal and use it to calculate the distance in cm.

### Circuit Connections

<p float="left">
<img src="https://user-images.githubusercontent.com/52168271/115127251-6669eb00-9fd5-11eb-97ca-7b0f68b695c5.png" width="350" height="300"/>
<img src="https://user-images.githubusercontent.com/52168271/115130969-61686400-9ff4-11eb-913b-b24078b6b50e.png" width="250" height="300"/>
</p>

The trigger of the altrasound sensor is connected to GPIO pin PA9, and the echo is connected to PA8, which is configured as TIM1 channel 1. The buzzer is connected to GPIO pin PB0. The snesor, the buzzer and the MCU share a common ground, and the sensor powered by 5V supply. 

## Demo
video link: https://drive.google.com/file/d/1420I_WIc1j1dxZz1iE0I2gjHltBmyWYi/view?usp=sharing

# Running and Building the Code
You should follow these steps to build and compile the project:

1. After downloading the project file, run the µVision5 Project titled CoScheduler.
2. If you would like to change the priorities of the tasks and their delay time, go to these parts in the code and change them accordingly: SCREENSHOOT!!!
3. You may use the QueTask() function to add tasks to the queue along with their priorities after the Init() function call.
4. Build the project, load it on the Nucleo-32 Board and make sure there are no errors.

### For Application 1
5. Enter the threshold value (the user has a buffer of 5 characters, they can use 2 digits for the integer and another 2 fractional partions separated by a '.').
6. Notice the output ambient temperature, and if it exceeds the threshold the LED will flash.

### For Application 2
5. Place an object in front of the ultrasonic sensor and vary the distance.
6. Notice the change in duration of the beeps reflecting the distance.

# Refrences
1. STM32L432KC Datasheet: https://www.st.com/resource/en/datasheet/stm32l432kc.pdf
2. DS3231 Tempreature Sensor Datasheet: https://datasheets.maximintegrated.com/en/ds/DS3231-DS3231S.pdf
3. HC-sr04 Ultrasonic sensor Datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
