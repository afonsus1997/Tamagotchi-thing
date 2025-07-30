
#include "userio.h"


struct button *btn_left;
struct button *btn_center;
struct button *btn_right;

uint32_t t0 = 0;

button_level_t get_button_state_left(void *ctx) {
	return HAL_GPIO_ReadPin(SW_LEFT_GPIO_Port, SW_LEFT_Pin) == GPIO_PIN_RESET;
}

button_level_t get_button_state_center(void *ctx) {
	return HAL_GPIO_ReadPin(SW_CENTER_GPIO_Port, SW_CENTER_Pin) == GPIO_PIN_RESET;
}

button_level_t get_button_state_right(void *ctx) {
	return HAL_GPIO_ReadPin(SW_RIGHT_GPIO_Port, SW_RIGHT_Pin) == GPIO_PIN_RESET;
}

static void on_button_event(struct button *btn, const button_state_t event,
                            const uint16_t clicks, const uint16_t repeats, void *ctx) {
    // switch (event) {
    // case BUTTON_STATE_PRESSED:
    //     break;
    // case BUTTON_STATE_RELEASED:
    //     break;
    // case BUTTON_STATE_HOLDING:
    //     break;
    // }
}

void test(){}

void userio_init(){
  
  btn_left = button_new(get_button_state_left, 0, on_button_event, 0);
  btn_center = button_new(get_button_state_center, 0, on_button_event, 0);
  btn_right = button_new(get_button_state_right, 0, on_button_event, 0);
  
  button_enable(btn_left);
  button_enable(btn_center);
  button_enable(btn_right);
}


void userio_refresh_buttons(){
  #if DO_DELTA_TIME
        const uint32_t now = HAL_GetTick();
        button_step_delta(btn_left, now - t0);
        button_step_delta(btn_center, now - t0);
        button_step_delta(btn_right, now - t0);
        t0 = now;
#else
        const uint32_t now = HAL_GetTick();
        button_step(btn_left, now);
        button_step(btn_center, now);
        button_step(btn_right, now);
#endif
}