/** ********************************************************************************** **/
/** * @file      Debug.h                                                             * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Debug.h.                                                            * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      25/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __DEBUG_H__
#define __DEBUG_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

#include <stdio.h>

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

#define DEBUG_NAME_REGISTER(_name)                                                       \
    *_DEBUG_NAME = #_name;

#define DEBUG_LEVEL_REGISTER(_level)                                                     \
    static const uint8_t _DEBUG_LEVEL = _level;                                          \
    static const char *_DEBUG_NAME = NULL;

#define MODULE_DEBUG_REGISTER(_level, _name)                                             \
    DEBUG_LEVEL_REGISTER(_level);                                                        \
    DEBUG_NAME_REGISTER(_name);  

/* TODO: Add defines. */

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
/* * Debug Prints                                                                     * */
/* ************************************************************************************ */

/**
*    @brief  This macro is used to print error messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_E( ... )                                                                  \
    do                                                                                  \
    {                                                                                   \
        if ((_DEBUG_LEVEL) >= DEBUG_LEVEL_E)                                            \
        {                                                                               \
            if (_DEBUG_NAME != NULL)                                                    \
            {                                                                           \
                printf("[%s][E] : \r\n", _DEBUG_NAME);                                  \
                printf("%s at %s : %d() \r\n",                                          \
                    __FILE__,                                                           \
                    __func__ ,                                                          \
                    __LINE__ );                                                         \
            }                                                                           \
                                                                                        \
            else                                                                        \
            {                                                                           \
                printf("[E] : ");                                                       \
                printf("%s at %s : %d() \r\n",                                          \
                    __FILE__,                                                           \
                    __func__ ,                                                          \
                    __LINE__ );                                                         \
            }                                                                           \
                                                                                        \
            printf( __VA_ARGS__ );                                                      \
            printf("\r\n");                                                             \
        }                                                                               \
    } while (0);


/**
*   @brief  This macro is used to print warning messages.
*   @param  _args_: Arguments to print
*/
#define PRINT_W( ... )                                                                  \
    do                                                                                  \
    {                                                                                   \
        if ((_DEBUG_LEVEL) >= DEBUG_LEVEL_W)                                            \
        {                                                                               \
            if (_DEBUG_NAME != NULL)                                                    \
            {                                                                           \
                printf("[%s][w] : \r\n", _DEBUG_NAME);                                  \
            }                                                                           \
                                                                                        \
            else                                                                        \
            {                                                                           \
                printf("[w] : ");                                                       \
            }                                                                           \
                                                                                        \
            printf( __VA_ARGS__ );                                                      \
            printf("\r\n");                                                             \
    } while (0);


/**
*    @brief  This macro is used to print informational messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_I( ... )                                                                  \
    do                                                                                  \
    {                                                                                   \
        if ((_DEBUG_LEVEL) >= DEBUG_LEVEL_I)                                            \
        {                                                                               \
            if (_DEBUG_NAME != NULL)                                                    \
            {                                                                           \
                printf("[%s][I] : \r\n", _DEBUG_NAME);                                  \
            }                                                                           \
                                                                                        \
            else                                                                        \
            {                                                                           \
                printf("[I] : ");                                                       \
            }                                                                           \
                                                                                        \
            printf( __VA_ARGS__ );                                                      \
            printf("\r\n");                                                             \
        }                                                                               \
    } while (0);


/**
*    @brief  This macro is used to print debug messages.
*    @param  _args_: Arguments to print
*/
#define PRINT_D( ... )                                                                  \
    do                                                                                  \
    {                                                                                   \
        if ((_DEBUG_LEVEL) >= DEBUG_LEVEL_I)                                            \
        {                                                                               \
            if (_DEBUG_NAME != NULL)                                                    \
            {                                                                           \
                printf("[%s][D] : \r\n", _DEBUG_NAME);                                  \
            }                                                                           \
                                                                                        \
            else                                                                        \
            {                                                                           \
                printf("[D] : ");                                                       \
            }                                                                           \
                                                                                        \
            printf( __VA_ARGS__ );                                                      \
            printf("\r\n");                                                             \
        }                                                                               \
    } while (0);    

/* TODO: Add debug prints. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H__ */

/* -- End of file -- */
