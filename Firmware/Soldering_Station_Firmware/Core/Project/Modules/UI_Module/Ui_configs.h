/** ********************************************************************************** **/
/** * @file      Ui_configs.h                                                        * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Ui_configs.h.                                                       * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      09/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __UI_CONFIGS_H__
#define __UI_CONFIGS_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include UI module typpes. */
#include "Ui_types.h"

/* Include the Display Driver API. */
#include "ili9341.h"

/* Include the Display Driver API. */
#include "st7789.h"
#include <string.h>


/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Encapsulating Functions                                                          * */
/* ************************************************************************************ */

/**
 * @brief   Encapsulating function to the SET_PIN() function.
 *
 * @param[in]  pin      Pin number.
 * @param[in]  port     Port number.
 * @param[in]  state    Pin state.
 *
 * @return None.
 */
void UI_GPIOPin_Set_encapsulated(uint16_t pin, uint32_t port, uint8_t state);

/**
 * @brief   Encapsulating function to the Get_PIN() function.
 *
 * @param[in]  pin      Pin number.
 * @param[in]  port     Port number.
 *
 * @return Return the pin state.
 * @retval GPIO_HIGH the pin state is high.
 * @retval GPIO_LOW the pin state is low.
 */
uint8_t UI_GPIOPin_Read_encapsulated(uint16_t pin, uint32_t port);

/* ************************************************************************************ */
/* * Public Constant Variables                                                        * */
/* ************************************************************************************ */

#if (UI_LCD_DRIVER == UI_LCD_DRIVER_ILI9341)

    const st_UI_Config UI_default_config = 
    {
        .Set_Pin                        =  UI_GPIOPin_Set_encapsulated          ,
        .Get_Pin                        =  UI_GPIOPin_Read_encapsulated         ,
        .Display_Init                   =  ILI9341_Init                         ,
        .Display_Draw_Horizontal_Line   =  ILI9341_DrawHLine                    ,
        .Display_Draw_Vertical_Line     =  ILI9341_DrawVLine                    ,
        .Display_Draw_Rectangle         =  ILI9341_DrawRectangle                ,
        .Display_DrawText               =  NULL                                 ,
        .Display_FillColour             =  ILI9341_Fill                         ,
        .Display_Draw_RoundedRectangular = ST7789_DrawRoundRect
    };

#elif (UI_LCD_DRIVER == UI_LCD_DRIVER_ST7789)

    const st_UI_Config UI_default_config = 
    {
        .Set_Pin                        =  UI_GPIOPin_Set_encapsulated          ,
        .Get_Pin                        =  UI_GPIOPin_Read_encapsulated         ,
        .Display_Init                   =  ST7789_Init                          ,
        .Display_Draw_Horizontal_Line   =  NULL                                 ,
        .Display_Draw_Vertical_Line     =  NULL                                 ,
        .Display_Draw_Rectangle         =  ST7789_DrawRectangle                 ,
        .Display_DrawChar               =  ST7789_WriteChar                     ,
        .Display_FillColour             =  ST7789_Fill                          ,
        .Display_Draw_RoundedRectangular = ST7789_DrawRoundRect
    };

#endif
/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

void UI_GPIOPin_Set_encapsulated(uint16_t pin, uint32_t port, uint8_t state)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)(GPIOA_BASE + (0x00000400UL * port)),
                      1 << pin,
                      (GPIO_PinState)state);
}

uint8_t UI_GPIOPin_Read_encapsulated(uint16_t pin, uint32_t port)
{
    GPIO_PinState pin_state;
    pin_state = HAL_GPIO_ReadPin((GPIO_TypeDef *)(GPIOA_BASE + (0x00000400UL * port)),
                                 1 << pin);

    return (uint8_t)pin_state;
}

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __UI_CONFIGS_H__ */

/* -- End of file -- */
