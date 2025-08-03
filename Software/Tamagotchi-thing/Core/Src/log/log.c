#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static log_level_t current_level = LOG_INFO;
static void (*log_write_fn)(const char*, size_t) = NULL;
static uint32_t (*timestamp_fn)(void) = NULL;

static const char* get_level_str(log_level_t level) {
    switch (level) {
        case LOG_ERROR:  return "ERROR";
        case LOG_INFO:   return "INFO";
        case LOG_MEMORY: return "MEMORY";
        case LOG_CPU:    return "CPU";
        case LOG_INT:    return "DEBUG";
        default:         return "UNKNOWN";
    }
}

void log_init(void (*write_fn)(const char*, size_t)) {
    log_write_fn = write_fn;
}

void log_set_level(log_level_t level) {
    current_level = level;
}

void log_set_timestamp_fn(uint32_t (*ts_fn)(void)) {
    timestamp_fn = ts_fn;
}




void vlog_printf_level(log_level_t level, const char* fmt, va_list args) {
    if ((current_level & level) == 0 || log_write_fn == NULL) {
        return;
    }

    char buf[256];
    int len = 0;

    if (timestamp_fn) {
        len += snprintf(buf + len, sizeof(buf) - len, "[%lu] ", timestamp_fn());
    }

    len += snprintf(buf + len, sizeof(buf) - len, "[%s] ", get_level_str(level));

    len += vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    if (len < (int)(sizeof(buf) - 2)) {
        buf[len++] = '\n';
        buf[len] = '\0';
    }

    log_write_fn(buf, len);
}

void log_printf_level(log_level_t level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vlog_printf_level(level, fmt, args);
    va_end(args);
}


void log_write_printf(const char* str, size_t len) {
    printf("%.*s", (int)len, str);
}

void log_init_printf(uint8_t level) {
    log_init(log_write_printf);
    log_set_level(level);
    log_set_timestamp_fn(HAL_GetTick);
}
