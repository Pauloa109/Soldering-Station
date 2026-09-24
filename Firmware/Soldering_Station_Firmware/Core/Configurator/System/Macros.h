/** ********************************************************************************** **/
/** * @file      Macros.h                                                            * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Macros.h.                                                           * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      03/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Macros                                                                    * */
/* ************************************************************************************ */

#define CHECK_INITIALIZED(_init_flag)                                                    \
    (_init_flag == true)                                                               
                                                                                  

#define CHECK_PTR(_ptr)                                                                  \
    (_ptr == NULL)                                                                     
 
#define CONVERT_HEXARRAY_TO_MUM
/* TODO: Add macros. */


#ifdef __cplusplus
}
#endif

#endif /* __MACROS_H__ */

/* -- End of file -- */
