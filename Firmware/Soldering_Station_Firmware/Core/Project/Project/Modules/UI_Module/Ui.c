/** ********************************************************************************** **/
/** * @file      Ui.c                                                                * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            Ui.c.                                                               * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 07/10/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Include header file.*/
#include "Ui.h"

#include "Core/Project/Project/Modules/UI_Module/Ui_defines.h"
#include "Ui_configs.h"

/* Include module configuration. */
#include "Core_Include.h"


#include "fonts.h"
#include "sd_card.h"
#include "tim.h"


/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */
#if (PROJECT_ENABLE_LOGGER == ENABLED)

    #if UI_DEBUG_LEVEL

        DEBUG_LEVEL_REGISTER(UI_DEBUG_LEVEL)

    #else 

        #warning "No debug level ser for the UI module"

        DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

    #endif

#else 

    MODULE_DEBUG_REGISTER(DEBUG_LEVEL_N, UI_module)

#endif


/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

#define MACRO_BAR_THICKNESS (   40  )

#define NO_MACRO_PRESSED    (   0   )

#define MACRO_M1_PRESSED    (   1   )

#define MACRO_M2_PRESSED    (   2   )
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
static uint8_t g_b1_but_pressed  = BUTTON_UNPRESSED;
static uint8_t g_b2_but_pressed  = BUTTON_UNPRESSED;

static uint8_t macro_flg = NO_MACRO_PRESSED;

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

static FATFS ffts;

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

et_RET UI_UI_b1_but_ISR(void)
{
    HAL_TIM_Base_Start_IT(&htim3);

    macro_flg = MACRO_M1_PRESSED;

    return RET_OK;
}

et_RET UI_UI_b2_but_ISR(void)
{
    HAL_TIM_Base_Start_IT(&htim3);

    macro_flg = MACRO_M2_PRESSED;

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
    
    ret = SD_Mount(&ffts);
    if (CHECK_RET_ERROR(ret))
    {
        return -RET_NOT_OK;
    }

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
            BLACK);

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
            BLACK);

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
            BLACK);

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

void UI_DrawMacroValue(uint16_t x, uint16_t y, uint16_t value)
{
    char value_text[5] = {' ', ' ', ' ', 'C', '\0'};
    const uint16_t text_width = 4U * Font_11x18.width;
    uint16_t text_x = x + (80U - text_width) / 2U;

    if (value > 999U)
    {
        value = 999U;
    }

    if (value >= 100U)
    {
        value_text[0] = (char)('0' + value / 100U);
    }
    if (value >= 10U)
    {
        value_text[1] = (char)('0' + (value / 10U) % 10U);
    }
    value_text[2] = (char)('0' + value % 10U);

    for (uint8_t index = 0U; index < 4U; index++)
    {
        st_ui_conf.Display_DrawChar(text_x + index * Font_11x18.width,
                                    y,
                                    value_text[index],
                                    Font_11x18,
                                    BLACK,
                                    CYAN);
    }
}

et_RET UI_Draw_IronScreen(uint16_t macro_m1, uint16_t macro_m2)
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

    st_ui_conf.Display_FillColour(50,
                                ST7789_HEIGHT - 2 * EDGE - 50,
                                130,
                                ST7789_HEIGHT - 2 * EDGE,
                                CYAN);

    st_ui_conf.Display_FillColour(ST7789_WIDTH - 50 - 80,
                                      ST7789_HEIGHT - 2 * EDGE - 50,
                                      ST7789_WIDTH - 50,
                                      ST7789_HEIGHT - 2 * EDGE,
                                      CYAN);

    x_position = GET_MIDDLE_OFFSET(80, 
                                   (sizeof(m1) - 1) * Font_11x18.width);

    while (m1[i])
    {
        st_ui_conf.Display_DrawChar(x_position + 50,
                                    ST7789_HEIGHT - 2 * EDGE - 50 + EDGE,
                                    m1[i],
                                    Font_11x18,
                                    BLACK,
                                    CYAN);
        
        st_ui_conf.Display_DrawChar(x_position + ST7789_WIDTH - 50 - 80,
                                    ST7789_HEIGHT - 2 * EDGE - 50 + EDGE,
                                    m2[i],
                                    Font_11x18,
                                    BLACK,
                                    CYAN);

        x_position += Font_11x18.width;

        i++;
    }

    UI_DrawMacroValue(50U,
                      ST7789_HEIGHT - 2U * EDGE - 50U + 27U,
                      macro_m1);
    UI_DrawMacroValue(ST7789_WIDTH - 50U - 80U,
                      ST7789_HEIGHT - 2U * EDGE - 50U + 27U,
                      macro_m2);

    return RET_OK;
}

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

