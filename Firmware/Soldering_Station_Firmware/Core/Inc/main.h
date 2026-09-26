/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_3_Pin GPIO_PIN_15
#define Button_3_GPIO_Port GPIOC
#define Button_3_EXTI_IRQn EXTI15_10_IRQn
#define Buzzer_Pin GPIO_PIN_1
#define Buzzer_GPIO_Port GPIOA
#define LCD_Back_Light_Pin GPIO_PIN_2
#define LCD_Back_Light_GPIO_Port GPIOA
#define Iron_Temp_Pin GPIO_PIN_3
#define Iron_Temp_GPIO_Port GPIOA
#define Gun_Temp_Pin GPIO_PIN_4
#define Gun_Temp_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_0
#define LCD_DC_GPIO_Port GPIOB
#define LDC_RST_Pin GPIO_PIN_1
#define LDC_RST_GPIO_Port GPIOB
#define Button_2_Pin GPIO_PIN_2
#define Button_2_GPIO_Port GPIOB
#define Button_2_EXTI_IRQn EXTI2_IRQn
#define LCD_CS_Pin GPIO_PIN_10
#define LCD_CS_GPIO_Port GPIOB
#define Heat_Gun_PWM_Pin GPIO_PIN_11
#define Heat_Gun_PWM_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_12
#define SD_CS_GPIO_Port GPIOB
#define Iron_PWM_Pin GPIO_PIN_8
#define Iron_PWM_GPIO_Port GPIOA
#define Blower_PWM_Pin GPIO_PIN_9
#define Blower_PWM_GPIO_Port GPIOA
#define Vaccum_PWM_Pin GPIO_PIN_10
#define Vaccum_PWM_GPIO_Port GPIOA
#define Zero_Cross_Pin GPIO_PIN_15
#define Zero_Cross_GPIO_Port GPIOA
#define Tilt_Sensor_Pin GPIO_PIN_3
#define Tilt_Sensor_GPIO_Port GPIOB
#define Tilt_Sensor_EXTI_IRQn EXTI3_IRQn
#define Reed_Switch_Pin GPIO_PIN_4
#define Reed_Switch_GPIO_Port GPIOB
#define Reed_Switch_EXTI_IRQn EXTI4_IRQn
#define Vaccum_On_Pin GPIO_PIN_5
#define Vaccum_On_GPIO_Port GPIOB
#define Vaccum_On_EXTI_IRQn EXTI9_5_IRQn
#define Button_4_Pin GPIO_PIN_6
#define Button_4_GPIO_Port GPIOB
#define Button_4_EXTI_IRQn EXTI9_5_IRQn
#define Channel_B_Pin GPIO_PIN_7
#define Channel_B_GPIO_Port GPIOB
#define Channel_A_Pin GPIO_PIN_8
#define Channel_A_GPIO_Port GPIOB
#define Channel_A_EXTI_IRQn EXTI9_5_IRQn
#define Button_2B9_Pin GPIO_PIN_9
#define Button_2B9_GPIO_Port GPIOB
#define Button_2B9_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
