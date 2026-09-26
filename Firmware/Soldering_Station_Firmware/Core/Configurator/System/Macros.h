/** ********************************************************************************** **/
/** * @file      Macros.h                                                            * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Macros.h.                                                           * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      03/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __MACROS_H__
#define __MACROS_H__

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
/* * Public Macro Defines                                                             * */
/* ************************************************************************************ */

#define CHECK_INITIALIZED(_init_flag)                                                    \
    ((_init_flag) != true)                                                               
                                                                                  

#define CHECK_PTR(_ptr)                                                                  \
    (_ptr == NULL)                                                                     
 
/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Public Macro Functions                                                           * */
/* ************************************************************************************ */

/**
 * @brief Returns the offset required to center an object.
 *
 * @param _full_space      Total available space.
 * @param _occupied_space  Space occupied by the object.
 *
 * @return Offset from the beginning of the available space.
 */
static inline uint16_t GET_MIDDLE_OFFSET(uint16_t _full_space,
                           uint16_t _occupied_space)
{
    return (_full_space - _occupied_space) / 2U;
}


/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __MACROS_H__ */

/* -- End of file -- */
