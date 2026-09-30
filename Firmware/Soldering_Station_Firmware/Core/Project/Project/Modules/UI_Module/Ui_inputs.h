/** ********************************************************************************** **/
/** * @file      Ui_inputs.h                                                         * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Ui_inputs.h.                                                        * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      09/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __UI_INPUTS_H__
#define __UI_INPUTS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* Include UI module defines. */
#include "Ui_defines.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * GUI's Pin Table                                                                  * */
/* ************************************************************************************ */

/**
  * @brief Macro to automatically generate all the input related funcs.
  */
#define FOREACH_BUTTON(BUTTON)                                                           \
/*  BUTTON(PIN NAME         |   PIN NUMBER                |   PIN PORT)               */ \
    BUTTON(iron_tilt_sen    ,   IRON_TILTI_SENSOR_PIN     ,   IRON_TILTI_SENSOR_PORT)    \
    BUTTON(heat_gun_sen     ,   HEAT_GUN_MAG_SENSOR_PIN   ,   HEAT_GUN_MAG_SENSOR_PORT)  \
    BUTTON(vaccum_pump_trg  ,   VACCUM_PUMP_TRIGGER_PIN   ,   VACCUM_PUMP_TRIGGER_PORT)  \
    BUTTON(zero_croos_sen   ,   ZERO_CROSS_PIN            ,   ZERO_CROSS_PORT)           \
    BUTTON(b1_but           ,   MACRO_B1_PIN              ,   MACRO_B1_PORT)             \
    BUTTON(b2_but           ,   MACRO_B2_PIN              ,   MACRO_B2_PORT)             \
    BUTTON(b3_but           ,   MACRO_B3_PIN              ,   MACRO_B3_PORT)             \
    BUTTON(encoder_c_but    ,   ENCODER_C_PIN             ,   ENCODER_C_PORT)    

//    BUTTON(encoder_b_but    ,   ENCODER_B_PIN             ,   ENCODER_B_PORT)          \
//    BUTTON(encoder_a_but    ,   ENCODER_A_PIN             ,   ENCODER_A_PORT)          \

    /* TODO: Add defines. */

#ifdef __cplusplus
}
#endif

#endif /* __UI_INPUTS_H__ */

/* -- End of file -- */
