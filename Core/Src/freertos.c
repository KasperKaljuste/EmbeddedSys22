/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "joystick.h"
#include "stm32f429i_discovery_lcd.h"
#include "fonts.h"
#include "ball_game.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f429i_discovery.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define splash 0
#define game 1
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
SemaphoreHandle_t JoyMutex;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vLCDtask(void const * argument);
void vJOYtask(void const * argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  JoyMutex = xSemaphoreCreateMutex();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 4096);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  UartTaskInit();
  xTaskCreate(vLCDtask, "LCDtask", 1000, NULL, osPriorityNormal, NULL);
  xTaskCreate(vJOYtask, "JOYtask", 1000, NULL, osPriorityNormal, NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
volatile Joystick_ud_lr ud_lr;

void vLCDtask(void const * argument){
	score score;
	score.score = 0;
	score.high_score = 0;
	score.level = 1;
	powerup powerup;
	powerup.type = 0;
	uint8_t state = splash;
	char buffer[50];
	char instruction[] = "score +1000";
	char instruction2[] = "or speed reset";

	ball ball = ball_init();
	line line1 = create_line(line1);
	line line2 = create_line(line2);
	// Second line offset
	line2.y = BSP_LCD_GetYSize()/2;

	for(;;){
		if (state == splash) {
			// Update high score
			if (score.score > score.high_score) {
				score.high_score = score.score;
			}
			// Display score and high score
			snprintf(buffer, 50, "SCORE: %d", score.score);
			BSP_LCD_DisplayStringAt(0, 10, buffer, CENTER_MODE);
			snprintf(buffer, 50, "BEST: %d", score.high_score);
			BSP_LCD_DisplayStringAt(0, 50, buffer, CENTER_MODE);

			// Display instructions
			BSP_LCD_FillRect(110, 80, 20, 20);
			BSP_LCD_DisplayStringAt(0, 100, instruction, CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 120, instruction2, CENTER_MODE);

			// Start game if button pressed
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
				score.score = 0;
				score.level = 1;
				ball = ball_init();
				line1 = create_line(line1);
				line2 = create_line(line2);
				line2.y = BSP_LCD_GetYSize()/2;
				state = game;
			}
		}
		if (state == game) {
			score.score += 1;
			// Increase level and possibly create powerup every 200 points
			if(!(score.score % 200)){
				score.level += 1;
				powerup = create_powerup(powerup);

			}

			// Move ball and lines
			ball = move_ball(ball, ud_lr, ball.speed);
			ball.speed = score.level + 1;
			line1.speed = score.level;
			line1 = move_line(line1);
			line2.speed = score.level;
			line2 = move_line(line2);
			// Check for collision
			if (check_collision(ball, line1) || check_collision(ball, line2)) {
				state = splash;
			}

			BSP_LCD_Clear(LCD_COLOR_GRAY);

			// Show score
			snprintf(buffer, 50, "SCORE: %d", score.score);
			BSP_LCD_DisplayStringAt(0, 10, buffer, CENTER_MODE);
			// Show ball and lines
			BSP_LCD_FillCircle(ball.x, ball.y, ball.radius);
			BSP_LCD_DrawHLine(line1.x1, line1.y, line1.x1_len);
			BSP_LCD_DrawHLine(line1.x2, line1.y, line1.x2_len);
			BSP_LCD_DrawHLine(line2.x1, line2.y, line2.x1_len);
			BSP_LCD_DrawHLine(line2.x2, line2.y, line2.x2_len);

			// Check for powerup
			if (powerup.type != 0) {
				BSP_LCD_FillRect(powerup.x-10, powerup.y-10, 20, 20);
				if (check_powerup_collision(ball, powerup)) {
					if(powerup.type == 1){
						score.score += 1000;
					}
					else {
						score.level = 1;
					}
					powerup.type = 0;
				}
			}

			HAL_Delay(20);
		}
	}
}

void vJOYtask(void const * argument){
	char buffer[50];
	uint16_t len;
	for(;;){
		xSemaphoreTake(JoyMutex, portMAX_DELAY);
		Joystick_Read(&ud_lr);
		xSemaphoreGive(JoyMutex);
		len = snprintf(buffer, sizeof(buffer), "Joy LR=%d, UD=%d\n", ud_lr.lr, ud_lr.ud);
		UartTask_sendData(buffer, len);
	}
}
/* USER CODE END Application */
