#if !defined(USERIO_H)
#define USERIO_H

#include "main.h"
#include "lwbtn.h"
#include "ui.h"

enum btnsIdx_e
{
  BUTTON_RIGHT = 0,
  BUTTON_CENTER,
  BUTTON_LEFT,
  BUTTONS_TOTAL
}; 

void userio_process();
void userio_init();

extern const int buttons_id[BUTTONS_TOTAL];


#endif // USERIO_H