uint8_t UI_b1_but_get_logged_state(void)
{
    return g_b1_but_pressed; 
}

void UI_b1_but_clear_logged_state(void)
{
    g_b1_but_pressed = BUTTON_UNPRESSED; 
}

uint8_t UI_b2_but_get_logged_state(void)
{
    return g_b2_but_pressed; 
}

void UI_b2_but_clear_logged_state(void)
{
    g_b2_but_pressed = BUTTON_UNPRESSED; 
}

uint8_t UI_Get_SelectedChannel()
{
    return g_selected_channel;
}

uint8_t UI_Set_BuzzerState(uint8_t state)
{
    st_ui_conf.Set_Pin(BUZZER_PIN, BUZZER_PORT, state);
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

#define GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION(_name, ...)                \
    void UI_##_name##_clear_logged_state(void)                                           \
    {                                                                                    \
        g_##_name##_pressed = BUTTON_UNPRESSED;                                          \
    }
FOREACH_BUTTON(GENERATE_BUTTON_CLEAR_LOGGEDSTATE_FUNC_IMPLEMENTATION)

/* TODO: Add Get/Set functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

    //HAL_TIM_Base_Stop_IT(&htim3);
    // __HAL_TIM_SET_COUNTER(&htim3, 0);
    //HAL_TIM_Base_Start_IT(&htim3);

    //UI_Set_BuzzerState(BUZZER_ON);

    switch (GPIO_Pin) 
    {
        case (1 << ENCODER_A_PIN):
        UI_encoder_a_but_ISR();
        break;

        case (1 << ENCODER_C_PIN):
        UI_encoder_c_but_set_logged_state();
        break;

        case (1 << MACRO_B1_PIN):
        //UI_b1_but_set_logged_state();
        UI_UI_b1_but_ISR();
        break;

        case (1 << MACRO_B2_PIN):
        //UI_b2_but_set_logged_state();
        UI_UI_b2_but_ISR();
        break;

        /*case (1 << MACRO_B3_PIN):
        UI_b3_but_set_logged_state();
        break;*/

        case (1 << IRON_TILTI_SENSOR_PIN):
        UI_iron_tilt_sen_get_logged_state();
        break;

        case (1 << HEAT_GUN_MAG_SENSOR_PIN):
        UI_heat_gun_sen_get_logged_state();
        break;

        case (1 << VACCUM_PUMP_TRIGGER_PIN):
        UI_vaccum_pump_trg_set_logged_state();
        break;

        case (1 << ZERO_CROSS_PIN):
        UI_zero_croos_sen_set_logged_state();
        break;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_TIM_Base_Stop_IT(htim);
        __HAL_TIM_SET_COUNTER(htim, 0);

        if (macro_flg == MACRO_M1_PRESSED)
        {
            if(st_ui_conf.Get_Pin(MACRO_B1_PIN, MACRO_B1_PORT) == BUTTON_PRESSED)
            {
                g_b1_but_pressed = BUTTON_LONG_PRESSED;
            }

            else 
            {
                g_b1_but_pressed = BUTTON_PRESSED;  
            }
        }

        else if (macro_flg == MACRO_M2_PRESSED)
        {
            if(st_ui_conf.Get_Pin(MACRO_B2_PIN, MACRO_B2_PORT) == BUTTON_PRESSED)
            {
                g_b2_but_pressed = BUTTON_LONG_PRESSED;
            }

            else 
            {
                g_b2_but_pressed = BUTTON_PRESSED;  
            }
        }

        macro_flg = NO_MACRO_PRESSED;
    }
}

/* TODO: Add private functions. */

/* -- End of file -- */
