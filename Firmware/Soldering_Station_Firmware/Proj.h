/** ********************************************************************************** **/
/** * @file      Proj.h                                                              * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Proj.h.                                                             * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      28/08/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 26/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __PROJ_H__
#define __PROJ_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include Debug defines.*/
#include "Debug.h"

#include "Internal_defines.h"

/* TODO: Add includes. */


/* ************************************************************************************ */
/* * Configurator Defines                                                             * */
/* ************************************************************************************ */

/** 
 * @brief  Macro to enable automatic target and code configurator configuration. 
 */
#define ENABLE_AUTO_CONFIGURATOR                (   1   ) 

#if (ENABLE_AUTO_CONFIGURATOR == 0)

    /* Define Project Target Here. */
    #define PROJECT_TARGET                      ( TARGET_STM32F1 )

    /* Define Code Configurator Here. */
    #define PROJECT_CODE_CONFIGURATOR           ( CODE_CONFIGURATOR_CMX )

#endif


/* ************************************************************************************ */
/* * System Configuration                                                             * */
/* ************************************************************************************ */

/* Enable logger function. */
#define PROJECT_ENABLE_LOGGER                   ( DISABLED )

/* Enable printf redirect. */
#define PROJECT_REDIRECT_PRINTF_ENABLE          ( 0 )

#if (PROJECT_REDIRECT_PRINTF_ENABLE == 1)

    /* Define Printf() Redirection Target Here. */
    #define PROJECT_REDIRECT_PRINTF_TARGET      ( PROJECT_REDIRECT_PRINTF_TARGET_USB )

    //#define PROJECT_REDIRECT_PRINTF_TARGET    ( PROJECT_REDIRECT_PRINTF_TARGET_UART )
#endif 


/* ************************************************************************************ */
/* * Public Main Defines                                                              * */
/* ************************************************************************************ */

/* Number of times that the application will retry configuration. */
#define NUMBER_OF_CONFIGURATION_RETRIES         (   3   )

/* Number of times that the application will retry loop. */
#define NUMBER_OF_LOOP_RETRIES                  (   3   )

/* TODO: Add defines here. */

/* ************************************************************************************ */
/* * Debug Configuration                                                              * */
/* ************************************************************************************ */

/* Main file debug level configuration.. */
#define MAIN_DEBUG_LEVEL                        ( DEBUG_LEVEL_I )

/* TODO: Add debug configuration here. */

/* ************************************************************************************ */
/* * UI Defines                                                                       * */
/* ************************************************************************************ */
#define UI_LCD_ENABLE                           (   ENABLED  )

#if (UI_LCD_ENABLE == ENABLED)

    #define UI_LCD_DRIVER                       (   UI_LCD_DRIVER_ST7789   )

    //#define UI_LCD_DRIVER                       (   UI_LCD_DRIVER_ILI9341   )

#endif

#ifdef __cplusplus
}
#endif


#endif /* __PROJ_H__ */

/* -- End of file -- */
