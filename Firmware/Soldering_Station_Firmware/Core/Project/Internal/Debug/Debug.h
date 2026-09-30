/** ********************************************************************************** **/
/** * @file      Debug.h                                                             * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            Debug.h.                                                            * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      25/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 30/09/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

#include "Proj.h"

#if (ENABLE_PROJECT_LOGGER == DISABLED)

    #include "Debug_NoOutput.h"

#elif (ENABLE_PROJECT_LOGGER == ENABLED)

    #include "Debug_Output.h"

#endif 


#endif /* __DEBUG_H__ */

/* -- End of file -- */