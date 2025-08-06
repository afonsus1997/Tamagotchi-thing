
#include "userio.h"
#include "lwbtn.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"

uint8_t btn_states[3] = {0, 0, 0};


const int buttons_id[BUTTONS_TOTAL] = {BUTTON_RIGHT, BUTTON_CENTER, BUTTON_LEFT};



lwbtn_btn_t btns[] = {

    {.arg = (void*)&buttons_id[BUTTON_RIGHT]}, 
    {.arg = (void*)&buttons_id[BUTTON_CENTER]}, 
    {.arg = (void*)&buttons_id[BUTTON_LEFT]}

};


void userio_button_event(struct lwbtn* lw, struct lwbtn_btn* btn, lwbtn_evt_t evt) {
    if (evt == LWBTN_EVT_ONPRESS) {
        int btn_id = *(int*)btn->arg;
        ui_process_button_event(btn_id);
    }
}

uint8_t prv_btn_get_state(struct lwbtn* lw, struct lwbtn_btn* btn) {
  switch (*(int*)btn->arg) {
    case BUTTON_RIGHT:
      return HAL_GPIO_ReadPin(SW_RIGHT_GPIO_Port, SW_RIGHT_Pin) == GPIO_PIN_SET;
    case BUTTON_CENTER:
      return HAL_GPIO_ReadPin(SW_CENTER_GPIO_Port, SW_CENTER_Pin) == GPIO_PIN_SET;
    case BUTTON_LEFT:
      return HAL_GPIO_ReadPin(SW_LEFT_GPIO_Port, SW_LEFT_Pin) == GPIO_PIN_SET;
    default:
      return 0; // Button not pressed
  };
}

void userio_process(){
  lwbtn_process_ex(NULL, HAL_GetTick());
}

void userio_init(){
  lwbtn_init_ex(NULL, btns, sizeof(btns) / sizeof(btns[0]), prv_btn_get_state, userio_button_event);
}