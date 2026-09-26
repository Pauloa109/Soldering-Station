/** ********************************************************************************** **/
/** * @file      Application.c                                                       * **/
/** * @brief     This file contains all the functions implementation or prototypes   * **/
/** *            of Application.h.                                                   * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Include Header File. */
#include "Application.h"

/* Include Core. */
#include "Core_Include.h"

/* Include FSM. */
#include "fsm.h"

/* Include Ui module. */
#include "Ui.h"

#include "sd_card.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_tim.h"
#include "tim.h"


/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

#ifdef APP_DEBUG_LEVEL
  DEBUG_LEVEL_REGISTER(APP_DEBUG_LEVEL)
#else 
  DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_I)
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

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET App_Init(void){
  
  RET_REGISTER(ret);

  ret = FSM_Initialize();

  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("[APP] error initializing App. ")
    return -RET_NOT_OK;
  }

  return RET_OK;
}

et_RET App_Loop(void)
{
  RET_REGISTER(ret);

  ret = FSM_EncodeFSM();

  if(CHECK_RET_ERROR(ret))
  {
    PRINT_E("[APP] error looping app. ")
    return -RET_NOT_OK;
  }

  return RET_OK;
}


/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  HAL_TIM_Base_Stop_IT(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
  HAL_TIM_Base_Start_IT(&htim3);

  UI_Set_BuzzerState(BUZZER_ON);

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
      break;
*/
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

/* TODO: Add private functions. */
