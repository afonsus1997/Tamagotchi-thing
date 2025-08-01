#ifndef __TAMA_USER__H__
#define __TAMA_USER__H__

#include "log.h"
#include "ui.h"
#include "main.h"
#include "u8g2.h"
#include "hal_types.h"
#include "hal.h"
#include "hw.h"
#include "tama_icons.h"

/* Tmama stuff */
#include "cpu.h"
#include "hw.h"
#include "tamalib.h"

#define TAMA_DISPLAY_FRAMERATE  3   // 3 is optimal for Arduino UNO
#define ENABLE_TAMA_SOUND
#define ENABLE_AUTO_SAVE_STATUS
#define AUTO_SAVE_MINUTES 60    // Auto save for every hour (to preserve EEPROM lifespan)
#define ENABLE_LOAD_STATE_FROM_EEPROM 

#define PIXEL_SIZE					3
#define ICON_SIZE					8
#define ICON_NUM 8
#define ICON_STRIDE_X					24
#define ICON_STRIDE_Y					56
#define ICON_OFFSET_X					24
#define ICON_OFFSET_Y					0
#define LCD_OFFET_X					16
#define LCD_OFFET_Y					8

//#define ENABLE_DUMP_STATE_TO_SERIAL_WHEN_START
//#define ENABLE_SERIAL_DEBUG_INPUT
//#define ENABLE_LOAD_HARCODED_STATE_WHEN_START


#endif  //!__TAMA_USER__H__
