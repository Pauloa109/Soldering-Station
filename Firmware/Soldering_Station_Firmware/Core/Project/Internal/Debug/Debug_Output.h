/** ********************************************************************************** **/
/** * @file      Debug_Output.h                                                             * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Debug_Output.h.                                                            * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      25/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 30/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __DEBUG_OUTPUT_H__
#define __DEBUG_OUTPUT_H__

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
/* * Check Enable                                                                     * */
/* ************************************************************************************ */

#if (ENABLE_PROJECT_LOGGER == ENABLED)

/* ************************************************************************************ */
/* * Public Defines                                                                   * */
/* ************************************************************************************ */

/**
 * @brief Register the debug configuration for a module.
 *
 * @param[in] _level  Debug level assigned to the module.
 * @param[in] _name   Name assigned to the module.
 */
#define MODULE_DEBUG_REGISTER(_level, _name)              \
    static const uint8_t _DEBUG_LEVEL = (_level);         \
    static const char *_DEBUG_NAME = #_name;

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

/**
 * @brief Internal debug print macro.
 *
 * @param[in] _level  Required debug level.
 * @param[in] _tag    Debug message tag.
 * @param[in] ...     Arguments passed to printf().
 */
#define DEBUG_PRINT(_level, _tag, ...)                                                   \
    do                                                                                   \
    {                                                                                    \
        if (_DEBUG_LEVEL >= (_level))                                                    \
        {                                                                                \
            printf("[%s][%s] %s:%d %s() - ",                                             \
                   _DEBUG_NAME,                                                          \
                   (_tag),                                                               \
                   __FILE__,                                                             \
                   __LINE__,                                                             \
                   __func__);                                                            \
            printf(__VA_ARGS__);                                                         \
            printf("\r\n");                                                              \
        }                                                                                \
    } while (0);

/* ************************************************************************************ */
/* * Debug Prints                                                                     * */
/* ************************************************************************************ */

/**
 * @brief Print an error message.
 *
 * Error messages are always displayed when the module debug level
 * allows error messages.
 *
 * @param[in] ... Arguments passed to printf().
 */
#define PRINT_E(...) \
    DEBUG_PRINT(DEBUG_LEVEL_E, "E", __VA_ARGS__)

/**
 * @brief Print a warning message.
 *
 * @param[in] ... Arguments passed to printf().
 */
#define PRINT_W(...) \
    DEBUG_PRINT(DEBUG_LEVEL_W, "W", __VA_ARGS__)

/**
 * @brief Print an informational message.
 *
 * @param[in] ... Arguments passed to printf().
 */
#define PRINT_I(...) \
    DEBUG_PRINT(DEBUG_LEVEL_I, "I", __VA_ARGS__)

/**
 * @brief Print a debug message.
 *
 * @param[in] ... Arguments passed to printf().
 */
#define PRINT_D(...) \
    DEBUG_PRINT(DEBUG_LEVEL_D, "D", __VA_ARGS__)

/* TODO: Add debug prints. */

#endif

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_OUTPUT_H__ */

/* -- End of file -- */