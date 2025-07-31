#include "usb_user.h"
#include "tusb.h"

// TinyUSB Callbacks (Device mode)

void tud_mount_cb(void)
{
    // Device mounted
}

void tud_umount_cb(void)
{
    // Device unmounted
}

void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
    // USB suspended
}

void tud_resume_cb(void)
{
    // USB resumed
}

void usb_user_init(void)
{
    tusb_init();
}

void usb_user_task(void)
{
    tud_task();
}
