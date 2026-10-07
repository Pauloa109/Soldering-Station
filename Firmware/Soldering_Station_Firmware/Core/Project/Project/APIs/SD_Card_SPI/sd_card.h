/** ********************************************************************************** **/
/** * @file      sd_card.h                                                           * **/
/** * @brief     This file contains all the functions prototypes of                  * **/
/** *            sd_card.h.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      19/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 02/10/2026                                                    * **/
/** ********************************************************************************** **/

#ifndef __SD_CARD_H__
#define __SD_CARD_H__

/* ************************************************************************************ */
/* * Public Includes                                                                  * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* Include Middle Ware. */
#include "ff.h"
#include "integer.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************ */
/* * Public Enumerations                                                              * */
/* ************************************************************************************ */

typedef enum
{
    FILE_READ		    = 0x01,
	FILE_OPEN_EXISTING	= 0x00,
	FILE_WRITE			= 0x02,
	FILE_CREATE_NEW		= 0x04,
	FILE_CREATE_ALWAYS	= 0x08,
	FILE_OPEN_ALWAYS    = 0x10
} et_FILLE_ACCESS_CONTROL;

/* TODO: Add enumerations. */

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

et_RET SD_Mount(FATFS *ffs);

et_RET SD_UnMount(void);

et_RET SD_OpenFille(FIL *file, const char *path, et_FILLE_ACCESS_CONTROL open_mode);

et_RET SD_CloseFille(FIL *file);

et_RET SD_WriteFille(FIL *file, const char *buf, uint16_t buf_size);

et_RET SD_ReadFille(FIL *file, char *buf, uint16_t buf_size);

et_RET SD_ReadFille_WithJump(FIL *file, char *buf, uint16_t buf_size, DWORD offset);

et_RET SD_CreadeDir(const char *path);


/* TODO: Add public function prototypes. */

/* ************************************************************************************ */
/* * C++ Support                                                                      * */
/* ************************************************************************************ */

#ifdef __cplusplus
}
#endif

#endif /* __SD_CARD_H__ */

/* -- End of file -- */
