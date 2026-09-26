/** ********************************************************************************** **/
/** * @file      ili9341.h                                                           * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            ili9341.h.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      25/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 26/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __ILI9341_H__
#define __ILI9341_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

#include "stm32f1xx_hal.h"
#include "fonts.h"


/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Defines                                                                   * */
/* ************************************************************************************ */

#define ILI9341_SCREEN_HEIGHT 	240
#define ILI9341_SCREEN_WIDTH 	320

/* PIN Configuration */
#define HSPI_INSTANCE			&hspi1
#define LCD_CS_PORT				GPIOB
#define LCD_CS_PIN				GPIO_PIN_10
#define LCD_DC_PORT				GPIOB
#define LCD_DC_PIN				GPIO_PIN_0
#define	LCD_RST_PORT			GPIOB
#define	LCD_RST_PIN				GPIO_PIN_1

#define BURST_MAX_SIZE 			500


#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3
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
extern SPI_HandleTypeDef hspi1;
/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Public Macros                                                                    * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

void ILI9341_WriteCommand(uint8_t cmd);
void ILI9341_WriteData(uint8_t data);
void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len);
void ILI9341_Reset(void);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_SetRotation(uint8_t rotation);
void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ILI9341_DrawColor(uint16_t color);
void ILI9341_DrawColorBurst(uint16_t color, uint32_t size);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color);
void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color);
void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color);

void ILI9341_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);

void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);

/* TODO: Add public function prototypes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __ILI9341_H__ */

/* -- End of file -- */
