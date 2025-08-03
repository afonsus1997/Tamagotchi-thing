#include "tama_user.h"
#include "ssd1306.h"
#include "u8g2.h"


uint16_t current_freq = 0; 
uint8_t runOnceBool = 0;
unsigned long lastSaveTimestamp = 0;
uint16_t time_shift = 0;

bool_t matrix_buffer[LCD_HEIGHT][LCD_WIDTH] = {{0}};
bool_t icon_buffer[ICON_NUM] = {0};


hal_t hal = {
	.malloc = &hal_malloc, //OK
	.free = &hal_free, //OK
	.halt = &hal_halt, //OK
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

void tama_user_calculate_time_shift(){
	while (((MCU_TIME_FREQ_X1000 << time_shift) < TAMALIB_FREQ * 1000) || (MCU_TIME_FREQ_X1000 << time_shift) % 1000) {
		time_shift++;
	}
}

void tama_user_init(){
	tama_user_calculate_time_shift();
	tamalib_register_hal(&hal);
	if (tamalib_init((const u12_t *) g_program, NULL, (MCU_TIME_FREQ_X1000 << time_shift)/1000)) {
			LOG_ERROR("Tamalib initialization error!");
	}
}


/* No need to support breakpoints */
void * hal_malloc(u32_t size)
{
	return NULL;
}

void hal_free(void *ptr)
{
}

void hal_halt(void)
{
	LOG_ERROR("Internal TAMALIB ERROR!\n");
}

/* No need to support logs */
bool_t hal_is_log_enabled(log_level_t level)
{
	return 0;
}

void hal_log(log_level_t level, char *buff, ...)
{
		va_list args;
    va_start(args, buff);
    vlog_printf_level(level, buff, args);
    va_end(args);
}

timestamp_t hal_get_timestamp(void)
{
    return (timestamp_t)(time_get() << time_shift);
}

// extern volatile int tamalib_is_late;  // make sure this is declared somewhere

void hal_sleep_until(timestamp_t ts)
{
    while ((int32_t)(ts - hal_get_timestamp()) > 0) {
        // Optionally, add a small delay to prevent full CPU spin
        time_delay(US_TO_MCU_TIME(50));  // delay ~50 microseconds
    }

    // tamalib_is_late = 0;
}

void hal_update_screen(void)
{
 	u8g2_ClearBuffer(&u8g2);       // Clear previous frame
	u8g2_SetDrawColor(&u8g2, White);   // Draw in white
	tama_draw_tamalib_screen();    // Draw pixel data
	u8g2_SendBuffer(&u8g2);
}


void hal_set_lcd_matrix(u8_t x, u8_t y, bool_t val)
{
	matrix_buffer[y][x] = val;
}

static bool_t is_calling = 0;

// void hal_set_lcd_icon(u8_t icon, bool_t val)
// {
// 	if (icon == 7 && icon_buffer[icon] != val) {
// 		/* The Tamagotchi started or stopped calling */
// 		// if (val && menu_is_visible()) {
// 			// menu_close();
// 		// }

// 		// is_calling = val;

// 		update_led();
// 	}

// 	icon_buffer[icon] = val;
// }

void hal_set_lcd_icon(u8_t icon, bool_t val)
{
	LOG_INFO("hal_set_lcd_icon: icon=%d, val=%d", icon, val);
	icon_buffer[icon] = val;
}

void hal_set_frequency(u32_t freq)
{
	// speaker_set_frequency(freq);
}

void hal_play_frequency(bool_t en)
{
	// speaker_enable((uint8_t) (en && config.speaker_enabled));
}

int hal_handler(void)
{
	return 0;
}





void tama_draw_tamalib_screen(void)
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