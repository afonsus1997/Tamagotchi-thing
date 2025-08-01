#include "usb_user_cdc.h"

void cdc_printf(const char* fmt, ...)
{
    char buf[128];  // Adjust size as needed
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    if (tud_cdc_connected()) {
        // Wait for enough room in TX buffer
        while (!tud_cdc_write_available()) {
            tud_task();  // Poll TinyUSB while waiting
        }

        tud_cdc_write(buf, len);
        tud_cdc_write_flush();  // Push data out immediately
    }
}

int _write(int fd, const void* buf, size_t count)
{
    if (tud_cdc_connected()) {
        tud_cdc_write(buf, count);
        tud_cdc_write_flush();
        return count;
    }
    return 0; // or -1 for error
}

void cdc_log_write(const char* data, size_t len)
{
    if (tud_cdc_connected()) {
        tud_cdc_write(data, len);
        tud_cdc_write_flush();
    }
}