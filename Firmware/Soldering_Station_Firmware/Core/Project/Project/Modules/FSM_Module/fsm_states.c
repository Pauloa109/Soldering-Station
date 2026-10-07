/** ********************************************************************************** **/
/** * @file      fsm_states.c                                                        * **/
/** * @brief     This file contains all the functions implementation or prototypes   * **/
/** *            of fsm_states.h.                                                    * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 07/10/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */


#include "Core/Project/Project/Modules/UI_Module/Ui_defines.h"
#include "Core_Include.h"

/* Inclue Header Fille. */
#include "fsm_states.h"

/* Include Ui Module. */
#include "Ui.h"

#include "adc.h"

#include "fonts.h"
#include "sd_card.h"
#include "st7789.h"
#include "tim.h"

#include "adc.h"
#include <stdbool.h>
#include <stdint.h>


/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

/* proportional Gain. */
#define KP      ( 1.0f )

/* Integrative Gain. */
#define KI      ( 0.2f )

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

static volatile uint8_t adc_new_val_flg = 0;
/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */

/* Variable that holds the segments' state for each number. */
static const uint8_t digit_segments[10] =
{
    0x3FU, 0x06U, 0x5BU, 0x4FU, 0x66U,
    0x6DU, 0x7DU, 0x07U, 0x7FU, 0x6FU
};

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */

static volatile uint32_t adc_iron_tmp_g = 0;

static volatile float sum_error = 0;

static volatile float error     = 0;

static volatile float duty = 0;

static uint16_t temp_setpoint_c = 300;

static uint16_t macro_m1_c = 350;
static uint16_t macro_m2_c = 350;

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

static void Draw_TemperatureSegment(uint16_t x,
                                    uint16_t y,
                                    uint8_t segment,
                                    uint16_t color,
                                    uint16_t width,
                                    uint16_t height,
                                    uint16_t thickness);

static uint16_t Get_SetPointTextX(void);

static void Draw_SetPointLabel(void);

static void Draw_SetPointValue(void);

static bool Read_MacroTemperature(const char *path, uint16_t *temperature);

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_FSM_state FSM_idle_state_handler(void)
{
    et_FSM_state next_state = idle_state;

    UI_Refresh_SelectedChannel();

    if (UI_encoder_c_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_encoder_c_but_clear_logged_state();

        switch(UI_Get_SelectedChannel())
        {
            case 0:
                UI_Draw_IronScreen(macro_m1_c, macro_m2_c);
                Draw_SetPointLabel();
                Draw_SetPointValue();
                (void)Display_TemperatureUnit(224U,
                                              48U,
                                              32U,
                                              24U,
                                              3U,
                                              4U,
                                              CYAN,
                                              BLACK);

                HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_2);

                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

                next_state = iron_state;
                break;

            case 1:
                next_state = gun_state;
                break;

            default:
                break;
        }
    }

    return next_state;
}

et_FSM_state FSM_init_state_handler(void)
{
    (void)Read_MacroTemperature("Conf/M1.txt", &macro_m1_c);
    (void)Read_MacroTemperature("Conf/M2.txt", &macro_m2_c);

    return idle_state;
}

static bool Read_MacroTemperature(const char *path, uint16_t *temperature)
{
    FIL file;
    char buffer[3];
    uint16_t parsed_value = 0U;
    bool valid = false;

    if (SD_OpenFille(&file, path, FILE_READ) != RET_OK)
    {
        return false;
    }

    if (f_size(&file) >= sizeof(buffer) &&
        SD_ReadFille_WithJump(&file, buffer, sizeof(buffer), 0U) == RET_OK)
    {
        valid = true;
        for (uint8_t index = 0U; index < sizeof(buffer); index++)
        {
            if (buffer[index] < '0' || buffer[index] > '9')
            {
                valid = false;
                break;
            }
            parsed_value = (uint16_t)(parsed_value * 10U +
                                      (uint16_t)(buffer[index] - '0'));
        }
    }

    if (SD_CloseFille(&file) != RET_OK)
    {
        valid = false;
    }
    else if (valid)
    {
        *temperature = parsed_value;
    }

    if (!valid) PRINT_E("[FSM] Invalid macro file %s", path);
    return valid;
}

