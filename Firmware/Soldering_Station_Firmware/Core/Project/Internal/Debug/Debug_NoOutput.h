/** ********************************************************************************** **/
/** * @file      Debug_NoOutput.h                                                    * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Debug_NoOutput.h.                                                   * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      30/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 30/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __DEBUG_NO_OUTPUT_H__
#define __DEBUG_NO_OUTPUT_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Generic Include. */
#include <stdint.h>

/* Generic Includes. */
#include <stdio.h>

/* Include Debug Levels. */
#include "Levels.h"

#include "Proj.h"
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
#if (ENABLE_PROJECT_LOGGER == DISABLED)

#define MODULE_DEBUG_REGISTER(_level, _name) 

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * Debug Prints                                                                     * */
/* ************************************************************************************ */

/**
*    @brief  This macro is used to print error messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_E( ... )


/**
*   @brief  This macro is used to print warning messages.
*   @param  _args_: Arguments to print
*/
#define PRINT_W( ... )


/**
*    @brief  This macro is used to print informational messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_I( ... )


/**
*    @brief  This macro is used to print debug messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_D( ... )   

/* TODO: Add debug prints. */

#endif /* __ENABLE_PROJECT_LOGGER__ */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_NO_OUTPUT_H__ */

/* -- End of file -- */
