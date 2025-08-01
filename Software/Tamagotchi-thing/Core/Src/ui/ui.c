#include "ui.h"


// Global display and UI objects
static u8g2_t u8g2;
static mui_t mui;

// Define menu field types
muif_t muif_list[] MUI_PROGMEM = {
    MUIF_RO("GP",mui_u8g2_goto_data),
    MUIF_BUTTON("GC", forms_main_menu),
    MUIF_BUTTON("GC", forms_main_menu),
    MUIF_RO("AB", forms_about_screen)
};

// Define form 1 with 3 menu options
fds_t fds_data[] = {
  MUI_FORM(1)
  MUI_STYLE(0)
  MUI_DATA("GP", 
    MUI_10 "Return to game|"
    MUI_20 "ROM Mgmt|"
    MUI_30 "Save Mgmt|"
    MUI_40 "SW Update|"
    MUI_50 "Stats|"
    MUI_60 "About|")
  MUI_XYA("GC", 0, 28, 0)
  MUI_XYA("GC", 0, 44, 1)
  MUI_XYA("GC", 0, 60, 2)
  MUI_FORM(99)
  MUI_STYLE(0)
  MUI_XY("AB", 0, 0)  // Dummy field to trigger the draw + input handler
};



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
    mui_GotoForm(&mui, 1, 1);
}

// Call repeatedly in your main loop
void ui_loop() {
    u8g2_ClearBuffer(&u8g2);

    // Draw title and line at top
    u8g2_SetFont(&u8g2, u8g2_font_t0_15b_tr);
    u8g2_DrawStr(&u8g2, 3, 13, "Main Menu");
    u8g2_DrawLine(&u8g2, 0, 15, 127, 15);

    // Draw the current form with cursor and menu entries
    mui_Draw(&mui);

    u8g2_SendBuffer(&u8g2);
}