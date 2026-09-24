/** ********************************************************************************** **/
/** * @file      Ui.c                                                                * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            Ui.c.                                                               * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

#include "Ui_defines.h"
#include "Ui_configs.h"
#include "Ui_types.h"

/* Include header file.*/
#include "Ui.h"

/* Include module configuration. */

#include "Core_Include.h"


#include "fonts.h"
#include "sd_card.h"
#include "st7789.h"
#include <stdint.h>

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

#ifdef UI_DEBUG_LEVEL
    #warning "No debug level defined\r\n".
    DEBUG_LEVEL_REGISTER  (UI_DEBUG_LEVEL)
#else 
    DEBUG_LEVEL_REGISTER  (DEBUG_LEVEL_D)
#endif

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

#define EDGE                ( 5 )

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

#define GENERATE_BUTTON_VARIABLE(_name, ...)                                             \
    static uint8_t _name##_pressed = BUTTON_UNPRESSED;
FOREACH_BUTTON(GENERATE_BUTTON_VARIABLE)

/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */

const char intro_buff[] = "Soldering Station";
const char iron_buff[]  = "Iron";
const char gun_buff[]   = "Heat Gun";

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */

static st_UI_Config g_ui_conf = UI_default_config;

static bool g_initialized = false;

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/**                                                                                  
 * @brief  Function to draw the intro screen.                                    
 *                                                                                   
 * @param  None.                                                                     
 *                                                                                   
 * @return Indicates if everything went ok.                                           
 * @retval RET_OK               All ok.                      
 * @retval RET_NOT_INITIALIZED  Muduloe not initialized.                   
 */  
static et_RET UI_Draw_IntroScreen(void);

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET UI_Initialize(void)
{
    PRINT_I("[UI] Initializing the UI module");

    g_ui_conf.Display_Init();
    
    g_initialized = true;

    UI_Draw_IntroScreen();

    PRINT_I("[UI] UI initialized");

    return RET_OK;
}

#define GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                  \
    uint8_t UI_##_name##_get_logged_state(void)                                          \
    {                                                                                    \
        return _name##_pressed;                                                          \
    }
FOREACH_BUTTON(GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_IMPLEMENTATION)

#define GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                  \
    void UI_##_name##_set_logged_state(void)                                             \
    {                                                                                    \
        _name##_pressed = BUTTON_PRESSED;                                                \
    }
FOREACH_BUTTON(GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_IMPLEMENTATION)

#define GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                \
    void UI_##_name##_clear_logged_state(void)                                           \
    {                                                                                    \
        _name##_pressed = BUTTON_UNPRESSED;                                              \
    }
FOREACH_BUTTON(GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION)

/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

static et_RET UI_Draw_IntroScreen(void)
{
    uint8_t size;
    uint8_t i;

    if ( !CHECK_INITIALIZED(g_initialized))
    {
        return -RET_NOT_INITIALIZED;
    }

    /* Clear the full screen. */
    g_ui_conf.Display_FillColour(0, 0, 319, 239, BLACK);

    g_ui_conf.Display_Draw_Rectangle(0 + EDGE, 
                                     40 + EDGE, 
                                     (ST7789_WIDTH / 2) - EDGE, 
                                     ST7789_HEIGHT - 1 - EDGE, 
                                     CYAN);

    g_ui_conf.Display_Draw_Rectangle((ST7789_WIDTH / 2) + EDGE, 
                                     40 + EDGE, 
                                     ST7789_WIDTH - EDGE, 
                                     ST7789_HEIGHT - 1 - EDGE, 
                                     CYAN);

    size = sizeof(intro_buff) - 1;
    uint16_t xposition = (ST7789_WIDTH - (size * Font_16x26.width)) / 2;
    i = 0;

    while (intro_buff[i])
    {
        g_ui_conf.Display_DrawChar(
            xposition,
            15,
            intro_buff[i],
            Font_16x26,
            CYAN,
            BLACK
        );

        xposition += Font_16x26.width;
        i++;
    }

    size = sizeof(iron_buff) - 1;
    xposition = (((ST7789_WIDTH / 2) - EDGE) - (size * Font_16x26.width)) / 2;
    i = 0;
    
    while (iron_buff[i])
    {
        g_ui_conf.Display_DrawChar(
            xposition,
            100,
            iron_buff[i],
            Font_16x26,
            CYAN,
            BLACK
        );

        xposition += Font_16x26.width;
        i++;
    }

    size = sizeof(gun_buff) - 1;
    xposition = (((ST7789_WIDTH / 2) - EDGE) - (size * Font_16x26.width)) / 2 +
                            (ST7789_WIDTH / 2) + EDGE;
    i = 0;
    
    while (gun_buff[i])
    {
        g_ui_conf.Display_DrawChar(
            xposition,
            100,
            gun_buff[i],
            Font_16x26,
            CYAN,
            BLACK
        );

        xposition += Font_16x26.width;
        i++;
    }

    return RET_OK;
}

/* TODO: Add private functions. */

/* -- End of file -- */
