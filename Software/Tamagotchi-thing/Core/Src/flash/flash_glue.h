#ifndef __FLASH_GLUE__H__
#define __FLASH_GLUE__H__

#include "ff_gen_drv.h"
#include "flash.h"

void fs_ll_init(void);

int8_t fs_ll_mount(void);
int8_t fs_ll_umount(void);

static DSTATUS storage_drv_initialize(BYTE lun);

static DSTATUS storage_drv_status(BYTE lun);

static DRESULT storage_drv_read(BYTE lun, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
static DRESULT storage_drv_write(BYTE lun, const BYTE *buff, DWORD sector, UINT count);
#endif

#if _USE_IOCTL == 1
static DRESULT storage_drv_ioctl(BYTE lun, BYTE cmd, void *buff);
#endif

static Diskio_drvTypeDef storage_drv_driver;

void fs_ll_init(void);

int8_t fs_ll_mount(void);

int8_t fs_ll_umount(void);

#endif  //!__FLASH_GLUE__H__