et_FSM_state FSM_iron_state_handler(void)
{
    static uint8_t virtual_time = 0;

    et_FSM_state next_state = iron_state;

    uint8_t encoder_state;

    float temperature_c =
    0.137101f * (float)adc_iron_tmp_g + 26.0f;

    encoder_state = UI_encoder_but_get_logged_state();

    if (encoder_state == ENCODER_ROTATED_RIGHT)
    {
        UI_encoder_but_clear_logged_state();

        if (temp_setpoint_c <= 500U)
        {
            temp_setpoint_c += 5U;
        }

        Draw_SetPointValue();
    }

    else if (encoder_state == ENCODER_ROTATED_LEFT)
    {
        UI_encoder_but_clear_logged_state();

        if (temp_setpoint_c >= 5U)
        {
            temp_setpoint_c -= 5U;
        }
        else
        {
            temp_setpoint_c = 0U;
        }

        Draw_SetPointValue();
    }

    if (adc_new_val_flg == 1)
    {
        /* Check if enought time has passed. */
        if(++virtual_time == 30)
        {
            virtual_time = 0;

            /* Refresh the display. */
            Display_Temperature((uint16_t)(temperature_c + 0.5f),
                                      91U,
                                      48U,
                                      36U,
                                      64U,
                                      5U,
                                      6U,
                                      CYAN,
                                      BLACK);
        }

        /* Clears flag. */
        adc_new_val_flg = 0;

        error = (float)temp_setpoint_c - temperature_c;
        sum_error += error;

        if (sum_error >  60000.0f)
        {
            sum_error = 60000.0f;
        }

        else if (sum_error < -60000.0f )
        {
            sum_error = -60000.0f;
        } 

        duty = error * KP + sum_error * KI;

        if (duty > 1800.0f)
        {
            duty = 1800.0f;
        }

        else if (duty < 0.0f )
        {
            duty = 0.0f;
        }

        /* Set new duty cycle value. */
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)duty);
    }

    if (UI_encoder_c_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_encoder_c_but_clear_logged_state();

        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        HAL_TIM_Base_Stop_IT(&htim1);

        UI_Draw_IntroScreen();
        next_state = idle_state;
    }

    if (UI_b1_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_b1_but_clear_logged_state();
        temp_setpoint_c = macro_m1_c;

        Draw_SetPointValue();
    }

    else if (UI_b1_but_get_logged_state() == BUTTON_LONG_PRESSED)
    {
        UI_b1_but_clear_logged_state();
        macro_m1_c = temp_setpoint_c;

        UI_DrawMacroValue(50U,
                    ST7789_HEIGHT - 2U * EDGE - 50U + 27U,
                    macro_m1_c);
    }

    else if (UI_b2_but_get_logged_state() == BUTTON_PRESSED)
    {
        UI_b2_but_clear_logged_state();
        temp_setpoint_c = macro_m2_c;

        Draw_SetPointValue();
    }

    else if (UI_b2_but_get_logged_state() == BUTTON_LONG_PRESSED)
    {
        UI_b2_but_clear_logged_state();
        macro_m2_c = temp_setpoint_c;

        UI_DrawMacroValue(ST7789_WIDTH - 50U - 80U,
                    ST7789_HEIGHT - 2U * EDGE - 50U + 27U,
                    macro_m2_c);

    }

    return next_state;
}

et_FSM_state FSM_gun_state_handler(void)
{
    return idle_state;
}

et_FSM_state FSM_error_state_handler(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Base_Stop_IT(&htim1);

    UI_Draw_IntroScreen();

    return idle_state;
}

bool Display_Temperature(uint16_t temperature,
                         uint16_t x,
                         uint16_t y,
                         uint16_t digit_width,
                         uint16_t digit_height,
                         uint16_t segment_thickness,
                         uint16_t digit_spacing,
                         uint16_t foreground_color,
                         uint16_t background_color)
{

    uint8_t new_segments[3];
    uint32_t display_width;

    uint16_t value = (temperature > 999U) ? 999U : temperature;

    if (digit_width <= (2U * segment_thickness) ||
        digit_height < (2U * segment_thickness + 4U) ||
        segment_thickness == 0U)
    {
        return false;
    }

    display_width = (3U * (uint32_t)digit_width) +
                    (2U * (uint32_t)digit_spacing);
    if ((uint32_t)x + display_width > ST7789_WIDTH ||
        (uint32_t)y + digit_height > ST7789_HEIGHT)
    {
        return false;
    }

    new_segments[0] = (value >= 100U) ? digit_segments[value / 100U] : 0U;
    new_segments[1] = (value >= 10U) ? digit_segments[(value / 10U) % 10U] : 0U;
    new_segments[2] = digit_segments[value % 10U];

    for (uint8_t digit = 0U; digit < 3U; digit++)
    {
        uint16_t digit_x = (uint16_t)(x + digit *
            (digit_width + digit_spacing));

        for (uint8_t segment = 0U; segment < 7U; segment++)
        {
            uint16_t color = (new_segments[digit] & (1U << segment)) != 0U
                ? foreground_color
                : background_color;

            Draw_TemperatureSegment(
                digit_x,
                y,
                segment,
                color,
                digit_width,
                digit_height,
                segment_thickness
            );
        }
    }

    return true;
}

