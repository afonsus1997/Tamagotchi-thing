
#include "userio.h"


struct button *btn;

button_level_t get_button_state(void *ctx) {
	return 1;
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
  btn = button_new(get_button_state, 0, on_button_event, 0);
  button_enable(btn);
}