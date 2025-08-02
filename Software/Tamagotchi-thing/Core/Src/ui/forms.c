#include "forms.h"
#include "ui.h"

void drawBatteryLevel(uint8_t x, uint8_t y, uint8_t percent) {
    if (percent > 100) {
        percent = 100;
    }

    const uint8_t max_width = 20;
    const uint8_t height = 4;

    uint8_t fill_width = (percent * max_width) / 100;

    if (fill_width > 0) {
        u8g2_DrawBox(&u8g2, x, y, fill_width, height);
    }

}

void draw_main_menu_title(uint8_t battery) {
    RTC_DateTypeDef gDate;
    RTC_TimeTypeDef gTime;
    char datetime_str[20];

    // Get current RTC time and date
    HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

    // Format as "HH:MM DD/MM/YY" using 24h format
    snprintf(datetime_str, sizeof(datetime_str), "%02u:%02u %02u/%02u/%02u",
             gTime.Hours, gTime.Minutes,
             gDate.Date, gDate.Month, gDate.Year);

    // Draw UI elements
    u8g2_SetFontMode(&u8g2, 1);
    u8g2_SetFont(&u8g2, u8g2_font_t0_12_tr);
    u8g2_SetBitmapMode(&u8g2, 1);
    u8g2_DrawStr(&u8g2, 3, 12, datetime_str);                 // Time/date string
    u8g2_DrawLine(&u8g2, 0, 15, 127, 15);                     // Separator
    u8g2_DrawXBM(&u8g2, 98, 4, 26, 8, image_Battery_bits);    // Battery frame
    drawBatteryLevel(100, 6, battery);                        // Battery level fill

    if (battery <= 5) {
        u8g2_DrawXBM(&u8g2, 88, 4, 9, 8, image_Alert_bits);   // Low battery alert icon
    }
}





uint8_t forms_about_screen(mui_t *ui, uint8_t msg)
{
  u8g2_t *u8g2 = mui_get_U8g2(ui);
  switch(msg)
  {
    case MUIF_MSG_DRAW:
      u8g2_ClearBuffer(u8g2);
      u8g2_SetFontMode(u8g2, 1);
      u8g2_SetBitmapMode(u8g2, 1);
      u8g2_SetFont(u8g2, u8g2_font_t0_12_tr);
      u8g2_DrawStr(u8g2, 16, 13, "Tamagotchi-Thing");
      u8g2_DrawFrame(u8g2, 13, 2, 102, 15);
      u8g2_DrawStr(u8g2, 13, 33, "By Afonso Muralha");
      u8g2_DrawStr(u8g2, 12, 44, "afonsomuralha.com");
      u8g2_DrawStr(u8g2, 13, 60, "Based on OpenTama");
      u8g2_SendBuffer(u8g2);
      break;
    case MUIF_MSG_CURSOR_SELECT:
      ui_force_redraw();  
      return mui_GotoFormAutoCursorPosition(ui, 1); 
  }
  return 0;
}