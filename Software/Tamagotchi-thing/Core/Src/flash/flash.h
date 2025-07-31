#ifndef __FLASH__H__
#define __FLASH__H__

#include <stdint.h>

#include "main.h"


/* Storage related offsets and sizes */
#define STORAGE_BASE_ADDRESS					0x800D000

#define STORAGE_SIZE						0x13000
#define STORAGE_PAGE_SIZE					32 // 128B in words (sizeof(uint32_t))

#define STORAGE_ROM_OFFSET					0x0
#define STORAGE_ROM_SIZE					0xC00 // 12KB in words (sizeof(uint32_t))

#define STORAGE_FS_OFFSET					0xC00
#define STORAGE_FS_SIZE						0x4000 // 64KB in words (sizeof(uint32_t))


int8_t storage_read(uint32_t offset, uint32_t *data, uint32_t length);
int8_t storage_write(uint32_t offset, uint32_t *data, uint32_t length);
int8_t storage_erase(void);

#endif  //!__FLASH__H__