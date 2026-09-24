/** ********************************************************************************** **/
/** * @file      sd_card.c                                                           * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            sd_card.c.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      19/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 23/09/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Include Header File. */
#include "sd_card.h"

/* Include Middle Ware. */
#include "Debug.h"
#include "Macros.h"
#include "Returns.h"
#include "ff.h"
#include "integer.h"
#include <stdint.h>

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */

#ifdef SD_DEBUG_LEVEL

    DEBUG_LEVEL_REGISTER(SD_DEBUG_LEVEL)

#else 

    #warning "No debug level ser for the SD_Card API"
    DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

#endif

/* TODO: Add debug configuration. */

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */

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

/* TODO: Add global variables. */

/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */

/* TODO: Add macros. */

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

static et_RET SD_Mount(FATFS *ffs);

static et_RET SD_UnMount(void);

static et_RET SD_OpenFille(FIL *file, 
                           const char *path, 
                           et_FILLE_ACCESS_CONTROL open_mode);

static et_RET SD_CloseFille(FIL *file);

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

et_RET SD_WriteFille(const char *path, const char *buf, uint16_t buf_size)
{
    RET_REGISTER(ret);

    FRESULT result;
    FATFS   ffs;
    FIL     file;
    UINT    bytes_written;

    PRINT_D("[SD] Writing file");

    ret = SD_Mount(&ffs);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not mounted");
        ret = SD_CloseFille(&file);
        ret = SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Mounted");

    ret = SD_OpenFille(&file, path, FILE_WRITE | FILE_OPEN_ALWAYS);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Fille not opened");
        ret = SD_CloseFille(&file);
        ret = SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Fille opened");

    result = f_write(&file, buf, buf_size, &bytes_written);   

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to write to the file");
        ret = SD_CloseFille(&file);
        ret = SD_UnMount();
        return -RET_NOT_OK;
    }

    ret = SD_CloseFille(&file);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Fille not closed");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Fille opened");
    
    ret = SD_UnMount();

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not unmounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Unmounted");
    return RET_OK;
}

et_RET SD_ReadFille(const char *path, char *buf, uint16_t buf_size)
{
    RET_REGISTER(ret);

    FRESULT result;
    FATFS   ffs;
    FIL     file;
    UINT    bytes_read = 0;

    PRINT_D("[SD] Reading file");

    ret = SD_Mount(&ffs);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not mounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Mounted");

    ret = SD_OpenFille(&file, path, FILE_READ);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] File not opened with reason %d", result);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] File opened");

    result = f_read(&file, buf, buf_size, &bytes_read);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to read file");
        SD_CloseFille(&file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    if (bytes_read != buf_size)
    {
        PRINT_E("[SD] Unable to read all bytes");
        SD_CloseFille(&file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    ret = SD_CloseFille(&file);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] File not closed");
        SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] File closed");

    ret = SD_UnMount();

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not unmounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Unmounted");

    return RET_OK;
}

et_RET SD_ReadFille_WithJump(const char *path, char *buf, uint16_t buf_size, unsigned long ofset)
{
    RET_REGISTER(ret);

    FRESULT result;
    FATFS   ffs;
    FIL     file;
    UINT    bytes_read = 0;

    PRINT_D("[SD] Reading file");

    ret = SD_Mount(&ffs);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not mounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Mounted");

    ret = SD_OpenFille(&file, path, FILE_READ);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] File not opened with reason %d", result);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] File opened");

    result = f_lseek( &file, (DWORD) ofset);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to ofset file");
        SD_CloseFille(&file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    result = f_read(&file, buf, buf_size, &bytes_read);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to read file");
        SD_CloseFille(&file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    if (bytes_read != buf_size)
    {
        PRINT_E("[SD] Unable to read all bytes");
        SD_CloseFille(&file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    ret = SD_CloseFille(&file);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] File not closed");
        SD_UnMount();
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] File closed");

    ret = SD_UnMount();

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not unmounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Unmounted");

    return RET_OK;
}

et_RET SD_CreadeDir(const char *path)
{
    
    RET_REGISTER(ret);

    FRESULT result;
    FATFS   ffs;

    PRINT_D("[SD] Reading file");

    ret = SD_Mount(&ffs);

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not mounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Mounted");

    result = f_mkdir((const TCHAR *)path);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to creade fir");;
        SD_UnMount();
        return -RET_NOT_OK;
    }

    ret = SD_UnMount();

    if (CHECK_RET_ERROR(ret))
    {
        PRINT_E("[SD] Not unmounted");
        return -RET_NOT_OK;
    }

    PRINT_I("[SD] Unmounted");

    return RET_OK;
}

/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

static et_RET SD_Mount(FATFS *ffs)
{
    FRESULT result;
    DWORD   fre_clust;
    FATFS   *space;

    PRINT_D("[SD] Mounting the SD_Card");

    if (CHECK_PTR(ffs))
    {
        PRINT_E("[SD] Error NULL ptr");
        return -RET_NULL_PTR;
    }

    result = f_mount(ffs, "", 0);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Error Mounting the SD_Card");
        return -RET_NOT_OK;
    }

    PRINT_D("[SD] SD_Card Mounted");

    result = f_getfree("", &fre_clust, &space);

    return RET_OK;
}

static et_RET SD_UnMount(void)
{
    FRESULT result;
    PRINT_D("[SD] Unmounting the SD_Card");
    
    result = f_mount(NULL, "", 0);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Error Unmounting the SD_Card");
        return -RET_NOT_OK;
    }

    PRINT_D("[SD] SD_Card Unmounted");

    return RET_OK;
} 

static et_RET SD_OpenFille(FIL *file, const char *path, et_FILLE_ACCESS_CONTROL open_mode)
{
    FRESULT result;
    PRINT_D("[SD] Opening file %s", path);

    if (CHECK_PTR(file))
    {
        PRINT_E("[SD] Error NULL ptr");
        return -RET_NULL_PTR;
    }

    if (CHECK_PTR(path))
    {
        PRINT_E("[SD] Error NULL ptr");
        return -RET_NULL_PTR;
    }

    result = f_open(file, path, (BYTE)open_mode);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Error opening file reason %d", result);
        return -RET_NOT_OK;
    }

    PRINT_D("[SD] File opened");

    return RET_OK;
}

static et_RET SD_CloseFille(FIL *file)
{
    FRESULT result;
    PRINT_D("[SD] Closing file");

    if (CHECK_PTR(file))
    {
        PRINT_E("[SD] Error NULL ptr");
        return -RET_NULL_PTR;
    }

    result = f_close(file);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Error closing file");
        return -RET_NOT_OK;
    }

    PRINT_D("[SD] File closed");

    return RET_OK;
}

/* TODO: Add private functions. */

/* -- End of file -- */
