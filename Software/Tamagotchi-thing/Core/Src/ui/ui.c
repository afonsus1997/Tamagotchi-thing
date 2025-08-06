#include "ui.h"
#include "mui.h"
#include "u8g2.h"
#include "userio.h"


// Global display and UI objects
u8g2_t u8g2;
mui_t mui;

uint8_t is_redraw = 1;

// Define menu field types
muif_t muif_list[] MUI_PROGMEM = {
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),
  MUIF_U8G2_FONT_STYLE(1, u8g2_font_t0_14_tr),
  MUIF_RO("GP",mui_u8g2_goto_data),
  MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pi),
  MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pf),
  MUIF_BUTTON("AB", forms_about_screen)
};


// Define form 1 with 3 menu options
fds_t fds_data[] = {
  MUI_FORM(1)
  MUI_STYLE(1)
  MUI_DATA("GP", 
    MUI_2 "Return to game|"
    MUI_2 "ROM Mgmt|"
    MUI_2 "Save Mgmt|"
    MUI_2 "SW Update|"
    MUI_2 "Stats|"
    MUI_2 "About|")
  MUI_XYA("GC", 0, 28, 0)
  MUI_XYA("GC", 0, 44, 1)
  MUI_XYA("GC", 0, 60, 2)
  MUI_FORM(2)
  MUI_STYLE(0)
  MUI_XY("AB", 0, 0)  // Dummy field to trigger the draw + input handler
  MUI_FORM(99)
  MUI_STYLE(0)
  MUI_XY("AB", 0, 0)  // Dummy field to trigger the draw + input handler
};

void ui_force_redraw(){
  is_redraw = 1;
}

// Initialize display and UI
void ui_init_display() {
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET);

    u8g2_Setup_sh1106_i2c_128x64_noname_f(
        &u8g2, U8G2_R2, u8x8_byte_hw_i2c, u8x8_stm32_gpio_and_delay_cb
    );
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    mui_Init(&mui, &u8g2, fds_data, muif_list, sizeof(muif_list)/sizeof(muif_t));
    mui_GotoForm(&mui, 1, 0);
}


// Call repeatedly in your main loop
void ui_loop() {
  u8g2_SetFont(&u8g2, u8g2_font_helvR08_tr);
  if ( mui_IsFormActive(&mui) )
  {
    /* menu is active: draw the menu */
    if ( is_redraw ) {                  // is any redraw of the menu required?
      u8g2_FirstPage(&u8g2);
      do {
        draw_main_menu_title(5);
        mui_Draw(&mui);

      } while( u8g2_NextPage(&u8g2) );
      is_redraw = 0;                    // menu is now up to date, no redraw required at the moment
    }
  }
}




void ui_process_button_event(int btn_id) {
    switch (btn_id) {
        case BUTTON_LEFT:
            // Move cursor up
            // is_redraw = 1;
            // mui_NextField(&mui);
            btn_states[BUTTON_LEFT] = 1;
            break;
        case BUTTON_RIGHT:
            // Move cursor down
            // is_redraw = 1;
            // mui_PrevField(&mui);
            btn_states[BUTTON_CENTER] = 1;
            break;
        case BUTTON_CENTER:
            // Activate selected field
            // is_redraw = 1;
            // mui_SendSelect(&mui);
            btn_states[BUTTON_RIGHT] = 1;
            break;
        default:
            break;
    }
}