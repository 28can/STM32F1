/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

int fputc(int ch,FILE *f)
{
HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);//重定向哪个串口第一个就写huart几
return ch;
}

#define LED0_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_0 ,GPIO_PIN_RESET)
#define LED0_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_0 ,GPIO_PIN_SET)

#define LED1_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_1 ,GPIO_PIN_RESET)
#define LED1_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_1 ,GPIO_PIN_SET)

#define LED2_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_2 ,GPIO_PIN_RESET)
#define LED2_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_2 ,GPIO_PIN_SET)

#define LED3_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_3,GPIO_PIN_RESET)
#define LED3_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_3 ,GPIO_PIN_SET)

#define LED4_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_4 ,GPIO_PIN_RESET)
#define LED4_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_4 ,GPIO_PIN_SET)

#define LED5_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_5 ,GPIO_PIN_RESET)
#define LED5_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_5 ,GPIO_PIN_SET)

#define LED6_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_6 ,GPIO_PIN_RESET)
#define LED6_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_6 ,GPIO_PIN_SET)

#define LED7_ON()  HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_7 ,GPIO_PIN_RESET)
#define LED7_OFF() HAL_GPIO_WritePin (GPIOC ,GPIO_PIN_7 ,GPIO_PIN_SET)

#define LED0_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0)
#define LED1_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1)
#define LED2_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_2)
#define LED3_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_3)
#define LED4_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_4)
#define LED5_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5)
#define LED6_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6)
#define LED7_Tog() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7)

uint8_t Tx_str1[]="hello world!\r\n";
uint8_t Tx_str2[]="LED1!\r\n";
uint8_t Tx_str3[]="LED2!\r\n";
uint8_t Rx_dat=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance==USART1 ){
		if(Rx_dat==0xa1){
			LED1_ON ();
			HAL_UART_Transmit(&huart1 ,Tx_str2 ,sizeof (Tx_str2),1000);
			LED1_OFF ();
			HAL_UART_Receive_IT(&huart1 ,&Rx_dat,1);
		}
		else if(Rx_dat==0xa2){
			LED2_ON ();
			HAL_UART_Transmit(&huart1 ,Tx_str3 ,sizeof (Tx_str3),1000);
			LED2_OFF ();
			HAL_UART_Receive_IT(&huart1 ,&Rx_dat,1);
		}
	}
	HAL_UART_Receive_IT(&huart1 ,&Rx_dat,1);
}


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LED1_ON ();
  //HAL_UART_Transmit(&huart1 ,Tx_str1,sizeof (Tx_str1),10000);
  printf ("hello world!");
  LED1_OFF ();
  HAL_UART_Receive_IT(&huart1 ,&Rx_dat,1); 

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
