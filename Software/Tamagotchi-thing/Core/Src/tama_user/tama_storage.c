#include "tama_storage.h"



#ifdef ROM_BUILT_IN
static __attribute__((used, section(".rom"))) const u12_t g_program[];
#include "rom_data.h"
#endif