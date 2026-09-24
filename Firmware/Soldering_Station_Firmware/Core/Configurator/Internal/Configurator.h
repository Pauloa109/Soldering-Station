/** ********************************************************************************** **/
/** * @file      Configurator.h                                                      * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Configurator.h.                                                     * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      02/09/2026                                                          * **/
/** * @version   V0.0.0                                                              * **/
/** *                                                                                * **/
/** * Last modified on 17/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __CONFIGURATOR_H__
#define __CONFIGURATOR_H__

#ifdef __cplusplus
extern "C" {
#endif
                                           
/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

/* Include Project Configuration File. */
#include "Proj.h"

/* Include Definitions File. */
#include "Internal_Defines.h"

/* ************************************************************************************ */
/* * Manual System Configuration                                                      * */
/* ************************************************************************************ */

#if (ENABLE_AUTO_CONFIGURATOR == 0)

    #define PROJECT_TARGET                    ( TARGET_STM32F1 )

    #define PROJECT_CODE_CONFIGURATOR         ( CODE_CONFIGURATOR_CMX )

#endif


/* ************************************************************************************ */
/* * Auto Configurator                                                                * */
/* ************************************************************************************ */

#if (ENABLE_AUTO_CONFIGURATOR == 1)

    #if defined(STM32F103xB)

        #define PROJECT_TARGET              ( TARGET_STM32F1 )
        #define PROJECT_CODE_CONFIGURATOR   ( CODE_CONFIGURATOR_CMX )

    #else 

        #warning "Automatic Configurator Failed"

    #endif

#endif


/* ************************************************************************************ */
/* * System Definitions                                                               * */
/* ************************************************************************************ */

#if ((PROJECT_TARGET == TARGET_STM32F1) &&                                               \
     (PROJECT_CODE_CONFIGURATOR == CODE_CONFIGURATOR_CMX))
    
    #include "stm32f1xx.h" 

#else

    #error "Target not supported"

#endif     


/* TODO: Add defines. */



#ifdef __cplusplus
}
#endif

#endif /* __CONFIGURATOR_H__ */

/* -- End of file -- */
