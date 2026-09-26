/** ********************************************************************************** **/
/** * @file      st7789.c                                                            * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            st7789.c.                                                           * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      29/10/2025                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 26/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* Include Config File. */
#include "st7789_config.h"

/* Include Types File. */
#include "st7789_types.h"

/* Include Header File. */
#include "st7789.h"


#include "sd_card.h"
#include <stdint.h>
#include <sys/_intsup.h>
/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

#if (PROJECT_ENABLE_LOGGER == ENABLED)

    #if ST7789_DEBUG_LEVEL

        DEBUG_LEVEL_REGISTER(ST7789_DEBUG_LEVEL)

    #else 

        #warning "No debug level ser for the ST7789 API"

        DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

    #endif

#else 

    MODULE_DEBUG_REGISTER(DEBUG_LEVEL_N, ST7789_module)

#endif

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

#define HOR_LEN     5   //  Mind the resolution of your screen!
    
/* Control Registers and constant codes */
#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36


/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80

/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40

/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20

/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10

/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00
#define ST7789_MADCTL_BGR 0x08

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Advanced options */
#define ST7789_COLOR_MODE_16bit 0x55    //  RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    //  RGB666 (18bit)

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

/* TODO: Add flags. */

/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */

/* TODO: Add constant variables. */

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */

static st_ST7789_conf g_st7789_conf = ST7789_default_config;

static uint8_t disp_buf[ST7789_WIDTH * HOR_LEN * 2];
/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* Basic operations */
#define ST7789_RST_CLR() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_RST_PIN, 			\
										 DISPLAY_RST_PORT, 			\
										 GPIO_LOW)

#define ST7789_RST_SET() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_RST_PIN, 			\
										 DISPLAY_RST_PORT, 			\
										 GPIO_HIGH)

#define ST7789_DC_CLR() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_DC_PIN, 			\
										 DISPLAY_DC_PORT, 			\
										 GPIO_LOW)

#define ST7789_DC_SET() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_DC_PIN, 			\
										 DISPLAY_DC_PORT, 			\
										 GPIO_HIGH)

#define ST7789_SELECT() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_CS_PIN, 			\
										 DISPLAY_CS_PORT, 			\
										 GPIO_LOW)

#define ST7789_UNSELECT() 											\
		g_st7789_conf.ST7789_GPIOPin_Set(DISPLAY_CS_PIN, 			\
										 DISPLAY_CS_PORT, 			\
										 GPIO_HIGH)

#if (ST7789_USE_DMA == ENABLED)
    
    #define ST7789_SPI_SEND(...)                                                         \
        g_st7789_conf.ST7789_SPI_Transmit(__VA_ARGS__)

#elif (ST7789_USE_DMA == DISABLED)

    #define ST7789_SPI_SEND(...)                                                         \
        g_st7789_conf.ST7789_SPI_Transmit(__VA_ARGS__, 1000)

#else 

    #error "Directive to use DMA not recognized"

#endif 

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/**
 * @brief Write command to ST7789 controller
 * @param cmd -> command to write
 * @return none
 */
static void ST7789_WriteCommand(uint8_t cmd);

/**
 * @brief Write data to ST7789 controller
 * @param buff -> pointer of data buffer
 * @param buff_size -> size of the data buffer
 * @return none
 */
static void ST7789_WriteData(uint8_t *buff, size_t buff_size);

/**
 * @brief Write data to ST7789 controller, simplify for 8bit data.
 * data -> data to write
 * @return none
 */
static void ST7789_WriteSmallData(uint8_t data);

/**
 * @brief Set address of DisplayWindow
 * @param xi&yi -> coordinates of window
 * @return none
 */
static void ST7789_SetAddressWindow(uint16_t x0,
                                    uint16_t y0,
                                    uint16_t x1,
                                    uint16_t y1);

/**
 * @brief Converts hexadecimal font data read from the SD card
 *        into a uint16_t buffer.
 *
 * @param[in]  buff   Buffer containing hexadecimal font data
 *                    in the format "0xXXXX, ".
 * @param[out] out    Output buffer containing the converted
 *                    uint16_t font values.
 * @param[in]  height Number of font rows to convert.
 *
 * @return None.
 */
static void HexFontBufferToUint16(const char *buff,
                                  uint16_t *out,
                                  uint16_t height);

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

