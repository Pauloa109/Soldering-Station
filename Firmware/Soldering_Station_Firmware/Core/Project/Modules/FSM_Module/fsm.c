/** ********************************************************************************** **/
/** * @file      fsm.c                                                               * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            fsm.c.                                                              * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      03/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 09/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* Include header file. */
#include "fsm.h"

/* Include UI module. */
#include "Ui.h"

/* TODO: Add includes. */


/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

#ifdef FSM_DEBUG_LEVEL
    DEBUG_LEVEL_REGISTER(FSM_DEBUG_LEVEL)
#else 
    DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)
#endif 

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

/* TODO: Add defines. */

/* ************************************************************************************ */
/* * Private Typedefs                                                                 * */
/* ************************************************************************************ */

/* TODO: Add typedefs. */

/* ************************************************************************************ */
/* * Private Enumerations                                                             * */
/* ************************************************************************************ */

/* TODO: Add enumerations. */

/* ************************************************************************************ */
/* * Private Structures                                                               * */
/* ************************************************************************************ */

/* TODO: Add structures. */

/* ************************************************************************************ */
/* * Private Flags                                                                    * */
/* ************************************************************************************ */

/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */

/* Initialized falg. */
static bool g_initialized = false;

#define GENERATE_STATE_HANDLER_ARRAY(STATE)    FSM_##STATE##_handler,                     
    static ptr_fsm_state_handler state_array[] =                                         \
        { FOREACH_STATE(GENERATE_STATE_HANDLER_ARRAY) };

/* FSM struct. */
static st_fsm fsm =
{
    .current_state  =  init_state,
    .stateHandler   =  state_array,
    .errorHandler   =  FSM_error_state_handler
};
/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET FSM_Initialize(void)
{
    if (CHECK_PTR(fsm.stateHandler))
    {
        PRINT_E("[FSM] no state handler defined.");
        return -RET_NOT_INITIALIZED;
    }

    else if (CHECK_PTR(fsm.errorHandler))
    {
        PRINT_E("[FSM] no error state handler defined.");
        return -RET_NOT_INITIALIZED;
    }

    g_initialized = true;

    return RET_INITIALIZED;
}

et_RET FSM_EncodeFSM(void)
{
    if (CHECK_INITIALIZED(g_initialized))
    {
        PRINT_E("FSM not initialized");
        return -RET_NOT_OK;
    }

    if(CHECK_PTR(fsm.stateHandler[fsm.current_state]))
    {
        PRINT_E("[FSM] null state handler.");
        return RET_NULL_PTR;
    }

    fsm.current_state = fsm.stateHandler[fsm.current_state]();

    return RET_OK;
}

/* TODO: Add private functions. */

/* -- End of file -- */
