/** ********************************************************************************** **/
/** * @file      Application.c                                                       * **/
/** * @brief     This file contains all the functions implementation or prototypes   * **/
/** *            of Application.h.                                                   * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 30/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Include Header File. */
#include "Application.h"

/* Include Core. */
#include "Core_Include.h"

/* Include FSM. */
#include "Helpers.h"
#include "Return_types.h"
#include "Returns.h"
#include "fsm.h"

/* Include Ui module. */
#include "Ui.h"

#include "sd_card.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "tim.h"

#include "spi.h"

#include "xpt2046.h"
#include <stdint.h>

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */
#if (PROJECT_ENABLE_LOGGER == ENABLED)

    #if APP_DEBUG_LEVEL

        DEBUG_LEVEL_REGISTER(APP_DEBUG_LEVEL)

    #else 

        #warning "No debug level ser for the APP"

        DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

    #endif

#else 

    MODULE_DEBUG_REGISTER(DEBUG_LEVEL_N,APP_module)

#endif

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * Private Typedefs                                                                 * */
/* ************************************************************************************ */

/* TODO: Add typedefs. */

/* ************************************************************************************ */
/* * Private Enumerations                                                             * */
/* ************************************************************************************ */

/* TODO: Add enumerations. */

/* ************************************************************************************ */
/* * Private Structures                                                               * */
/* ************************************************************************************ */

/* TODO: Add structures. */

/* ************************************************************************************ */
/* * Private Flags                                                                    * */
/* ************************************************************************************ */

/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */

uint16_t x,y;

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

et_RET reconfigure_spi(SPI_HandleTypeDef *spi, uint32_t prescaler);

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET App_Init(void){
  
  RET_REGISTER(ret);

  ret = reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_256);
  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("error initializing App. ");
    return -RET_NOT_OK;
  }

  xpt2046_spi(&hspi1);
  xpt2046_init();

  ret = reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_4);
  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("[APP] error initializing App. ");
    return -RET_NOT_OK;
  }

  ret = FSM_Initialize();
  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("[APP] error initializing App. ");
    return -RET_NOT_OK;
  }

  return RET_OK;
}

et_RET App_Loop(void)
{
  RET_REGISTER(ret);

  ret = FSM_EncodeFSM();

  /*reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_256);
  xpt2046_read_position(&x, &y);
  reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_4);*/

  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("[APP] error looping app. ");
    return -RET_NOT_OK;
  }

  return RET_OK;
}


/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

et_RET reconfigure_spi(SPI_HandleTypeDef *spi, uint32_t prescaler)
{
  HAL_StatusTypeDef hal_ret;
  
  if (CHECK_PTR(spi))
  {
    return -RET_NULL_PTR;
  }

  hal_ret = HAL_SPI_DeInit(spi);

  if (hal_ret != HAL_OK)
  {
    return -RET_NULL_PTR;
  }

  hspi1.Instance = spi->Instance;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = prescaler;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;

  if (HAL_SPI_Init(spi) != HAL_OK)
  {
    return -RET_NOT_OK;
    __disable_irq();
  }

  return RET_OK;
}

/* TODO: Add private functions. */

/* ************************************************************************************ */
/* * ISR Functions                                                                    * */
/* ************************************************************************************ */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  HAL_TIM_Base_Stop_IT(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
  HAL_TIM_Base_Start_IT(&htim3);

  //UI_Set_BuzzerState(BUZZER_ON);

  switch (GPIO_Pin) 
  {
    case (1 << ENCODER_A_PIN):
      UI_encoder_a_but_ISR();
      break;

    case (1 << ENCODER_C_PIN):
      UI_encoder_c_but_set_logged_state();
      break;

    case (1 << MACRO_B1_PIN):
      UI_b1_but_set_logged_state();
      break;

    case (1 << MACRO_B2_PIN):
      UI_b2_but_set_logged_state();
      break;

    /*case (1 << MACRO_B3_PIN):
      UI_b3_but_set_logged_state();
      break;*/

    case (1 << IRON_TILTI_SENSOR_PIN):
      UI_iron_tilt_sen_get_logged_state();
      break;

    case (1 << HEAT_GUN_MAG_SENSOR_PIN):
      UI_heat_gun_sen_get_logged_state();
      break;

    case (1 << VACCUM_PUMP_TRIGGER_PIN):
      UI_vaccum_pump_trg_set_logged_state();
      break;

    case (1 << ZERO_CROSS_PIN):
      UI_zero_croos_sen_set_logged_state();
      break;

    case (1 << DISPLAY_IQR_PIN):  
      reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_256);
      xpt2046_update();
      reconfigure_spi(&hspi1, SPI_BAUDRATEPRESCALER_4);
      break;
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    HAL_TIM_Base_Stop_IT(&htim3);
    UI_Set_BuzzerState(BUZZER_OFF);
  }
}

/* TODO: Add ISR functions. */
