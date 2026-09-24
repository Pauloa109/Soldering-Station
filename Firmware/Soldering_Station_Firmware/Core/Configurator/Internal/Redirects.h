/** ********************************************************************************** **/
/** * @file      Redirects.h                                                         * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Redirects.h.                                                        * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      17/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 17/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __REDIRECTS_H__
#define __REDIRECTS_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Configurator.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

#if (PROJECT_CODE_CONFIGURATOR == CODE_CONFIGURATOR_CMX)

    #if (PROJECT_REDIRECT_PRINTF_ENABLE == 1)

        #if (PROJECT_REDIRECT_PRINTF_TARGET == PROJECT_REDIRECT_PRINTF_TARGET_USB)

            #include "USB_DEVICE/App/usbd_cdc_if.h"

            int _write(int file, char *ptr, int len)
            {
                HAL_USB_(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
                return len;
            }

        #elif (PROJECT_REDIRECT_PRINTF_TARGET == PROJECT_REDIRECT_PRINTF_TARGET_UART)

            int _write(int file, char *ptr, int len)
            {
                HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
                return len;
            }

        #else

            #warning "Unknown printf redirect target"

        #endif

    #else

        #warning "No printf redirect"
    
    #endif

#else

    #warning "Unknown PROJECT_CODE_CONFIGURATOR"

#endif 

/* TODO: Add public function prototypes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __REDIRECTS_H__ */

/* -- End of file -- */
