/** ********************************************************************************** **/
/** * @file      fsm_states.h                                                        * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            fsm_states.h.                                                       * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 07/10/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __FSM_STATES_H__
#define __FSM_STATES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Include Core. */
#include "Core_Include.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Public Defines                                                                   * */
/* ************************************************************************************ */

/** @brief  State table. */
#define FOREACH_STATE(STATE)                                                             \
    STATE(init_state)                                                                    \
    STATE(idle_state)                                                                    \
    STATE(iron_state)                                                                    \
    STATE(gun_state)                                                                     \
    STATE(error_state)                       

/* TODO: Add defines. */


/* ************************************************************************************ */
/* * Public Typedefs                                                                  * */
/* ************************************************************************************ */

/* TODO: Add typedefs. */

/* ************************************************************************************ */
/* * Public Enumerations                                                              * */
/* ************************************************************************************ */

#define GENERATE_ENUM(NAME) NAME,

/** @brief FSM states enum. */
typedef enum
{
    FOREACH_STATE(GENERATE_ENUM)
    NUMBER_STATES

} et_FSM_state;

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
 * @brief  State handler function prototypes definition.
 */
#define GENERATE_STATE_HANDLER(STATE) \
    et_FSM_state FSM_##STATE##_handler(void);

FOREACH_STATE(GENERATE_STATE_HANDLER)

/**
 * @brief Draw a three-digit seven-segment temperature value.
 * @param temperature Value to display; values above 999 are clamped to 999.
 * @param x,y Top-left position of the first digit.
 * @param digit_width,digit_height Size of each digit in pixels.
 * @param segment_thickness Thickness of each segment in pixels.
 * @param digit_spacing Horizontal spacing between digits in pixels.
 * @param foreground_color Color used by lit segments.
 * @param background_color Color used by unlit segments.
 * @return true if the geometry fits the display and was drawn, otherwise false.
 */
bool Display_Temperature(uint16_t temperature,
                         uint16_t x,
                         uint16_t y,
                         uint16_t digit_width,
                         uint16_t digit_height,
                         uint16_t segment_thickness,
                         uint16_t digit_spacing,
                         uint16_t foreground_color,
                         uint16_t background_color);

/**
 * @brief Draw a degree-Celsius icon using caller-supplied geometry.
 * @param x,y Top-left position of the icon.
 * @param width,height Overall icon dimensions in pixels.
 * @param thickness Segment and degree-ring thickness in pixels.
 * @param spacing Gap between the degree ring and the C.
 * @param foreground_color Color used by the icon.
 * @param background_color Color used to clear its area.
 * @return true if the geometry fits the display and was drawn, otherwise false.
 */
bool Display_TemperatureUnit(uint16_t x,
                             uint16_t y,
                             uint16_t width,
                             uint16_t height,
                             uint16_t thickness,
                             uint16_t spacing,
                             uint16_t foreground_color,
                             uint16_t background_color);

#ifdef __cplusplus
}
#endif


#endif /* __FSM_STATES_H__ */

/* -- End of file -- */
