/** ********************************************************************************** **/
/** * @file      Ui.h                                                                * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Ui.h.                                                               * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __UI_H__
#define __UI_H__

#include "Returns.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include UI module defines. */
#include "Ui_defines.h"

/* Include UI module typpes. */
#include "Ui_types.h"

/* Include UI module inputs. */
#include "Ui_inputs.h"

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

/* TODO: Add enumerations. */

/* ************************************************************************************ */
/* * Public Structures                                                                * */
/* ************************************************************************************ */

/* TODO: Add structures. */

/* ************************************************************************************ */
/* * Public Flags                                                                     * */
/* ************************************************************************************ */

/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Public Constant Variables                                                        * */
/* ************************************************************************************ */

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Public Global Variables                                                          * */
/* ************************************************************************************ */

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Public Macros                                                                    * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */


/**
 * @brief   Ui initialize function.
 *
 * @param  None.
 *
 * @retval  RET_OK      Initialization successful.
 * @retval  Other       See @ref et_RET.
 */
et_RET UI_Initialize(void);

#define GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_PROTOTYPE(_name, ...)                       \
    /**                                                                                  \
     * @brief  Function to get the _name input state.                                    \
     *                                                                                   \
     * @param  None.                                                                     \
     *                                                                                   \
     * @return Return the state of the button.                                           \
     * @retval BUTTON_PRESSED   if there is a pressed event logged.                      \
     * @retval BUTTON_UNPRESSED if there is no new press event logged.                   \
     */                                                                                  \
    uint8_t UI_##_name##_get_logged_state(void);
FOREACH_BUTTON(GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_PROTOTYPE)

#define GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_PROTOTYPE(_name, ...)                       \
    /**                                                                                  \
     * @brief  Function to set the logged _name input state.                             \
     *                                                                                   \
     * @param  None.                                                                     \
     *                                                                                   \
     * @return None.                                                                     \
     */                                                                                  \
    void UI_##_name##_set_logged_state(void);
FOREACH_BUTTON(GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_PROTOTYPE)

#define GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_PROTOTYPE(_name, ...)                     \
    /**                                                                                  \
     * @brief  Function to clear the logged _name input state.                           \
     *                                                                                   \
     * @param  None.                                                                     \
     *                                                                                   \
     * @return None.                                                                     \
     */                                                                                  \
    void UI_##_name##_clear_logged_state(void);
FOREACH_BUTTON(GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_PROTOTYPE)

/* TODO: Add public function prototypes. */

#ifdef __cplusplus
}
#endif

#endif /* __UI_H__ */

/* -- End of file -- */
