#include "forms.h"
#include "mui.h"



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

void draw_main_menu_title(uint8_t battery){
// Draw title and line at top
  u8g2_SetFontMode(&u8g2, 1);
  u8g2_SetBitmapMode(&u8g2, 1);
  u8g2_DrawStr(&u8g2, 3, 13, "Main Menu");
  u8g2_DrawLine(&u8g2, 0, 15, 127, 15);
  u8g2_DrawXBM(&u8g2, 98, 4, 26, 8, image_Battery_bits);
  drawBatteryLevel(100, 6, 75);  // Draw battery with 75% fill
  if(battery <= 5)
    u8g2_DrawXBM(&u8g2, 88, 4, 9, 8, image_Alert_bits);

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
    case MUIF_MSG_CURSOR_ENTER:
      return mui_GotoFormAutoCursorPosition(ui, ui->last_form_id[ui->last_form_stack_pos]);  }
  return 0;
}