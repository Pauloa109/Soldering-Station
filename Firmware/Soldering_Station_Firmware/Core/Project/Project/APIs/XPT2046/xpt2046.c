#include "xpt2046.h"


#define MAX_RAX_X_COORDINATES 		(1930)
#define MAX_RAX_Y_COORDINATES 		(1930)

/* --------------------------------------------------------------------------
 * Global variables
 * -------------------------------------------------------------------------- */

SPI_HandleTypeDef* spiPort = NULL;

TouchScreen_CoordinatesRaw ts_CoordinatesRaw;
TouchScreen_Coordinates ts_Coordinates;
TouchScreen_OrientationTypeDef ts_Orientation;
TouchScreen_Size ts_Size;
TouchScreen_ControlByte ts_ControlByte;

GPIO_TypeDef* ts_Cs_Port = NULL;
GPIO_TypeDef* ts_Penirq_Port = NULL;

uint16_t ts_Cs_Pin = 0;
uint16_t ts_Penirq_Pin = 0;

uint8_t command = 0;


/* --------------------------------------------------------------------------
 * Initialization
 * -------------------------------------------------------------------------- */

void xpt2046_init(void)
{
    /*
     * 12-bit ADC
     */
    ts_ControlByte.bitMode = XPT2046_12BIT_MODE;

    /*
     * Keep ADC/reference configuration compatible with normal SPI reading.
     *
     * We are initially using Z1 for touch detection.
     * PENIRQ can be added afterwards.
     */
    ts_ControlByte.powerMode = XPT2046_REFERENCE_ON_ADC_OFF;

    /*
     * Differential measurement
     */
    ts_ControlByte.reference = XPT2046_DFR_MODE;

    /*
     * Default channel
     */
    ts_ControlByte.channel = XPT2046_DFR_X;

    /*
     * Start bit
     */
    ts_ControlByte.startBit = XPT2046_START;


    ts_Orientation = XPT2046_ORIENTATION_LANDSCAPE_MIRROR;

    ts_Size.width = XPT2046_WIDTH;
    ts_Size.height = XPT2046_HEIGHT;


    ts_Cs_Port = XPT2046_CS_Port;
    ts_Cs_Pin  = XPT2046_CS_Pin;

    ts_Penirq_Port = XPT2046_PENIRQ_Port;
    ts_Penirq_Pin  = XPT2046_PENIRQ_Pin;

    xpt2046_control_byte_update();

    xpt2046_unselect();

    /*
     * Clear coordinates
     */
    ts_CoordinatesRaw.x  = 0;
    ts_CoordinatesRaw.y  = 0;
    ts_CoordinatesRaw.z1 = 0;
    ts_CoordinatesRaw.z2 = 0;

    ts_Coordinates.x = 0;
    ts_Coordinates.y = 0;
    ts_Coordinates.z = 0;
}


/* --------------------------------------------------------------------------
 * SPI
 * -------------------------------------------------------------------------- */

void xpt2046_spi(SPI_HandleTypeDef* spi)
{
    spiPort = spi;
}


/* --------------------------------------------------------------------------
 * CS
 * -------------------------------------------------------------------------- */

void xpt2046_cs(GPIO_TypeDef* cs_port, uint16_t cs_pin)
{
    ts_Cs_Port = cs_port;
    ts_Cs_Pin = cs_pin;
}


void xpt2046_select(void)
{
    HAL_GPIO_WritePin(
        ts_Cs_Port,
        ts_Cs_Pin,
        GPIO_PIN_RESET
    );
}


void xpt2046_unselect(void)
{
    HAL_GPIO_WritePin(
        ts_Cs_Port,
        ts_Cs_Pin,
        GPIO_PIN_SET
    );
}


/* --------------------------------------------------------------------------
 * PENIRQ
 * -------------------------------------------------------------------------- */

void xpt2046_penirq(
    GPIO_TypeDef* penirq_port,
    uint16_t penirq_pin)
{
    ts_Penirq_Port = penirq_port;
    ts_Penirq_Pin = penirq_pin;
}


uint8_t xpt2046_interrupt(void)
{
    if (ts_Penirq_Port == NULL)
        return 0;

    /*
     * PENIRQ is ACTIVE LOW.
     *
     * LOW  = touch
     * HIGH = no touch
     */
    return (
        HAL_GPIO_ReadPin(
            ts_Penirq_Port,
            ts_Penirq_Pin
        ) == GPIO_PIN_RESET
    );
}


/* --------------------------------------------------------------------------
 * Orientation
 * -------------------------------------------------------------------------- */

void xpt2046_orientation(
    TouchScreen_OrientationTypeDef orientation_)
{
    ts_Orientation = orientation_;
}


/* --------------------------------------------------------------------------
 * Configuration
 * -------------------------------------------------------------------------- */

void xpt2046_bit_mode(uint8_t b)
{
    ts_ControlByte.bitMode = b;

    xpt2046_control_byte_update();
}


