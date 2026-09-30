/** ********************************************************************************** **/
/** * @file      st7789_config.h                                                     * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            st7789_config.h.                                                    * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      29/10/2025                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 18/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __ST7789_CONFIG_H__
#define __ST7789_CONFIG_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

#include "st7789_types.h"
#include "stm32f1xx_hal_spi.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Encapsulating Functions Prototypes                                               * */
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
void ST7789_GPIOPin_Set_encapsulated(uint16_t pin, uint32_t port, uint8_t state);

/* ************************************************************************************ */
/* * Public Constant Variables                                                        * */
/* ************************************************************************************ */

//Configuration struct definition
const st_ST7789_conf ST7789_default_config =  
{
    .ST7789_GPIOPin_Set   = ST7789_GPIOPin_Set_encapsulated ,

    #if (ST7789_USE_DMA == ENABLED)  

        .ST7789_SPI_Transmit  = HAL_SPI_Transmit_DMA

    #else

        .ST7789_SPI_Transmit  = HAL_SPI_Transmit
        
    #endif

};

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

void ST7789_GPIOPin_Set_encapsulated(uint16_t pin, uint32_t port, uint8_t state)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)(GPIOA_BASE + (0x00000400UL * port)),
                      1 << pin,
                      (GPIO_PinState)state);
}

/* TODO: Add public function prototypes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __ST7789_CONFIG_H__ */

/* -- End of file -- */

