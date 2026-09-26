/** ********************************************************************************** **/
/** * @file      Ui.c                                                                * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            Ui.c.                                                               * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 25/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

#include "Returns.h"
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
#include "st7789_defines.h"
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

#define EDGE                (   5   )

#define MACRO_BAR_THICKNESS (   40  )

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

static uint8_t g_encoder_pressed = ENCODER_NOT_ROTATED;

#define GENERATE_BUTTON_VARIABLE(_name, ...)                                             \
    static uint8_t g_##_name##_pressed = BUTTON_UNPRESSED;
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

static st_UI_Config st_ui_conf = UI_default_config;

static bool g_initialized = false;

static uint8_t g_selected_channel = 0;

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */



/* TODO: Add macros. */

/* ************************************************************************************ */
/* * ISR Functions                                                                    * */
/* ************************************************************************************ */

et_RET UI_encoder_a_but_ISR(void)
{
    if (st_ui_conf.Get_Pin(ENCODER_B_PIN, ENCODER_B_PORT))
    {
        g_encoder_pressed = ENCODER_ROTATED_RIGHT;
    }

    else 
    {
        g_encoder_pressed = ENCODER_ROTATED_LEFT;
    }

    return RET_OK;
}

/* TODO: Add ISR functions. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET UI_Initialize(void)
{
    RET_REGISTER(ret);

    PRINT_I("[UI] Initializing the UI module");

    st_ui_conf.Display_Init();
    
    g_initialized = true;

    ret = UI_Draw_IntroScreen();

    if (CHECK_RET_ERROR(ret))
    {
        return -RET_NOT_OK;
    }

    PRINT_I("[UI] UI initialized");

    return RET_INITIALIZED;
}

et_RET UI_Draw_IntroScreen(void)
{
    uint8_t i;

    uint16_t xposition = 0;
    uint16_t yposition = 0;

    if (CHECK_INITIALIZED(g_initialized))
    {
        return -RET_NOT_INITIALIZED;
    }

    /* Clear the full screen. */
    st_ui_conf.Display_FillColour(0, 0, 319, 239, BLACK);

    UI_Refresh_SelectedChannel();

    xposition = GET_MIDDLE_OFFSET(ST7789_WIDTH,
                      (sizeof(intro_buff) - 1) * Font_16x26.width);

    i = 0;

    while (intro_buff[i])
    {
        st_ui_conf.Display_DrawChar(
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

    xposition = GET_MIDDLE_OFFSET(((ST7789_WIDTH / 2) - EDGE),
                                  (sizeof(iron_buff) - 1) * Font_16x26.width);

    yposition = GET_MIDDLE_OFFSET(ST7789_HEIGHT - MACRO_BAR_THICKNESS - EDGE- EDGE, 
                                  Font_16x26.width);

    
    yposition += MACRO_BAR_THICKNESS + EDGE;
    
    i = 0;
    
    while (iron_buff[i])
    {
        st_ui_conf.Display_DrawChar(
            xposition,
            yposition,
            iron_buff[i],
            Font_16x26,
            CYAN,
            BLACK
        );

        xposition += Font_16x26.width;
        i++;
    }

    xposition = GET_MIDDLE_OFFSET(((ST7789_WIDTH / 2) - EDGE),
                                  (sizeof(gun_buff) - 1) * Font_16x26.width);

    xposition += (ST7789_WIDTH / 2) + EDGE;

    i = 0;
    
    while (gun_buff[i])
    {
        st_ui_conf.Display_DrawChar(
            xposition,
            yposition,
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

et_RET UI_Refresh_SelectedChannel()
{
    if (UI_encoder_but_get_logged_state() == ENCODER_ROTATED_RIGHT)
    {
        g_selected_channel++;
    }

    else if (UI_encoder_but_get_logged_state() == ENCODER_ROTATED_LEFT)
    {
        g_selected_channel--;
    }

    g_selected_channel &= 0x1;
    UI_encoder_but_clear_logged_state();

    if (!g_selected_channel)
    {
        st_ui_conf.Display_Draw_Rectangle(0 + EDGE, 
                                    MACRO_BAR_THICKNESS + EDGE, 
                                    (ST7789_WIDTH / 2) - EDGE, 
                                    ST7789_HEIGHT - 1 - EDGE, 
                                    CYAN);

        st_ui_conf.Display_Draw_Rectangle((ST7789_WIDTH / 2) + EDGE, 
                                        MACRO_BAR_THICKNESS + EDGE, 
                                        ST7789_WIDTH - EDGE, 
                                        ST7789_HEIGHT - 1 - EDGE, 
                                        WHITE);
    }

    else
    {
        st_ui_conf.Display_Draw_Rectangle(0 + EDGE, 
                                    MACRO_BAR_THICKNESS + EDGE, 
                                    (ST7789_WIDTH / 2) - EDGE, 
                                    ST7789_HEIGHT - 1 - EDGE, 
                                    WHITE);

        st_ui_conf.Display_Draw_Rectangle((ST7789_WIDTH / 2) + EDGE, 
                                        MACRO_BAR_THICKNESS + EDGE, 
                                        ST7789_WIDTH - EDGE, 
                                        ST7789_HEIGHT - 1 - EDGE, 
                                        CYAN);
    }

    return RET_OK;
}

et_RET UI_Draw_IronScreen(void)
{
    char m1[] = "M1";
    char m2[] = "M2";    

    uint8_t i = 0;
    uint16_t x_position = 0;

    if (CHECK_INITIALIZED(g_initialized))
    {
        return -RET_NOT_INITIALIZED;
    }

    /* Clear the full screen. */
    st_ui_conf.Display_FillColour(0, 0, 319, 239, BLACK);

    st_ui_conf.Display_FillColour(EDGE,
                                  EDGE,
                                  MACRO_BAR_THICKNESS, 
                                  ST7789_HEIGHT - EDGE, 
                                  CYAN);

    x_position = GET_MIDDLE_OFFSET(MACRO_BAR_THICKNESS, 
                                   (sizeof(m1) - 1) * Font_11x18.width);

    x_position += EDGE;

    while (m1[i])
    {


        st_ui_conf.Display_DrawChar(
                                x_position,
                                100,
                                m1[i],
                                Font_11x18,
                                BLACK,
                                CYAN
                            );

        x_position += Font_11x18.width;
        i++;
    }

    return RET_OK;
}

#define GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                \
    void UI_##_name##_clear_logged_state(void)                                           \
    {                                                                                    \
        g_##_name##_pressed = BUTTON_UNPRESSED;                                          \
    }
FOREACH_BUTTON(GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION)

/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Get/Set Functions                                                                * */
/* ************************************************************************************ */

uint8_t UI_encoder_but_get_logged_state(void)
{
    return g_encoder_pressed; 
}

void UI_encoder_but_clear_logged_state(void)
{
    g_encoder_pressed = ENCODER_NOT_ROTATED; 
}

uint8_t UI_Get_SelectedChannel()
{
    return g_selected_channel;
}

#define GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                  \
    uint8_t UI_##_name##_get_logged_state(void)                                          \
    {                                                                                    \
        return g_##_name##_pressed;                                                      \
    }
FOREACH_BUTTON(GENERATE_BUTTON_GET_LOGGEDSTATE_FUNC_IMPLEMENTATION)

#define GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                  \
    void UI_##_name##_set_logged_state(void)                                             \
    {                                                                                    \
        g_##_name##_pressed = BUTTON_PRESSED;                                            \
    }
FOREACH_BUTTON(GENERATE_BUTTON_SET_LOGGEDSTATE_FUNC_IMPLEMENTATION)

uint8_t UI_Set_BuzzerState(uint8_t state)
{
    st_ui_conf.Set_Pin(BUZZER_PIN, BUZZER_PORT, state);
}

/* TODO: Add Get/Set functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

/* TODO: Add private functions. */

/* -- End of file -- */
