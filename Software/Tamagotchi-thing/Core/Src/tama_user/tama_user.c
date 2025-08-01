#include "tama_user.h"

static uint16_t current_freq = 0; 
static uint8_t runOnceBool = 0;
static unsigned long lastSaveTimestamp = 0;

static bool_t matrix_buffer[LCD_HEIGHT][LCD_WIDTH] = {{0}};
static bool_t icon_buffer[ICON_NUM] = {0};

/* No need to support breakpoints */
static void * hal_malloc(u32_t size)
{
	return NULL;
}

static void hal_free(void *ptr)
{
}

static void hal_halt(void)
{
}

/* No need to support logs */
static bool_t hal_is_log_enabled(log_level_t level)
{
	return 0;
}

static void hal_log(log_level_t level, char *buff, ...)
{
}

static timestamp_t hal_get_timestamp(void)
{
	// return (timestamp_t) (time_get() << time_shift);
}

static void hal_sleep_until(timestamp_t ts)
{
	/* Since TamaLIB is always late in implementations without mainloop,
	 * notify the cpu job that TamaLIB catched up instead of waiting
	 */
	// if ((int32_t) (ts - hal_get_timestamp()) > 0) {
		// tamalib_is_late = 0;
	// }
}

static void hal_update_screen(void)
{
}

static void hal_set_lcd_matrix(u8_t x, u8_t y, bool_t val)
{
	matrix_buffer[y][x] = val;
}

static void hal_set_lcd_icon(u8_t icon, bool_t val)
{
	if (icon == 7 && icon_buffer[icon] != val) {
		/* The Tamagotchi started or stopped calling */
		// if (val && menu_is_visible()) {
			// menu_close();
		// }

		// is_calling = val;

		// update_led();
	}

	icon_buffer[icon] = val;
}

static void hal_set_frequency(u32_t freq)
{
	// speaker_set_frequency(freq);
}

static void hal_play_frequency(bool_t en)
{
	// speaker_enable((uint8_t) (en && config.speaker_enabled));
}

static int hal_handler(void)
{
	return 0;
}

static hal_t hal = {
	.malloc = &hal_malloc,
	.free = &hal_free,
	.halt = &hal_halt,
	.is_log_enabled = &hal_is_log_enabled,
	.log = &hal_log,
	.sleep_until = &hal_sleep_until,
	.get_timestamp = &hal_get_timestamp,
	.update_screen = &hal_update_screen,
	.set_lcd_matrix = &hal_set_lcd_matrix,
	.set_lcd_icon = &hal_set_lcd_icon,
	.set_frequency = &hal_set_frequency,
	.play_frequency = &hal_play_frequency,
	.handler = &hal_handler,
};



static void tama_draw_tamalib_screen(void)
{
	uint8_t i, j;

	// Dot matrix pixels
	for (j = 0; j < LCD_HEIGHT; j++) {
		for (i = 0; i < LCD_WIDTH; i++) {
			if (matrix_buffer[j][i]) {
				u8g2_DrawBox(&u8g2, 
				             i * PIXEL_SIZE + LCD_OFFET_X, 
				             j * PIXEL_SIZE + LCD_OFFET_Y, 
				             PIXEL_SIZE, 
				             PIXEL_SIZE);
			}
		}
	}

	// Icons
	for (i = 0; i < ICON_NUM; i++) {
		if (icon_buffer[i]) {
			uint8_t icon_x = (i % 4) * ICON_STRIDE_X + ICON_OFFSET_X;
			uint8_t icon_y = (i / 4) * ICON_STRIDE_Y + ICON_OFFSET_Y;

			for (uint8_t y = 0; y < ICON_SIZE; y++) {
				for (uint8_t x = 0; x < ICON_SIZE; x++) {
					if (icons[i][y][x]) {
						u8g2_DrawPixel(&u8g2, icon_x + x, icon_y + y);
					}
				}
			}
		}
	}
}