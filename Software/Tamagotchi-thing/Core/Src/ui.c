#include "ui.h"


static u8g2_t u8g2;
// Create MUI object
static mui_t ui;


muif_t muif_list[] = {  
  MUIF_VARIABLE("BN", NULL, mui_u8g2_btn_exit_wm_fi)
};

fds_t fds_data[] = 
MUI_FORM(1)
MUI_XYT("BN", 64, 16, " Select Me ");


ui_init_display(){
  HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET);
  // ssd1306_Init();
  // ssd1306_SetCursor(2, 1);
  // ssd1306_WriteString("Test", Font_7x10, White);
  // ssd1306_UpdateScreen();

  u8g2_Setup_sh1106_i2c_128x64_noname_f(
    &u8g2,
    U8G2_R0,
    u8x8_byte_hw_i2c,
    u8x8_stm32_gpio_and_delay_cb
  );
  u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
  u8g2_SetPowerSave(&u8g2, 0); // wake up display
  u8g2_ClearDisplay(&u8g2);
  u8g2_UpdateDisplay(&u8g2);
  u8g2_SetDrawColor(&u8g2, 1);
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_helvR08_tr);
  mui_Init(&ui, &u8g2, &fds_data, &muif_list, sizeof(muif_list)/sizeof(muif_t));
  mui_GotoForm(&ui,/* form_id= */ 1, /* initial_cursor_position= */ 0);
  u8g2_ClearBuffer(&u8g2);
  mui_Draw(&ui);
  // u8g2_UpdateDisplay(&u8g2);
  u8g2_SendBuffer(&u8g2);
}