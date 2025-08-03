#ifndef __TAMA_STORAGE__H__
#define __TAMA_STORAGE__H__

#include "main.h"
#include "log.h"
#include "flash.h"
#include "hal_types.h"


#define ROM_BUILT_IN

#ifdef ROM_BUILT_IN
// static __attribute__((used, section(".rom"))) const u12_t g_program[];
#include "rom_12bit.h"
#endif

#endif  //!__TAMA_STORAGE__H__