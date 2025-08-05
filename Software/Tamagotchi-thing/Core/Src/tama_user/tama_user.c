#include "tama_user.h"
#include "ssd1306.h"
#include "tamalib.h"
#include "u8g2.h"
#include "log.h"

uint16_t current_freq = 0;
uint8_t runOnceBool = 0;
unsigned long lastSaveTimestamp = 0;

// Buffers for LCD matrix and icon state
bool_t matrix_buffer[LCD_HEIGHT][LCD_WIDTH] = {{0}};
bool_t icon_buffer[ICON_NUM] = {0};

static bool_t is_calling = 0;
uint32_t time_shift = 0;

// ---------------------------------------------
// HAL: Memory Management
// ---------------------------------------------
void *hal_malloc(u32_t size) { return NULL; }
void hal_free(void *ptr) {}
void hal_halt(void) { LOG_ERROR("Tamalib halted!\n"); }

// ---------------------------------------------
// HAL: Logging
// ---------------------------------------------
bool_t hal_is_log_enabled(log_level_t level) { return 0; }

void hal_log(log_level_t level, char *buff, ...) {
    va_list args;
    va_start(args, buff);
    vlog_printf_level(level, buff, args);
    va_end(args);
}



void hal_sleep_until(timestamp_t t) {
    time_wait_until(t); // Blocks until target timestamp is reached
}

// ---------------------------------------------
// HAL: LCD Drawing
// ---------------------------------------------
void hal_update_screen(void) {
    u8g2_ClearBuffer(&u8g2);               // Clear frame buffer *before* drawing
    u8g2_SetDrawColor(&u8g2, White);       // Set drawing color
    tama_draw_tamalib_screen();           // Draw current frame contents
    u8g2_SendBuffer(&u8g2);               // Send buffer to screen
}

void hal_set_lcd_matrix(u8_t x, u8_t y, bool_t val) {
    if (x < LCD_WIDTH && y < LCD_HEIGHT) {
        matrix_buffer[y][x] = val;
    }
}

void hal_set_lcd_icon(u8_t icon, bool_t val) {
    if (icon < ICON_NUM) {
        LOG_INFO("hal_set_lcd_icon: icon=%d, val=%d", icon, val);
        icon_buffer[icon] = val;

        if (icon == 7) {  // Handle "calling" state if needed
            is_calling = val;
        }
    }
}

// ---------------------------------------------
// HAL: Audio (stubbed)
// ---------------------------------------------
void hal_set_frequency(u32_t freq) {
    current_freq = freq;
    // Setup buzzer frequency if needed
}

void hal_play_frequency(bool_t en) {
    if (en) {
        // enable buzzer using current_freq
    } else {
        // disable buzzer
    }
}

// ---------------------------------------------
// HAL: Dummy Event Handler
// ---------------------------------------------
int hal_handler(void) {
    return 0;
}

// ---------------------------------------------
// HAL Struct
// ---------------------------------------------
hal_t hal = {
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

// ---------------------------------------------
// Tamalib Initialization
// ---------------------------------------------

timestamp_t hal_get_timestamp(void) {
    return (timestamp_t)(time_get());  // no shift
}

void tama_user_init(void) {
    tamalib_register_hal(&hal);

    // No need to compute time_shift
    uint32_t effective_freq = MCU_TIME_FREQ_HZ;  // 131072

    LOG_INFO("Initializing Tamalib with freq = %lu Hz", effective_freq);

    if (tamalib_init((const u12_t *) g_program, NULL,     if (tamalib_init((const u12_t *) g_program, NULL, 1000000)) {
)) {
        LOG_ERROR("Tamalib initialization error!");
    }

    cpu_set_speed(1);
    tamalib_reset();
    tamalib_set_exec_mode(EXEC_MODE_RUN);
}
// ---------------------------------------------
// LCD Drawing Logic
// ---------------------------------------------
void tama_draw_tamalib_screen(void) {
    uint8_t i, j;

    // Dot matrix (pixels)
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
