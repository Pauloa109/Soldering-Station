/** ********************************************************************************** **/
/** * @file      st7789_types.h                                                      * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            st7789_types.h.                                                     * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      17/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __ST7789_TYPES_H__
#define __ST7789_TYPES_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include API define File. */
#include "st7789_defines.h"
#include "stm32f1xx_hal_spi.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Typedefs                                                                  * */
/* ************************************************************************************ */

//Type for a function that sets the state of a GPIO pin
typedef void    (*t_ST7789_GpioPin_Set)             (uint16_t pin, 
                                                     uint32_t port, 
                                                     uint8_t state); 

#if (PROJECT_CODE_CONFIGURATOR == CODE_CONFIGURATOR_CMX)

    #if (ST7789_USE_DMA == ENABLED)

        //Type for a function that send spi data with DMA
        typedef HAL_StatusTypeDef  (*t_ST7789_SPI_Transmit)    (SPI_HandleTypeDef *hspi, 
                                                                const uint8_t *pData, 
                                                                uint16_t Size);
                                                        
    #else 

        //Type for a function that send spi data withOUT DMA
        typedef HAL_StatusTypeDef  (*t_ST7789_SPI_Transmit)    (SPI_HandleTypeDef *hspi, 
                                                                const uint8_t *pData, 
                                                                uint16_t Size, 
                                                                uint32_t Timeout);

    #endif

#endif

/* TODO: Add typedefs. */

/* ************************************************************************************ */
/* * Public Structures                                                                * */
/* ************************************************************************************ */

//Configuration struct definition
typedef struct 
{
    t_ST7789_GpioPin_Set            ST7789_GPIOPin_Set;                                      
    t_ST7789_SPI_Transmit           ST7789_SPI_Transmit;

} st_ST7789_conf;



/* TODO: Add structures. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __ST7789_TYPES_H__ */

/* -- End of file -- */