void ST7789_SetRotation(uint8_t m)
{
    ST7789_WriteCommand(ST7789_MADCTL); // MADCTL
    switch (m) {
    case 0:
        ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
        break;
    case 1:
        ST7789_WriteSmallData(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
        break;
    case 2:
        ST7789_WriteSmallData(ST7789_MADCTL_RGB);
        break;
    case 3:
        ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
        break;
    default:
        break;
    }
}

void ST7789_Init(void)
{
    
    #if (ST7789_USE_DMA == ENABLED)
    
        /* Clears the buffer for new use. */
        memset(disp_buf, 0, sizeof(disp_buf));
    
    #endif

    HAL_Delay(50);
    ST7789_RST_CLR();
    HAL_Delay(50);
    ST7789_RST_SET();
    HAL_Delay(200);

	ST7789_WriteCommand(ST7789_SWRESET);

	ST7789_WriteCommand(ST7789_SLPOUT); //  Out of sleep mode

    ST7789_WriteCommand(ST7789_COLMOD);     //  Set color mode
	
    ST7789_WriteSmallData(ST7789_COLOR_MODE_16bit);
    ST7789_WriteCommand(0xB2);              //  Porch control

    {
        uint8_t data[] = { 0x0C, 0x0C, 0x00, 0x33, 0x33 };
        ST7789_WriteData(data, sizeof(data));
    }

    ST7789_SetRotation(ST7789_ROTATION);    //  MADCTL (Display Rotation)

    /* Internal LCD Voltage generator settings */
    ST7789_WriteCommand(0XB7);              //  Gate Control
    ST7789_WriteSmallData(0x35);            //  Default value
    ST7789_WriteCommand(0xBB);              //  VCOM setting
    ST7789_WriteSmallData(0x19);            //  0.725v (default 0.75v for 0x20)
    ST7789_WriteCommand(0xC0);              //  LCMCTRL
    ST7789_WriteSmallData(0x2C);            //  Default value
    ST7789_WriteCommand(0xC2);              //  VDV and VRH command Enable
    ST7789_WriteSmallData(0x01);            //  Default value
    ST7789_WriteCommand(0xC3);              //  VRH set
    ST7789_WriteSmallData(0x12);            //  +-4.45v (defalut +-4.1v for 0x0B)
    ST7789_WriteCommand(0xC4);              //  VDV set
    ST7789_WriteSmallData(0x20);            //  Default value
    ST7789_WriteCommand(0xC6);              //  Frame rate control in normal mode
    ST7789_WriteSmallData(0x0F);            //  Default value (60HZ)
    ST7789_WriteCommand(0xD0);              //  Power control
    ST7789_WriteSmallData(0xA4);            //  Default value
    ST7789_WriteSmallData(0xA1);            //  Default value

    ST7789_WriteCommand(0xE0);

    {
        uint8_t data[] = { 0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23 };
        ST7789_WriteData(data, sizeof(data));
    }

    ST7789_WriteCommand(0xE1);

    {
        uint8_t data[] = { 0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23 };
        ST7789_WriteData(data, sizeof(data));
    }

    ST7789_WriteCommand(ST7789_INVOFF);      //  Inversion FF
    
    ST7789_WriteCommand(ST7789_NORON);      //  Normal Display on
    ST7789_WriteCommand(ST7789_DISPON); //  Main screen turned on

}

void ST7789_Fill_Color(uint16_t color)
{
    uint16_t row;

    for (row = 0; row < ST7789_WIDTH * HOR_LEN * 2; row += 2)
    {
        disp_buf[row] = (uint8_t)(color >> 8);
        disp_buf[row + 1] = (uint8_t)color;
    }

    for (row = 0; row < ST7789_HEIGHT; row += HOR_LEN)
    {
        uint16_t rows = (ST7789_HEIGHT - row < HOR_LEN) ? ST7789_HEIGHT - row : HOR_LEN;

        ST7789_SetAddressWindow(0, row, ST7789_WIDTH - 1, row + rows - 1);
        ST7789_WriteData(disp_buf, ST7789_WIDTH * rows * 2);
    }
}

void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t data[] = { color >> 8, color & 0xFF };

    if ((x < 0) || (x >= ST7789_WIDTH) ||
        (y < 0) || (y >= ST7789_HEIGHT))
    {
        return;
    }
        
    ST7789_SetAddressWindow(x, y, x, y);
    
    ST7789_SELECT();
    ST7789_WriteData(data, sizeof(data));
    ST7789_UNSELECT();
}

