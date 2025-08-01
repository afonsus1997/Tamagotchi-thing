#include "forms.h"
#include "mui.h"


uint8_t forms_main_menu(mui_t *ui, uint8_t msg) {
    u8g2_t *u8g2 = mui_get_U8g2(ui);
    uint8_t arg = ui->arg;

    switch (msg) {
        case MUIF_MSG_DRAW:
            if (mui_GetSelectableFieldTextOption(ui, ui->last_form_fds, arg + ui->form_scroll_top)) {
                const char *label = ui->text + 1; // Skip first char (form ID)

                if (mui_IsCursorFocus(ui)) {
                    // Inverted highlight
                    u8g2_SetDrawColor(u8g2, 1);
                    u8g2_DrawBox(u8g2, 0, ui->y - 12, 128, 14);
                    u8g2_SetDrawColor(u8g2, 0);
                } else {
                    u8g2_SetDrawColor(u8g2, 1);
                }

                u8g2_SetFont(u8g2, u8g2_font_t0_14_tr);
                u8g2_DrawStr(u8g2, 3, ui->y, label);
            }
            break;

        case MUIF_MSG_CURSOR_SELECT:
            if (mui_GetSelectableFieldTextOption(ui, ui->last_form_fds, arg + ui->form_scroll_top)) {
                mui_SaveFormWithCursorPosition(ui, arg + ui->form_scroll_top);
                mui_SaveCursorPosition(ui, arg + ui->form_scroll_top);
                return mui_GotoFormAutoCursorPosition(ui, (uint8_t)ui->text[0]);
            }
            break;

        // default:
            // return mui_u8g2_u8_opt_child_mse_common(ui, msg);
    }

    return 0;
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