bool Display_TemperatureUnit(uint16_t x,
                             uint16_t y,
                             uint16_t width,
                             uint16_t height,
                             uint16_t thickness,
                             uint16_t spacing,
                             uint16_t foreground_color,
                             uint16_t background_color)
{
    uint16_t degree_width = width / 3U;
    uint16_t degree_height = height / 3U;
    uint16_t c_x;
    uint16_t c_width;

    if (thickness == 0U ||
        degree_width <= 2U * thickness ||
        degree_height <= 2U * thickness ||
        width <= degree_width + spacing + 2U * thickness ||
        height < 2U * thickness + 4U ||
        (uint32_t)x + width > ST7789_WIDTH ||
        (uint32_t)y + height > ST7789_HEIGHT)
    {
        return false;
    }

    c_x = x + degree_width + spacing;
    c_width = width - degree_width - spacing;

    ST7789_Fill(x, y, x + width - 1U, y + height - 1U, background_color);

    ST7789_Fill(x + thickness,
                y,
                x + degree_width - thickness - 1U,
                y + thickness - 1U,
                foreground_color);

    ST7789_Fill(x + thickness,
                y + degree_height - thickness,
                x + degree_width - thickness - 1U,
                y + degree_height - 1U,
                foreground_color);

    ST7789_Fill(x,
                y + thickness,
                x + thickness - 1U,
                y + degree_height - thickness - 1U,
                foreground_color);

    ST7789_Fill(x + degree_width - thickness,
                y + thickness,
                x + degree_width - 1U,
                y + degree_height - thickness - 1U,
                foreground_color);

    Draw_TemperatureSegment(c_x, y, 0U, foreground_color,
                            c_width, height, thickness);

    Draw_TemperatureSegment(c_x, y, 3U, foreground_color,
                            c_width, height, thickness);

    Draw_TemperatureSegment(c_x, y, 4U, foreground_color,
                            c_width, height, thickness);

    Draw_TemperatureSegment(c_x, y, 5U, foreground_color,
                            c_width, height, thickness);

    return true;
}
/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

static void Draw_TemperatureSegment(uint16_t x,
                                    uint16_t y,
                                    uint8_t segment,
                                    uint16_t color,
                                    uint16_t width,
                                    uint16_t height,
                                    uint16_t thickness)
{
    uint16_t x_start;
    uint16_t y_start;
    uint16_t x_end;
    uint16_t y_end;

    switch (segment)
    {
        case 0U:
            x_start = x + thickness;
            y_start = y;
            x_end = x + width - thickness - 1U;
            y_end = y + thickness - 1U;
            break;

        case 1U:
            x_start = x + width - thickness;
            y_start = y + thickness;
            x_end = x + width - 1U;
            y_end = y + (height / 2U) - 1U;
            break;

        case 2U:
            x_start = x + width - thickness;
            y_start = y + (height / 2U) + 1U;
            x_end = x + width - 1U;
            y_end = y + height - thickness - 1U;
            break;

        case 3U:
            x_start = x + thickness;
            y_start = y + height - thickness;
            x_end = x + width - thickness - 1U;
            y_end = y + height - 1U;
            break;

        case 4U:
            x_start = x;
            y_start = y + (height / 2U) + 1U;
            x_end = x + thickness - 1U;
            y_end = y + height - thickness - 1U;
            break;

        case 5U:
            x_start = x;
            y_start = y + thickness;
            x_end = x + thickness - 1U;
            y_end = y + (height / 2U) - 1U;
            break;

        case 6U:
            x_start = x + thickness;
            y_start = y + (height / 2U) - (thickness / 2U);
            x_end = x + width - thickness - 1U;
            y_end = y_start + thickness - 1U;
            break;

        default:
            return;
    }

    ST7789_Fill(x_start, y_start, x_end, y_end, color);
}

static uint16_t Get_SetPointTextX(void)
{
    const uint16_t text_width = 16U * Font_11x18.width;

    return (ST7789_WIDTH - text_width) / 2U;
}

static void Draw_SetPointLabel(void)
{
    const uint16_t x = Get_SetPointTextX();
    const uint16_t y = 135U;

    ST7789_WriteString(x, y, "Set Point: ", Font_11x18, CYAN, BLACK);
    ST7789_WriteString(x + 14U * Font_11x18.width,
                       y,
                       " C",
                       Font_11x18,
                       CYAN,
                       BLACK);
}

static void Draw_SetPointValue(void)
{
    char value_text[4] = {' ', ' ', ' ', '\0'};
    const uint16_t x = Get_SetPointTextX() + 11U * Font_11x18.width;
    const uint16_t y = 135U;
    const uint16_t value =
        (temp_setpoint_c > 999U) ? 999U : temp_setpoint_c;

    if (value >= 100U)
    {
        value_text[0] = (char)('0' + value / 100U);
    }
    if (value >= 10U)
    {
        value_text[1] = (char)('0' + (value / 10U) % 10U);
    }
    value_text[2] = (char)('0' + value % 10U);

    ST7789_WriteString(x, y, value_text, Font_11x18, CYAN, BLACK);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        /* Retrives the new adc value. */
        adc_iron_tmp_g = (uint32_t)((float)adc_iron_tmp_g * 0.4f + (float)HAL_ADC_GetValue(hadc) * 0.6f);

        /* Signals that a new conversion is available. */
        adc_new_val_flg = 1;
    }
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
      __NOP();
        // Injected conversion terminou
    }
}
    
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        /* Triggers the ADC conversion. */
        HAL_ADC_Start_IT(&hadc1);
    }
}

/* TODO: Add private functions. */

/* -- End of file -- */
