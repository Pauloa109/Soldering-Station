/** ********************************************************************************** **/
/** * @file      fsm_states.c                                                        * **/
/** * @brief     This file contains all the functions implementation or prototypes   * **/
/** *            of fsm_states.h.                                                    * **/
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

/* Inclue Header Fille. */
#include "fsm_states.h"

/* Include Ui Module. */
#include "Core/Project/Project/Modules/UI_Module/Ui_defines.h"
#include "Ui.h"

#include "adc.h"
#include "st7789.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_dma.h"
#include <stdio.h>

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

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

/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

et_FSM_state FSM_idle_state_handler(void)
{
    et_FSM_state next_state = idle_state;

    UI_Refresh_SelectedChannel();

    if (UI_encoder_c_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_encoder_c_but_clear_logged_state();

        switch(UI_Get_SelectedChannel())
        {
            case 0:
                UI_Draw_IronScreen();
                next_state = iron_state;
                break;

            case 1:
                next_state = gun_state;
                break;

            default:
                break;

        }

    }

    return next_state;
}

et_FSM_state FSM_init_state_handler(void)
{
    

    return RET_OK;
}

et_FSM_state FSM_iron_state_handler(void)
{
    et_FSM_state next_state = iron_state;

    static uint16_t adc_result_vec[2];

    char buff[10];

    if (UI_encoder_c_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_encoder_c_but_clear_logged_state();
        UI_Draw_IronScreen();
        next_state = idle_state;

    }

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_result_vec, 2);
    
  HAL_Delay(1500);
    sprintf(buff, "%d   ", adc_result_vec[0]);

    uint8_t i = 0;
    while (buff[i])
    {
        ST7789_WriteChar(10 +i *20, 10, buff[i], Font_11x18,CYAN, BLACK);

        i++;
    }

    return next_state;
}

et_FSM_state FSM_gun_state_handler(void)
{
    return RET_OK;
}

et_FSM_state FSM_error_state_handler(void)
{
    return RET_OK;
}

/* TODO: Add private functions. */

/* -- End of file -- */
