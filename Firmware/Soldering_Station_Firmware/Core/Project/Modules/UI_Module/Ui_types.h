/** ********************************************************************************** **/
/** * @file      Ui_types.h                                                          * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Ui_types.h.                                                         * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __UI_TYPES_H__
#define __UI_TYPES_H__

#include "st7789.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* TODO: Add includes. */


/* ************************************************************************************ */
/* * Public Typedefs                                                                  * */
/* ************************************************************************************ */

//Type for a function that sets the state of a GPIO pin
typedef void    (*t_GpioPin_Set)                    (uint16_t pin, 
                                                     uint32_t port, 
                                                     uint8_t state); 

//Type for a function that reads the state of a GPIO pin
typedef uint8_t (*t_GpioPin_Read)                   (uint16_t pin, 
                                                     uint32_t port);

//Type for a function that initializes the display
typedef void    (*t_Display_Init)                   (void); 

//Type for a function that draws an horizontal line
typedef void    (*t_Display_Draw_Horizontal_Line)   (uint16_t x, 
                                                     uint16_t y, 
                                                     uint16_t width, 
                                                     uint16_t color);

//Type for a function that draws a vertical line
typedef void    (*t_Display_Draw_Vertical_Line)     (uint16_t x, 
                                                     uint16_t y,
                                                     uint16_t height, 
                                                     uint16_t color);

//Type for a function that draws a rectangle
typedef void    (*t_Display_Draw_Rectangle)         (uint16_t x, 
                                                     uint16_t y, 
                                                     uint16_t width, 
                                                     uint16_t height, 
                                                     uint16_t color);

//Type for a function that draws text
typedef void    (*t_Display_Draw_Text)              (uint16_t x, 
                                                     uint16_t y, 
                                                     char ch, 
                                                     FontDef font, 
                                                     uint16_t color, 
                                                     uint16_t bgcolor);


//Type for a function that fills the screen with a colour
typedef void    (*t_Display_Fill_Colour)            (uint16_t xSta, 
                                                     uint16_t ySta, 
                                                     uint16_t xEnd, 
                                                     uint16_t yEnd, 
                                                     uint16_t color);

//Type for a function that fills the screen with a colour
typedef void    (*t_Display_Draw_RoundedRectangular) (uint16_t x,
                                                      uint16_t y,
                                                      uint16_t width,
                                                      uint16_t height,
                                                      uint16_t radius,
                                                      uint16_t color);


/* TODO: Add typedefs. */

/* ************************************************************************************ */
/* * Public Enumerations                                                              * */
/* ************************************************************************************ */

//Configuration struct definition
typedef struct{
    t_GpioPin_Set                       Set_Pin;                    
    t_GpioPin_Read                      Get_Pin;                   
    
    t_Display_Init                      Display_Init;
    t_Display_Draw_Horizontal_Line      Display_Draw_Horizontal_Line;
    t_Display_Draw_Vertical_Line        Display_Draw_Vertical_Line;
    t_Display_Draw_Rectangle            Display_Draw_Rectangle;
    t_Display_Draw_Text                 Display_DrawChar;

    t_Display_Fill_Colour               Display_FillColour;

    t_Display_Draw_RoundedRectangular   Display_Draw_RoundedRectangular;
    
} st_UI_Config;


#ifdef __cplusplus
}
#endif

#endif /* __UI_TYPES_H__ */

/* -- End of file -- */