void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{
    if (xSta >= ST7789_WIDTH || ySta >= ST7789_HEIGHT ||
        xEnd >= ST7789_WIDTH || yEnd >= ST7789_HEIGHT ||
        xSta > xEnd || ySta > yEnd)
    {
        return;
    }
        
    uint16_t width = xEnd - xSta + 1;
    uint16_t row;

    for (row = 0; row < width * HOR_LEN * 2; row += 2)
    {
        disp_buf[row] = (uint8_t)(color >> 8);
        disp_buf[row + 1] = (uint8_t)color;
    }

    for (row = ySta; row <= yEnd; row += HOR_LEN)
    {
        uint16_t rows = (yEnd - row + 1 < HOR_LEN) ? yEnd - row + 1 : HOR_LEN;

        ST7789_SetAddressWindow(xSta, row, xEnd, row + rows - 1);
        ST7789_WriteData(disp_buf, width * rows * 2);
    }
}

void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x <= 0) || (x > ST7789_WIDTH) || (y <= 0) || (y > ST7789_HEIGHT))
    {
        return;
    }

    ST7789_SELECT();
    ST7789_Fill(x - 1, y - 1, x + 1, y + 1, color);
    ST7789_UNSELECT();
}

void ST7789_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, 
                                  uint16_t y1, uint16_t color) 
{
    uint16_t swap;
    uint16_t steep = ABS(y1 - y0) > ABS(x1 - x0);

    if (steep) 
    {
        swap = x0;
        x0 = y0;
        y0 = swap;

        swap = x1;
        x1 = y1;
        y1 = swap;
        //_swap_int16_t(x0, y0);
        //_swap_int16_t(x1, y1);
    }

    if (x0 > x1) 
    {
        swap = x0;
        x0 = x1;
        x1 = swap;

        swap = y0;
        y0 = y1;
        y1 = swap;
        //_swap_int16_t(x0, x1);
        //_swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = ABS(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) 
    {
        if (steep) 
        {
            ST7789_DrawPixel(y0, x0, color);
        } 
        
        else 
        {
            ST7789_DrawPixel(x0, y0, color);
        }

        err -= dy;

        if (err < 0) 
        {
            y0 += ystep;
            err += dx;
        }
    }
}

void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    ST7789_SELECT();
    ST7789_DrawLine(x1, y1, x2, y1, color);
    ST7789_DrawLine(x1, y1, x1, y2, color);
    ST7789_DrawLine(x1, y2, x2, y2, color);
    ST7789_DrawLine(x2, y1, x2, y2, color);
    ST7789_UNSELECT();
}

void ST7789_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ST7789_SELECT();
    ST7789_DrawPixel(x0, y0 + r, color);
    ST7789_DrawPixel(x0, y0 - r, color);
    ST7789_DrawPixel(x0 + r, y0, color);
    ST7789_DrawPixel(x0 - r, y0, color);

    while (x < y) 
    {
        if (f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7789_DrawPixel(x0 + x, y0 + y, color);
        ST7789_DrawPixel(x0 - x, y0 + y, color);
        ST7789_DrawPixel(x0 + x, y0 - y, color);
        ST7789_DrawPixel(x0 - x, y0 - y, color);

        ST7789_DrawPixel(x0 + y, y0 + x, color);
        ST7789_DrawPixel(x0 - y, y0 + x, color);
        ST7789_DrawPixel(x0 + y, y0 - x, color);
        ST7789_DrawPixel(x0 - y, y0 - x, color);
    }

    ST7789_UNSELECT();
}

void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{
    if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT) ||
        ((x + w - 1) >= ST7789_WIDTH) || ((y + h - 1) >= ST7789_HEIGHT))
    {
        return;
    }
        
    ST7789_SELECT();
    ST7789_SetAddressWindow(x, y, x + w - 1, y + h - 1);
    ST7789_WriteData((uint8_t*) data, sizeof(uint16_t) * w * h);
    ST7789_UNSELECT();
}

void ST7789_InvertColors(uint8_t invert)
{
    ST7789_SELECT();
    ST7789_WriteCommand(invert ? 0x21 /* INVON */: 0x20 /* INVOFF */);
    ST7789_UNSELECT();
}