void xpt2046_set_size(uint16_t w, uint16_t h)
{
    ts_Size.width = w;
    ts_Size.height = h;
}


/*
 * These functions were declared in your .h but were missing
 * from your .c.
 */

void xpt2046_power_mode(uint8_t p)
{
    ts_ControlByte.powerMode = p;

    xpt2046_control_byte_update();
}


void xpt2046_reference(uint8_t r)
{
    ts_ControlByte.reference = r;

    xpt2046_control_byte_update();
}


void xpt2046_channel(uint8_t c)
{
    ts_ControlByte.channel = c;

    xpt2046_control_byte_update();
}


/* --------------------------------------------------------------------------
 * Control byte
 * -------------------------------------------------------------------------- */

void xpt2046_control_byte_update(void)
{
    command =
        ts_ControlByte.startBit |
        ts_ControlByte.channel |
        ts_ControlByte.bitMode |
        ts_ControlByte.reference |
        ts_ControlByte.powerMode;
}


/* --------------------------------------------------------------------------
 * Z threshold
 * -------------------------------------------------------------------------- */

uint16_t xpt2046_zthreshold(void)
{
    if (ts_ControlByte.bitMode == XPT2046_8BIT_MODE)
    {
        return Z_THRESHOLD_08BIT;
    }

    return Z_THRESHOLD_12BIT;
}


/* --------------------------------------------------------------------------
 * Interrupt mode
 * -------------------------------------------------------------------------- */

uint8_t xpt2046_interruptions_activated(void)
{
    return (
        ts_ControlByte.powerMode == XPT2046_POWER_DOWN ||
        ts_ControlByte.powerMode == XPT2046_REFERENCE_ON_ADC_OFF
    );
}


/* --------------------------------------------------------------------------
 * Touch detection
 * -------------------------------------------------------------------------- */

uint8_t xpt2046_pressed(void)
{
    /*
     * If IRQ is configured in a valid power-down mode,
     * use PENIRQ.
     */
    if (xpt2046_interruptions_activated())
    {
        return xpt2046_interrupt();
    }

    /*
     * Otherwise use Z1.
     */
    return (
        ts_CoordinatesRaw.z1 >
        xpt2046_zthreshold()
    );
}


/* --------------------------------------------------------------------------
 * Read ADC
 * -------------------------------------------------------------------------- */

static uint16_t xpt2046_read_adc(uint8_t channel)
{
    uint8_t rx[2] = {0, 0};
    uint8_t dummy[2] = {0, 0};


    ts_ControlByte.channel = channel;

    xpt2046_control_byte_update();


    /*
     * Send command byte.
     */
    if (HAL_SPI_Transmit(
            spiPort,
            &command,
            1,
            HAL_MAX_DELAY) != HAL_OK)
    {
        return 0;
    }


    /*
     * Receive 16 clocks.
     */
    if (HAL_SPI_TransmitReceive(
            spiPort,
            dummy,
            rx,
            2,
            HAL_MAX_DELAY) != HAL_OK)
    {
        return 0;
    }


    /*
     * XPT2046 12-bit format:
     *
     * rx[0] = D11 D10 D9 D8 D7 D6 D5 D4
     * rx[1] = D3  D2  D1 D0  X  X  X  X
     *
     * Therefore:
     *
     * result = rx[0] << 4 | rx[1] >> 4
     */
    if (ts_ControlByte.bitMode == XPT2046_12BIT_MODE)
    {
        return (
            ((uint16_t)rx[0] << 4) |
            ((uint16_t)rx[1] >> 4)
        );
    }


    /*
     * 8-bit mode
     */
    return rx[0];
}


/* --------------------------------------------------------------------------
 * Update touch data
 * -------------------------------------------------------------------------- */

