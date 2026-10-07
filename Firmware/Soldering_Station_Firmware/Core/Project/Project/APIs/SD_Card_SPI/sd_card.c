/** ********************************************************************************** **/
/** * @file      sd_card.c                                                           * **/
/** * @brief     This file contains all the functions implementation or prototypes of  * **/
/** *            sd_card.c.                                                          * **/
/** * @author    Paulo Peixoto                                                       * **/
/** *                                                                                * **/
/** * @date      19/09/2026                                                          * **/
/** * @version   V...                                                                * **/
/** *                                                                                * **/
/** * Last modified on 02/10/2026                                                    * **/
/** ********************************************************************************** **/

/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */

/* Core Include. */
#include "Core_Include.h"

/* Include Header File. */
#include "sd_card.h"

/* Inclued Project Level Configurator. */
#include "Proj.h"
#include "Returns.h"

/* TODO: Add includes. */

/* ************************************************************************************ */
/* * Debug                                                                            * */
/* ************************************************************************************ */
#if (PROJECT_ENABLE_LOGGER == ENABLED)

    #if SD_DEBUG_LEVEL

        DEBUG_LEVEL_REGISTER(SD_DEBUG_LEVEL)

    #else 

        #warning "No debug level ser for the SD_Card API"

        DEBUG_LEVEL_REGISTER(DEBUG_LEVEL_D)

    #endif

#else 

    MODULE_DEBUG_REGISTER(DEBUG_LEVEL_N, SD_module)

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

/* TODO: Add private function prototypes. */

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET SD_Mount(FATFS *ffs)
{
    FRESULT result;

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

    return RET_OK;
}

et_RET SD_UnMount(void)
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

et_RET SD_OpenFille(FIL *file, const char *path, et_FILLE_ACCESS_CONTROL open_mode)
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

et_RET SD_CloseFille(FIL *file)
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

et_RET SD_WriteFille(FIL *file, const char *buf, uint16_t buf_size)
{
    RET_REGISTER(ret);

    FRESULT result;
    UINT    bytes_written;

    result = f_write(file, buf, buf_size, &bytes_written);   

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to write to the file");
        ret = SD_CloseFille(file);
        ret = SD_UnMount();
        return -RET_NOT_OK;
    }

    return RET_OK;
}

et_RET SD_ReadFille(FIL *file, char *buf, uint16_t buf_size)
{
    FRESULT result;
    UINT    bytes_read = 0;

    result = f_read(file, buf, buf_size, &bytes_read);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to read file");
        SD_CloseFille(file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    if (bytes_read != buf_size)
    {
        PRINT_E("[SD] Unable to read all bytes");
        SD_CloseFille(file);
        SD_UnMount();
        return -RET_NOT_OK;
    }

    return RET_OK;
}

et_RET SD_ReadFille_WithJump(FIL *file, char *buf, uint16_t buf_size, DWORD offset)
{
    FRESULT result;
    UINT    bytes_read = 0;

    if (CHECK_PTR(file) || CHECK_PTR(buf))
    {
        PRINT_E("[SD] NULL file or buffer passed to offset read");
        return -RET_NULL_PTR;
    }

    result = f_lseek(file, offset);

    if (result != FR_OK)
    {
        PRINT_E("[SD] f_lseek failed: result=%d, offset=%lu",
                (int)result, (unsigned long)offset);
        return -RET_NOT_OK;
    }

    if (f_tell(file) != offset)
    {
        PRINT_E("[SD] f_lseek clipped offset: requested=%lu, actual=%lu, size=%lu",
                (unsigned long)offset,
                (unsigned long)f_tell(file),
                (unsigned long)f_size(file));
        return -RET_NOT_OK;
    }

    if ((DWORD)buf_size > f_size(file) - offset)
    {
        PRINT_E("[SD] Offset read exceeds file size: offset=%lu, bytes=%u, size=%lu",
                (unsigned long)offset,
                (unsigned int)buf_size,
                (unsigned long)f_size(file));
        return -RET_NOT_OK;
    }

    result = f_read(file, buf, buf_size, &bytes_read);

    if (result != FR_OK)
    {
        PRINT_E("[SD] f_read after seek failed: result=%d, offset=%lu",
                (int)result, (unsigned long)offset);
        return -RET_NOT_OK;
    }

    if (bytes_read != buf_size)
    {
        PRINT_E("[SD] Short read after seek: requested=%u, read=%u, offset=%lu",
                (unsigned int)buf_size,
                (unsigned int)bytes_read,
                (unsigned long)offset);
        return -RET_NOT_OK;
    }

    return RET_OK;
}

et_RET SD_CreadeDir(const char *path)
{
    FRESULT result;

    result = f_mkdir((const TCHAR *)path);

    if (result != FR_OK)
    {
        PRINT_E("[SD] Unable to creade fir");;
        SD_UnMount();
        return -RET_NOT_OK;
    }

    return RET_OK;
}

/* TODO: Add public functions. */

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

/* TODO: Add private functions. */

/* -- End of file -- */
