/** ********************************************************************************** **/
/** * @file      Return_types.h                                                      * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Return_types.h.                                                     * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      28/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 28/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __RETURN_TYPES_H__
#define __RETURN_TYPES_H__

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Enumerations                                                              * */
/* ************************************************************************************ */

/**
 *   @brief Indicates all the return values that can be used in this 
 *          project.
 *
 *   @note  Negative returns are reserved for errors.
 */
typedef enum 
{
/******************************** General *********************************/   
    /* Indicates that the operation completed successfully. */
    RET_OK = 0,
    /* Indicates something went wrong. */
    RET_NOT_OK,
    /* Indicates that the operation initialized successfully. */
    RET_INITIALIZED,
    /* Indicates that the operation failed to initialize. */
    RET_NOT_INITIALIZED,
    /* Indicates a null ptr*/
    RET_NULL_PTR,
    /* ... */

/****************************** Communications ****************************/ 
    /* ... */

} et_RET;

/* TODO: Add enumerations. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __RETURN_TYPES_H__ */

/* -- End of file -- */
