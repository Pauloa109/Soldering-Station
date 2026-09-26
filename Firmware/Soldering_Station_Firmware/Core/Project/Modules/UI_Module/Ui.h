/** ********************************************************************************** **/
/** * @file      Ui.h                                                                * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Ui.h.                                                               * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
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

/**                                                                                  
 * @brief  Function to draw the intro screen.                                    
 *                                                                                   
 * @param  None.                                                                     
 *                                                                                   
 * @return Indicates if everything went ok.                                           
 * @retval RET_OK               All ok.                      
 * @retval RET_NOT_INITIALIZED  Muduloe not initialized.                   
 */  
et_RET UI_Draw_IntroScreen(void);

et_RET UI_Refresh_SelectedChannel();

et_RET UI_Draw_IronScreen(void);

/**
 * @brief   Encoder Pin A ISR function.
 *
 * @param   None.
 *
 * @retval  RET_OK      Initialization successful.
 * @retval  Other       See @ref et_RET.
 */
et_RET UI_encoder_a_but_ISR(void);

/**                                                                                  \
 * @brief  Function to get the encoder state.                                        \
 *                                                                                   \
 * @param  None.                                                                     \
 *                                                                                   \
 * @return Return the state of the button.                                           \
 * @retval BUTTON_PRESSED   if there is a pressed event logged.                      \
 * @retval BUTTON_UNPRESSED if there is no new press event logged.                   \
 */   
uint8_t UI_encoder_but_get_logged_state(void);

/**                                                                                  \
 * @brief  Function to clear the logged _name input state.                           \
 *                                                                                   \
 * @param  None.                                                                     \
 *                                                                                   \
 * @return None.                                                                     \
 */   
void UI_encoder_but_clear_logged_state(void);


uint8_t UI_Get_SelectedChannel();

uint8_t UI_Set_BuzzerState(uint8_t state);

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
