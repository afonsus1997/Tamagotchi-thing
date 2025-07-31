#ifndef USB_USER_H
#define USB_USER_H

#include <stdbool.h>
#include "tusb.h"

#ifdef __cplusplus
extern "C" {
#endif

void usb_user_init(void);
void usb_user_task(void);

// USB device lifecycle callbacks
void tud_mount_cb(void);
void tud_umount_cb(void);
void tud_suspend_cb(bool remote_wakeup_en);
void tud_resume_cb(void);

#ifdef __cplusplus
}
#endif

#endif // USB_USER_H
