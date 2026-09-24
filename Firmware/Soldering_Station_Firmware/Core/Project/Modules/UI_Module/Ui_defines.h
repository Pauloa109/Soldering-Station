/** ********************************************************************************** **/
/** * @file      Ui_defines.h                                                        * **/
/** * @brief     This file contains all the pin related defines of the Ui module     * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 18/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __UI_DEFINES_H__
#define __UI_DEFINES_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* */
#include "Proj.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* *  Pin related Defines                                                             * */
/* ************************************************************************************ */

#define BLACK      				0x0000
#define NAVY        			0x000F
#define DARKGREEN   			0x03E0
#define DARKCYAN    			0x03EF
#define MAROON      			0x7800
#define PURPLE      			0x780F
#define OLIVE       			0x7BE0
#define LIGHTGREY   			0xC618
#define DARKGREY    			0x7BEF
#define BLUE        			0x001F
#define GREEN       			0x07E0
#define CYAN        			0x07FF
#define RED         			0xF800
#define MAGENTA     			0xF81F
#define YELLOW      			0xFFE0
#define WHITE       			0xFFFF
#define ORANGE      			0xFD20
#define GREENYELLOW 			0xAFE5
#define PINK        			0xF81F

/* ************************************************************************************ */
/* *  Pin related Defines                                                             * */
/* ************************************************************************************ */

#define BUZZER_OFF                      (   GPIO_LOW   )
#define BUZZER_ON                       (   GPIO_HIGH  )

#define BUTTON_PRESSED                  (   GPIO_LOW   )
#define BUTTON_UNPRESSED                (   GPIO_HIGH  )

#define ENCODER_NOT_ROTATED             (   0   )
#define ENCODER_ROTATED_LEFT            (   1   )
#define ENCODER_ROTATED_RIGHT           (   2   )  


/* ************************************************************************************ */
/* * GUI's Pins Defines                                                               * */
/* ************************************************************************************ */

/* Buzzer pin defines. */
#define BUZZER_PIN                      (   1   )
#define BUZZER_PORT                     (   GPIO_PORTA   )

/* Display pins defines. */
#define DISPLAY_BACK_LIGHT_PIN          (   2   )
#define DISPLAY_BACK_LIGHT_PORT         (   GPIO_PORTA   )
#define DISPLAY_IQR_PIN                 (   13   )
#define DISPLAY_IQR_PPORT               (   GPIO_PORTC   )
/*#define DISPLAY_TOUCH_CS_PIN            (   14   )
#define DISPLAY_TOUCH_CS_PORT           (   GPIO_PORTC   )
#define DISPLAY_DC_PIN                  (   0   )
#define DISPLAY_DC_PORT                 (   GPIO_PORTB   )
#define DISPLAY_CS_PIN                  (   10   )
#define DISPLAY_CS_PORT                 (   GPIO_PORTB   )
#define DISPLAY_RST_PIN                 (   1   )
#define DISPLAY_RST_PORT                (   GPIO_PORTB   )*/

/* ADC pins defines. */
#define IRON_TMP_PIN                    (   3   )
#define IRON_TMP_PORT                   (   GPIO_PORTA   )
#define HEAT_GUN_TMP_PIN                (   4   )
#define HEAT_GUN_TMP_PORT               (   GPIO_PORTA   )

/* Input pins defines. */
#define IRON_TILTI_SENSOR_PIN           (   3   )
#define IRON_TILTI_SENSOR_PORT          (   GPIO_PORTB   )
#define HEAT_GUN_MAG_SENSOR_PIN         (   4   )
#define HEAT_GUN_MAG_SENSOR_PORT        (   GPIO_PORTB   )
#define VACCUM_PUMP_TRIGGER_PIN         (   5   )
#define VACCUM_PUMP_TRIGGER_PORT        (   GPIO_PORTB   )
#define ZERO_CROSS_PIN                  (   15   )
#define ZERO_CROSS_PORT                 (   GPIO_PORTA   )

/* Macro pins defines. */
#define MACRO_B1_PIN                    (   2   )
#define MACRO_B1_PORT                   (   GPIO_PORTB   )
#define MACRO_B2_PIN                    (   9   )
#define MACRO_B2_PORT                   (   GPIO_PORTB   )
#define MACRO_B3_PIN                    (   15   )
#define MACRO_B3_PORT                   (   GPIO_PORTC   )

/* Encoder pins defines. */
#define ENCODER_A_PIN                   (   8   )
#define ENCODER_A_PORT                  (   GPIO_PORTB   )
#define ENCODER_B_PIN                   (   7   )
#define ENCODER_B_PORT                  (   GPIO_PORTB   )
#define ENCODER_C_PIN                   (   6   )
#define ENCODER_C_PORT                  (   GPIO_PORTB   )

/* PWM pins defines. */
#define IRON_PWM_PIN                    (   8   )
#define IRON_PWM_PORT                   (   GPIO_PORTA   )
#define HEAT_GUN_PWM_PIN                (   11   )
#define HEAT_GUN_PWM_PORT               (   GPIO_PORTB   )
#define HEAT_GUN_FAN_PWM_PIN            (   9   )
#define HEAT_GUN_FAN_PWM_PORT           (   GPIO_PORTA   )
#define VACCUM_PUMP_PWM_PIN             (   10   )
#define VACCUM_PUMP_PWM_PORT            (   GPIO_PORTA   )

/* SDcard pins defines. */
#define SD_CS_PIN                       (   12   )
#define SD_CS_PORT                      (   GPIO_PORTB   )



#ifdef __cplusplus
}
#endif

#endif /* __UI_DEFINES_H__ */

/* -- End of file -- */


