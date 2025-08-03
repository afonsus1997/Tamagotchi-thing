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
#include "rtc.h"
#include "ui.h"
#include "tim.h"
#include "tama_storage.h"

#define TAMA_DISPLAY_FRAMERATE  3   // 3 is optimal for Arduino UNO
#define ENABLE_TAMA_SOUND
#define ENABLE_AUTO_SAVE_STATUS
#define AUTO_SAVE_MINUTES 60    // Auto save for every hour (to preserve EEPROM lifespan)
#define ENABLE_LOAD_STATE_FROM_EEPROM 

#define ICON_SIZE					8
#define ICON_NUM 8
#define ICON_STRIDE_X					24
#define ICON_STRIDE_Y					56
#define ICON_OFFSET_X					24
#define ICON_OFFSET_Y					0
#define LCD_OFFET_X					0//16
#define LCD_OFFET_Y					0//8

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64

// Calculate scale that fits both width and height
#define PIXEL_SIZE   ( (SCREEN_WIDTH / LCD_WIDTH < SCREEN_HEIGHT / LCD_HEIGHT) ? \
                       (SCREEN_WIDTH / LCD_WIDTH) : (SCREEN_HEIGHT / LCD_HEIGHT) )

// Calculate offsets to center the image
#define LCD_OFFSET_X  ((SCREEN_WIDTH - (LCD_WIDTH * PIXEL_SIZE)) / 2)
#define LCD_OFFSET_Y  ((SCREEN_HEIGHT - (LCD_HEIGHT * PIXEL_SIZE)) / 2)

#define TAMALIB_FREQ					32768 // Hz

//#define ENABLE_DUMP_STATE_TO_SERIAL_WHEN_START
//#define ENABLE_SERIAL_DEBUG_INPUT
//#define ENABLE_LOAD_HARCODED_STATE_WHEN_START


void *hal_malloc(u32_t size);
void hal_free(void *ptr);
void hal_halt(void);

bool_t hal_is_log_enabled(log_level_t level);
void hal_log(log_level_t level, char *buff, ...);

timestamp_t hal_get_timestamp(void);
void hal_sleep_until(timestamp_t ts);

void hal_update_screen(void);
void hal_set_lcd_matrix(u8_t x, u8_t y, bool_t val);
void hal_set_lcd_icon(u8_t icon, bool_t val);

void hal_set_frequency(u32_t freq);
void hal_play_frequency(bool_t en);

int hal_handler(void);

void tama_user_init();

void tama_draw_tamalib_screen(void);


#endif  //!__TAMA_USER__H__
