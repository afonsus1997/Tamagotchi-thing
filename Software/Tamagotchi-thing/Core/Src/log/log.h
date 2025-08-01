#pragma once

#include <stdint.h>
#include <stddef.h>
#include "main.h"
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} log_level_t;

void log_init(void (*write_fn)(const char*, size_t));
void log_init_printf(uint8_t level);
void log_set_level(log_level_t level);
void log_set_timestamp_fn(uint32_t (*ts_fn)(void));
void log_printf_level(log_level_t level, const char* fmt, ...);

#define LOG_DEBUG(...)   log_printf_level(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOG_INFO(...)    log_printf_level(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...)    log_printf_level(LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_ERROR(...)   log_printf_level(LOG_LEVEL_ERROR, __VA_ARGS__)
