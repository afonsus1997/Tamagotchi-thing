#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static log_level_t current_level = LOG_LEVEL_INFO;
static void (*log_write_fn)(const char*, size_t) = NULL;
static uint32_t (*timestamp_fn)(void) = NULL;

static const char* level_str[] = {
    "DEBUG", "INFO", "WARN", "ERROR"
};

void log_init(void (*write_fn)(const char*, size_t))
{
    log_write_fn = write_fn;
}

void log_set_level(log_level_t level)
{
    current_level = level;
}

void log_set_timestamp_fn(uint32_t (*ts_fn)(void))
{
    timestamp_fn = ts_fn;
}

void log_printf_level(log_level_t level, const char* fmt, ...)
{
    if (level < current_level || log_write_fn == NULL) return;

    char buf[256];
    int len = 0;

    // Add timestamp if available
    if (timestamp_fn) {
        len += snprintf(buf + len, sizeof(buf) - len, "[%lu] ", timestamp_fn());
    }

    // Add log level string
    len += snprintf(buf + len, sizeof(buf) - len, "[%s] ", level_str[level]);

    // Format the actual log message
    va_list args;
    va_start(args, fmt);
    len += vsnprintf(buf + len, sizeof(buf) - len, fmt, args);
    va_end(args);

    // Ensure newline
    if (len < (int)(sizeof(buf) - 2)) {
        buf[len++] = '\n';
        buf[len] = '\0';
    }

    log_write_fn(buf, len);
}


static void log_write_printf(const char* str, size_t len) {
    printf("%.*s", (int)len, str);
}

void log_init_printf(uint8_t level)
{
    log_init(log_write_printf);
    log_set_level(level);
    log_set_timestamp_fn(HAL_GetTick);
}
