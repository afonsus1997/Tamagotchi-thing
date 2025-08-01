#if !defined(UI_H)
#define UI_H

#include "main.h"
#include "u8x8_stm32_HAL.h"
#include "u8g2.h"
#include "mui_u8g2.h"
#include "mui.h"
#include "forms.h"
#include "userio.h"
#include "rtc.h"


void ui_init_display();
void ui_loop();
void ui_force_redraw();
void ui_process_button_event(int btn_id);

extern u8g2_t u8g2;
extern mui_t mui;

#endif // UI_H
