/** ********************************************************************************** **/
/** * @file      Internal_defines.h                                                  * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Defines.h.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      17/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 26/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __INTERNAL_DEFINES_H__
#define __INTERNAL_DEFINES_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include Project Level Cofiguration Fille. */
#include "Proj.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Code Configurators                                                               * */
/* ************************************************************************************ */

/* Code Configurator Defines. */
#define CODE_CONFIGURATOR_CMX        ( 1 )


/* ************************************************************************************ */
/* * Supported Targets                                                                * */
/* ************************************************************************************ */

#define TARGET_STM32F1               ( 1 )

/* ************************************************************************************ */
/* * Generic Defines                                                                  * */
/* ************************************************************************************ */

#define DISABLED                      ( 0 )

#define ENABLED                       ( 1 )

/* ************************************************************************************ */
/* * Redirect Defines                                                                 * */
/* ************************************************************************************ */

/**
 * @brief   Defines the USB interface as the printf redirection target.
 *
 * @note    PROJECT_REDIRECT_PRINTF_TARGET must be defined with this value.
 */
#define PROJECT_REDIRECT_PRINTF_TARGET_USB              (   0   )

/**
 * @brief   Defines the uart interface as the printf redirection target.
 *
 * @note    PROJECT_REDIRECT_PRINTF_TARGET must be defined with this value.
 */
#define PROJECT_REDIRECT_PRINTF_TARGET_UART             (   1   )

/* ************************************************************************************ */
/* * Ui Defines                                                                       * */
/* ************************************************************************************ */

/**
 * @brief   Defines the ili9341 as the lcd.
 *
 */
#define UI_LCD_DRIVER_ILI9341          (   0   )

/**
 * @brief   Defines the st7789 as the lcd.
 *
 */
#define UI_LCD_DRIVER_ST7789           (   1   )

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __INTERNAL_DEFINES_H__ */

/* -- End of file -- */