void xpt2046_update(void)
{
    uint32_t x_sum = 0;
    uint32_t y_sum = 0;
    uint32_t z1_sum = 0;
    uint32_t z2_sum = 0;


    if (spiPort == NULL)
    {
        return;
    }


    /*
     * Select XPT2046
     */
    xpt2046_select();


    /*
     * Take several measurements.
     */
    for (uint32_t i = 0; i < AVERAGE_POINTS; i++)
    {
        x_sum += xpt2046_read_adc(XPT2046_DFR_X);

        y_sum += xpt2046_read_adc(XPT2046_DFR_Y);

        z1_sum += xpt2046_read_adc(XPT2046_DFR_Z1);

        z2_sum += xpt2046_read_adc(XPT2046_DFR_Z2);
    }


    /*
     * Release CS.
     */
    xpt2046_unselect();


    /*
     * Average raw values.
     */
    ts_CoordinatesRaw.x =
        x_sum / AVERAGE_POINTS;

    ts_CoordinatesRaw.y =
        y_sum / AVERAGE_POINTS;

    ts_CoordinatesRaw.z1 =
        z1_sum / AVERAGE_POINTS;

    ts_CoordinatesRaw.z2 =
        z2_sum / AVERAGE_POINTS;


    /* ----------------------------------------------------------
     * Convert raw coordinates
     * ---------------------------------------------------------- */

    int32_t rawX = ts_CoordinatesRaw.x;
    int32_t rawY = ts_CoordinatesRaw.y;


    /*
     * Prevent values outside ADC range.
     */
    if (rawX < 0)
        rawX = 0;

    if (rawX > MAX_RAX_X_COORDINATES)
        rawX = MAX_RAX_X_COORDINATES;

    if (rawY < 0)
        rawY = 0;

    if (rawY > MAX_RAX_Y_COORDINATES)
        rawY = MAX_RAX_Y_COORDINATES;


    int32_t x = 0;
    int32_t y = 0;


    /* ----------------------------------------------------------
     * Orientation
     * ---------------------------------------------------------- */

	switch (ts_Orientation)
	{
		/*
		* 0°
		*/
		case XPT2046_ORIENTATION_PORTRAIT:
		{
			x = ((int32_t)(ts_Size.width  - 1) * rawX) / MAX_RAX_X_COORDINATES;
			y = ((int32_t)(ts_Size.height - 1) * rawY) / MAX_RAX_Y_COORDINATES;

			x -= XPT2046_X_OFFSET;
			y -= XPT2046_Y_OFFSET;

			break;
		}


		/*
		* 90°
		*/
		case XPT2046_ORIENTATION_LANDSCAPE:
		{
			x = ((int32_t)(ts_Size.width  - 1) * rawY) / MAX_RAX_Y_COORDINATES;
			y = ((int32_t)(ts_Size.height - 1) * (MAX_RAX_X_COORDINATES - rawX)) / MAX_RAX_X_COORDINATES;

			x -= XPT2046_Y_OFFSET;
			y -= XPT2046_X_OFFSET;

			break;
		}


		/*
		* 180°
		*/
		case XPT2046_ORIENTATION_PORTRAIT_MIRROR:
		{
			x = ((int32_t)(ts_Size.width  - 1) * (MAX_RAX_X_COORDINATES - rawX)) / MAX_RAX_X_COORDINATES;
			y = ((int32_t)(ts_Size.height - 1) * (MAX_RAX_Y_COORDINATES - rawY)) / MAX_RAX_Y_COORDINATES;

			x -= XPT2046_X_OFFSET;
			y -= XPT2046_Y_OFFSET;

			break;
		}


		/*
		* 270°
		*/
		case XPT2046_ORIENTATION_LANDSCAPE_MIRROR:
		{
			x = ((int32_t)(ts_Size.width  - 1) * (MAX_RAX_X_COORDINATES - rawY)) / MAX_RAX_X_COORDINATES;
			y = ((int32_t)(ts_Size.height - 1) * (MAX_RAX_Y_COORDINATES - rawX)) / MAX_RAX_Y_COORDINATES;

			x -= XPT2046_X_OFFSET;
			y -= XPT2046_Y_OFFSET;

			break;
		}

		default:
		{
			x = 0;
			y = 0;

			break;
		}
	}


    /* ----------------------------------------------------------
     * Clamp coordinates
     * ---------------------------------------------------------- */

    if (x < 0)
        x = 0;

    if (y < 0)
        y = 0;


    if (x >= ts_Size.width)
        x = ts_Size.width - 1;

    if (y >= ts_Size.height)
        y = ts_Size.height - 1;


    /* ----------------------------------------------------------
     * Store
     * ---------------------------------------------------------- */

    ts_Coordinates.x = (uint16_t)x;
    ts_Coordinates.y = (uint16_t)y;
    ts_Coordinates.z = ts_CoordinatesRaw.z1;
}


/* --------------------------------------------------------------------------
 * Read position
 * -------------------------------------------------------------------------- */

void xpt2046_read_position(
    uint16_t* x,
    uint16_t* y)
{
    if (x == NULL || y == NULL)
        return;


    /*
     * Read ADC values.
     */
    xpt2046_update();


    /*
     * Check touch.
     */
    if (xpt2046_pressed())
    {
        *x = ts_Coordinates.x;
        *y = ts_Coordinates.y;
    }
    else
    {
        *x = 0;
        *y = 0;
    }
}


/* --------------------------------------------------------------------------
 * Compare
 * -------------------------------------------------------------------------- */

uint8_t xtp_compare_cords(
    uint16_t x,
    uint16_t y,
    uint16_t z,
    TouchScreen_Coordinates tsc)
{
    return (
        x == tsc.x &&
        y == tsc.y &&
        z == tsc.z
    );
}


uint8_t xtp_compare_tsc(
    TouchScreen_Coordinates c,
    TouchScreen_Coordinates tsc)
{
    return (
        c.x == tsc.x &&
        c.y == tsc.y &&
        c.z == tsc.z
    );
}