void ST7789_WriteChar(uint16_t x,
                      uint16_t y,
                      char ch,
                      FontDef font,
                      uint16_t color,
                      uint16_t bgcolor)
{
    uint32_t i, b, j;

    ST7789_SELECT();

    ST7789_SetAddressWindow(
        x,
        y,
        x + font.width - 1,
        y + font.height - 1
    );

    #if (ST7789_USE_INTERNAL_STORAGE == ENABLED)

        for (i = 0; i < font.height; i++)
        {
            b = font.data[(ch - 32) * font.height + i];

            for (j = 0; j < font.width; j++)
            {
                uint16_t pixel_color;

                if ((b << j) & 0x8000)
                    pixel_color = color;
                else
                    pixel_color = bgcolor;

                uint8_t data[] =
                {
                    pixel_color >> 8,
                    pixel_color & 0xFF
                };

                ST7789_WriteData(data, sizeof(data));
            }
        }

    #else

        

        char buff[font.height * 8UL];
        uint16_t decoded_buff[font.height];

        unsigned long offset =
            (unsigned long)(ch - 32) *
            (font.height * 8UL + 2UL);

        if (SD_ReadFille_WithJump(
                font.path,
                buff,
                font.height * 8UL,
                offset) != RET_OK)
        {
            ST7789_UNSELECT();
            return;
        }

        HexFontBufferToUint16(
            buff,
            decoded_buff,
            font.height
        );

        for (i = 0; i < font.height; i++)
        {
            b = decoded_buff[i];

            for (j = 0; j < font.width; j++)
            {
                uint16_t pixel_color;

                if ((b << j) & 0x8000)
                    pixel_color = color;
                else
                    pixel_color = bgcolor;

                uint8_t data[] =
                {
                    pixel_color >> 8,
                    pixel_color & 0xFF
                };

                ST7789_WriteData(data, sizeof(data));
            }
        }

    #endif

    ST7789_UNSELECT();
}

#if (ST7789_USE_INTERNAL_STORAGE == ENABLED)

    void ST7789_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
    {
        ST7789_SELECT();
        while (*str) 
        {
            if (x + font.width >= ST7789_WIDTH) 
            {
                x = 0;
                y += font.height;

                if (y + font.height >= ST7789_HEIGHT) 
                {
                    break;
                }

                if (*str == ' ') 
                {
                    // skip spaces in the beginning of the new line
                    str++;
                    continue;
                }
            }

            ST7789_WriteChar(x, y, *str, font, color, bgcolor);
            
            x += font.width;
            str++;
        }
        ST7789_UNSELECT();
    }

#endif

void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    ST7789_SELECT();
    uint8_t i;

    /* Check input parameters */
    if (x >= ST7789_WIDTH || y >= ST7789_HEIGHT) 
    {
        /* Return error */
        return;
    }

    /* Check width and height */
    if ((x + w) >= ST7789_WIDTH) 
    {
        w = ST7789_WIDTH - x;
    }

    if ((y + h) >= ST7789_HEIGHT) 
    {
        h = ST7789_HEIGHT - y;
    }

    /* Draw lines */
    for (i = 0; i <= h; i++) 
    {
        /* Draw lines */
        ST7789_DrawLine(x, y + i, x + w, y + i, color);
    }
    
    ST7789_UNSELECT();
}

void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color)
{
    ST7789_SELECT();
    /* Draw lines */
    ST7789_DrawLine(x1, y1, x2, y2, color);
    ST7789_DrawLine(x2, y2, x3, y3, color);
    ST7789_DrawLine(x3, y3, x1, y1, color);
    ST7789_UNSELECT();
}

void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color)
{
    ST7789_SELECT();
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1);
    deltay = ABS(y2 - y1);
    x = x1;
    y = y1;

    if (x2 >= x1) {
        xinc1 = 1;
        xinc2 = 1;
    }
    else {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1) {
        yinc1 = 1;
        yinc2 = 1;
    }
    else {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay) {
        xinc1 = 0;
        yinc2 = 0;
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;
    }
    else {
        xinc2 = 0;
        yinc1 = 0;
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        ST7789_DrawLine(x, y, x3, y3, color);

        num += numadd;
        if (num >= den) {
            num -= den;
            x += xinc1;
            y += yinc1;
        }
        x += xinc2;
        y += yinc2;
    }
    ST7789_UNSELECT();
}

void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    ST7789_SELECT();
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ST7789_DrawPixel(x0, y0 + r, color);
    ST7789_DrawPixel(x0, y0 - r, color);
    ST7789_DrawPixel(x0 + r, y0, color);
    ST7789_DrawPixel(x0 - r, y0, color);
    ST7789_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7789_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        ST7789_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        ST7789_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        ST7789_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
    ST7789_UNSELECT();
}

void ST7789_TearEffect(uint8_t tear)
{
    ST7789_SELECT();
    ST7789_WriteCommand(tear ? 0x35 /* TEON */: 0x34 /* TEOFF */);
    ST7789_UNSELECT();
}

