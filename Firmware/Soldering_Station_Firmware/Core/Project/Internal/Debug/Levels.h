/** ********************************************************************************** **/
/** * @file      Levels.h                                                            * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Levels.h.                                                           * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      28/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 28/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __LEVELS_H__
#define __LEVELS_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Debug Levels                                                                     * */
/* ************************************************************************************ */

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

/* TODO: Add debug levels. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __LEVELS_H__ */

/* -- End of file -- */
