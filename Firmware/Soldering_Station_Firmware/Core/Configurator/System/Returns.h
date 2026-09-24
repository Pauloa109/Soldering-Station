/** ********************************************************************************** **/
/** * @file      Returns.h                                                           * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Returns.h.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      26/08/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 19/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __RETURNS_H__
#define __RETURNS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Public Defines                                                                   * */
/* ************************************************************************************ */

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * Public Typedefs                                                                  * */
/* ************************************************************************************ */

/* TODO: Add typedefs. */

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
/* * Public Macros                                                                    * */
/* ************************************************************************************ */

/** 
 *   @brief  Register a return value
 *
 *   @param  _name: Name of the return value
*/
#define RET_REGISTER(_name)     \
    et_RET _name = RET_NOT_OK;
    
/**
 *   @brief  Check a return value and return if it is an error
 *
 *   @param  _ret: Return value to check
*/
#define CHECK_RET(_ret, ...)    \
    if (_ret < RET_OK)          \
    {                           \
        return _ret;            \
    }

/** 
 *   @brief  Check a return value
 *
 *   @param  _ret: Return value to check
*/
#define CHECK_RET_ERROR(_ret)   \
    ((_ret) < RET_OK)         


/* TODO: Add macros. */


#ifdef __cplusplus
}
#endif

#endif /* __RETURNS_H__ */

/* -- End of file -- */