void ST7789_DrawRoundRect(uint16_t x,
                          uint16_t y,
                          uint16_t width,
                          uint16_t height,
                          uint16_t radius,
                          uint16_t color)
{
    if (radius > width / 2)
        radius = width / 2;

    if (radius > height / 2)
        radius = height / 2;

    for (int16_t dy = 0; dy < height; dy++)
    {
        int16_t x_start = 0;
        int16_t x_end = width - 1;

        // Top rounded corners
        if (dy < radius)
        {
            int16_t yy = radius - dy;

            int32_t inside = (int32_t)radius * radius -
                             (int32_t)yy * yy;

            int16_t offset = radius - sqrt(inside);

            x_start = offset;
            x_end = width - 1 - offset;
        }

        // Bottom rounded corners
        else if (dy >= height - radius)
        {
            int16_t yy = dy - (height - radius - 1);

            int32_t inside = (int32_t)radius * radius -
                             (int32_t)yy * yy;

            int16_t offset = radius - sqrt(inside);

            x_start = offset;
            x_end = width - 1 - offset;
        }

        for (int16_t dx = x_start; dx <= x_end; dx++)
        {
            ST7789_DrawPixel(
                x + dx,
                y + dy,
                color
            );
        }
    }
}


/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

static void ST7789_WriteCommand(uint8_t cmd)
{
    ST7789_SELECT();
    ST7789_DC_CLR();
    ST7789_SPI_SEND(&ST7789_SPI_PORT, &cmd, sizeof(cmd));

    while (HAL_SPI_GetState(&ST7789_SPI_PORT) != HAL_SPI_STATE_READY)
    {
        /* Do Nothing. */
    }

    ST7789_UNSELECT();
}

static void ST7789_WriteData(uint8_t *buff, size_t buff_size)
{
    ST7789_SELECT();
    ST7789_DC_SET();

    // split data in small chunks because HAL can't send more than 64K at once

    while (buff_size > 0) 
    {
        uint16_t chunk_size = buff_size > 65535 ? 65535 : buff_size;

    #if (ST7789_USE_DMA == ENABLED)

        ST7789_SPI_SEND(&ST7789_SPI_PORT, buff, chunk_size);
        while (HAL_SPI_GetState(&ST7789_SPI_PORT) != HAL_SPI_STATE_READY)
        {
            /* Do Nothing. */
        }

    #else
    
        ST7789_SPI_SEND(&ST7789_SPI_PORT, buff, chunk_size);
    
    #endif

        buff += chunk_size;
        buff_size -= chunk_size;
    }

    ST7789_UNSELECT();
}

static void ST7789_WriteSmallData(uint8_t data)
{
    ST7789_SELECT();
    ST7789_DC_SET();

    ST7789_SPI_SEND(&ST7789_SPI_PORT, &data, sizeof(data));

    while (HAL_SPI_GetState(&ST7789_SPI_PORT) != HAL_SPI_STATE_READY)
    {
        /* Do Nothing. */
    }

    ST7789_UNSELECT();
}

static void ST7789_SetAddressWindow(uint16_t x0,
                                    uint16_t y0,
                                    uint16_t x1,
                                    uint16_t y1)
{
    uint8_t data[4];

    x0 += X_SHIFT;
    x1 += X_SHIFT;
    y0 += Y_SHIFT;
    y1 += Y_SHIFT;

    /* Column address */
    ST7789_WriteCommand(ST7789_CASET);

    data[0] = x0 >> 8;
    data[1] = x0 & 0xFF;
    data[2] = x1 >> 8;
    data[3] = x1 & 0xFF;

    ST7789_WriteData(data, 4);

    /* Row address */
    ST7789_WriteCommand(ST7789_RASET);

    data[0] = y0 >> 8;
    data[1] = y0 & 0xFF;
    data[2] = y1 >> 8;
    data[3] = y1 & 0xFF;

    ST7789_WriteData(data, 4);

    /* Start memory write */
    ST7789_WriteCommand(ST7789_RAMWR);
}

static void HexFontBufferToUint16(const char *buff,
                                  uint16_t *out,
                                  uint16_t height)
{
    for (uint16_t i = 0; i < height; i++)
    {
        const char *p = &buff[i * 8];

        uint16_t value = 0;

        for (uint8_t j = 2; j < 6; j++)
        {
            char c = p[j];

            value <<= 4;

            if (c >= '0' && c <= '9')
                value |= (uint16_t)(c - '0');
            else if (c >= 'A' && c <= 'F')
                value |= (uint16_t)(c - 'A' + 10);
            else if (c >= 'a' && c <= 'f')
                value |= (uint16_t)(c - 'a' + 10);
        }

        out[i] = value;
    }
}


/* TODO: Add private functions. */

/* -- End of file -- */
