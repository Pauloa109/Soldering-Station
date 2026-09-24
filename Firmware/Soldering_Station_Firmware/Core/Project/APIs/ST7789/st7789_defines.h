/** ********************************************************************************** **/
/** * @file      st7789_defines.h                                                   * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            st7789_defines.h.                                                  * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      17/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __ST7789_DEFINES_H__
#define __ST7789_DEFINES_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

#include "spi.h"
/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Defines                                                                   * */
/* ************************************************************************************ */

/* choose a Hardware SPI port to use. */
#define ST7789_SPI_PORT hspi1

/* choose whether use DMA or not */
#define ST7789_USE_DMA                  ( DISABLED )

#define ST7789_USING_240X320

#define ST7789_ROTATION 1


#define ST7789_USE_INTERNAL_STORAGE     ( DISABLED )
/* TODO: Add defines. */

/* ************************************************************************************ */
/* * ST7789 API's Pins Defines                                                        * */
/* ************************************************************************************ */

#define DISPLAY_DC_PIN                  (   0   )
#define DISPLAY_DC_PORT                 (   GPIO_PORTB   )

#define DISPLAY_CS_PIN                  (   10   )
#define DISPLAY_CS_PORT                 (   GPIO_PORTB   )

#define DISPLAY_RST_PIN                 (   1   )
#define DISPLAY_RST_PORT                (   GPIO_PORTB   )

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * Size Definitions                                                                 * */
/* ************************************************************************************ */

#ifdef ST7789_USING_135X240

    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 53
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 52
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 52
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 53
    #endif

#endif

#ifdef ST7789_USING_240X240

#define ST7789_WIDTH 240
#define ST7789_HEIGHT 240

#if ST7789_ROTATION == 0
#define X_SHIFT 0
#define Y_SHIFT 80
#elif ST7789_ROTATION == 1
            #define X_SHIFT 80
            #define Y_SHIFT 0
        #elif ST7789_ROTATION == 2
            #define X_SHIFT 0
            #define Y_SHIFT 0
        #elif ST7789_ROTATION == 3
            #define X_SHIFT 0
            #define Y_SHIFT 0
        #endif

#endif

#ifdef ST7789_USING_240X320

    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 320
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 240
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 320
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 240
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #endif

#endif

#ifdef ST7789_USING_170X320

    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif

#endif

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __ST7789_DEFINES_H__ */

/* -- End of file -- */
