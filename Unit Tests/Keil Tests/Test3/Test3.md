void task1() {
		HAL_Delay(2000);

	//printf("this is task 1 :) \n");
	for (int i = 1; i<=20;i++) // toggle
	 {
		 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		 HAL_Delay(250);
	 }
	
	 /* 1 tick =50 ms, every 20 ticks = 1 sec*/
	 ReRunMe(20); /*rerun after 1 sec*/ 
}

void task2() {
	HAL_Delay(2000);

	//printf("this is task 2 hellooo \n");
	for (int i = 1; i<=14;i++) // toggle
	 {
		 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		 HAL_Delay(250);
	 }
	 
	ReRunMe(200); /*rerun after 10 sec*/ 

}

void task3() {
	HAL_Delay(2000);
	
	for (int i = 1; i<=10;i++) // toggle
	 {
		 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		 HAL_Delay(250);
	 }
}

int main(void)
{
	
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



	Task A;
	A.priority = 1;
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

	QueTask(B);


	QueTask(C);

	while (1) {
		Dispatch();

	}
	
  /* USER CODE END 3 */
}
