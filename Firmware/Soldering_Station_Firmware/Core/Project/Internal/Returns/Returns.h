/** ********************************************************************************** **/
/** * @file      Returns.h                                                           * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Returns.h.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      26/08/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 28/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __RETURNS_H__
#define __RETURNS_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include Return Enum. */
#include "Return_types.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

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

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __RETURNS_H__ */

/* -- End of file -- */

