/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Proj.h"

#include "Core_Include.h"

#include "Application.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum
{
  APP_STATE_INIT = 0,
  APP_STATE_INIT_ERROR,
  APP_STATE_LOOP,
  APP_STATE_LOOP_ERROR,
  APP_STATE_EXCESSIVE_ERROR
} et_app_state;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef NUMBER_OF_CONFIGURATION_RETRIES   
  #error "MAIN is not configured. Define NUMBER_OF_CONFIGURATION_RETRIES in the project  \
          configuration file. "
#endif

#ifndef NUMBER_OF_LOOP_RETRIES  
  #error "MAIN is not configured. Define NUMBER_OF_LOOP_RETRIES in the project           \
          configuration file. "
#endif

#ifndef MAIN_DEBUG_LEVEL
  #error "Main's debug level is not configured. Define MAIN_DEBUG_LEVEL                  \
          in the project configuration file."
#endif

#if (PROJECT_ENABLE_LOGGER == ENABLED)

    #if MAIN_DEBUG_LEVEL

        DEBUG_LEVEL_REGISTER(MAIN_DEBUG_LEVEL)

    #else 

        #warning "No debug level ser for the main"

        DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

    #endif

#else 

    MODULE_DEBUG_REGISTER(DEBUG_LEVEL_N, MAIN)

#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* */
static uint8_t g_numb_confretry = 0;
static uint8_t g_numb_loopretry = 0;

/* Application state variables */
static et_app_state g_state =      APP_STATE_INIT;
static et_app_state g_next_state = APP_STATE_INIT;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static et_RET MAIN_Init(void)
{
  RET_REGISTER(ret);

  while (g_numb_confretry < NUMBER_OF_CONFIGURATION_RETRIES)
  {
    ret = App_Init();

    if (CHECK_RET_ERROR(ret))
    {
      g_numb_confretry++;
      PRINT_D("APP failed to initialize. Retrying... (%d/%d)", g_numb_confretry, NUMBER_OF_CONFIGURATION_RETRIES);
    }

    else
    {
      break;
    }
  }

  return RET_INITIALIZED;
}

static et_RET MAIN_Loop(void)
{
  RET_REGISTER(ret);
  
  while (g_numb_loopretry < NUMBER_OF_LOOP_RETRIES)
  {
    ret = App_Loop();

    if (CHECK_RET_ERROR(ret))
    {
      g_numb_loopretry++;
      PRINT_D("APP loop failed. Retrying... (%d/%d)", g_numb_loopretry, NUMBER_OF_LOOP_RETRIES);
    }
    
    else
    {
      return RET_OK;
    }
  }

  return RET_NOT_OK;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  RET_REGISTER(ret);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    switch(g_state)
    {
      case APP_STATE_INIT:
        ret = MAIN_Init();
        
        if (CHECK_RET_ERROR(ret))
        {
          g_next_state = APP_STATE_INIT_ERROR;
          break;
        }

        g_next_state = APP_STATE_LOOP;
        break;

      case APP_STATE_INIT_ERROR:
        g_numb_confretry = 0;
        
        PRINT_D("APP failed to initialize. Going to error handler... ");

        g_next_state = APP_STATE_EXCESSIVE_ERROR;
        break;
              
      case APP_STATE_LOOP:
        ret = MAIN_Loop();
        
        if (CHECK_RET_ERROR(ret))
        {
          g_next_state = APP_STATE_LOOP_ERROR;
          break;
        }

        g_next_state = APP_STATE_LOOP;
        break;

      case APP_STATE_LOOP_ERROR:

        g_numb_loopretry = 0 ;
        PRINT_D("APP loop failed. Going to error handler...");
        
        g_next_state =  APP_STATE_EXCESSIVE_ERROR;
        break;

      case APP_STATE_EXCESSIVE_ERROR:
      
        PRINT_D("APP reached excessive error state.");
        
        while (1)
        {
          /* Infinite loop */
        }
        break;

      default:
        g_next_state = APP_STATE_LOOP_ERROR;
        
        break;
    }

    /* Encode FSM. */
    g_state = g_next_state;
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
#ifdef USE_FULL_ASSERT
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
