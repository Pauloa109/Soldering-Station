/** ********************************************************************************** **/
/** * @file      fsm_module_types.h                                                  * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            fsm_module_types.h.                                                 * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.1                                                              * **/
/** *                                                                                * **/
/** * Last modified on 09/09/2026                                                    * **/
/** ********************************************************************************** **/
#ifndef __FSM_MODULE_TYPES_H__
#define __FSM_MODULE_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/*  Fsm States  */
#include "fsm_states.h"

/* TODO: Add includes. */


/* ************************************************************************************ */
/* * Public Typedefs                                                                  * */
/* ************************************************************************************ */

/** 
  * @brief  State Handler Function Pointer.  
  */
typedef et_FSM_state (*ptr_fsm_state_handler)(void);

/* TODO: Add typedefs. */


/* ************************************************************************************ */
/* * Public Structures                                                                * */
/* ************************************************************************************ */

/** 
  * @brief  FSM main struct definition. 
  */
typedef struct
{
  et_FSM_state           current_state;

  ptr_fsm_state_handler *stateHandler;
  ptr_fsm_state_handler  errorHandler;

} st_fsm;

/* TODO: Add structures. */


#ifdef __cplusplus
}
#endif

#endif /* __FSM_MODULE_TYPES_H__ */

/* -- End of file -- */
