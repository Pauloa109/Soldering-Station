/********************************************************************************
  * @file   Debug.h
  * @brief  This file contains the debug levels used in the project
  ******************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
* Includes
****************************************************************************/

#include <stdio.h>


#define DEBUG_LEVEL_REGISTER(_level)             \
    static const uint8_t _DEBUG_LEVEL = _level;

/****************************************************************************
* Debug Levels
****************************************************************************/

/**
 * @brief   This debug level is used to indicate that no debug 
 *          information should be printed.
 */
#define DEBUG_LEVEL_N       ( 0 )

/**
 * @brief   This debug level is used to indicate that only error messages 
 *          should be printed.
 */
#define DEBUG_LEVEL_E       ( 1 )

/**
 * @brief   This debug level is used to indicate that error and warning 
 *          messages should be printed.
 */
#define DEBUG_LEVEL_W       ( 2 )

/**
 * @brief   This debug level is used to indicate that all debug messages 
 *          should be printed.
 */
#define DEBUG_LEVEL_I       ( 3 )

/**
 * @brief   This debug level is used to indicate that error, warning, 
 *          and debug messages should be printed.
 */
#define DEBUG_LEVEL_D       ( 4 )

/****************************************************************************
* Debug Prints
****************************************************************************/

/**
*    @brief  This macro is used to print error messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_E( ... )                  \
    if (_DEBUG_LEVEL <= DEBUG_LEVEL_E)  \
    {                                   \
        printf("[E]");                  \
        printf( __VA_ARGS__ );          \
        printf("\r\n");                 \
    }

/**
*   @brief  This macro is used to print warning messages.
*   @param  _args_: Arguments to print
*/
#define PRINT_W( ... )                  \
    if (_DEBUG_LEVEL <= DEBUG_LEVEL_W)  \
    {                                   \
        printf("[W]");                  \
        printf( __VA_ARGS__ );          \
        printf("\r\n");                 \
    }

/**
*    @brief  This macro is used to print informational messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_I( ... )                  \
    if (_DEBUG_LEVEL <= DEBUG_LEVEL_I)  \
    {                                   \
        printf("[I]");                  \
        printf( __VA_ARGS__ );          \
        printf("\r\n");                 \
    }

/**
*    @brief  This macro is used to print debug messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_D( ... )                  \
    if (_DEBUG_LEVEL <= DEBUG_LEVEL_D)  \
    {                                   \
        printf("[D]");                  \
        printf( __VA_ARGS__ );          \
        printf("\r\n");                 \
    }


#ifdef __cplusplus
}
#endif


#endif /* __DEBUG_H__ */
