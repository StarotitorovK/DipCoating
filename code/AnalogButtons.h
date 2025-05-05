#ifndef ANALOG_BUTTONS_H
#define ANALOG_BUTTONS_H

enum Button {
  BUTTON_NONE,
  UP,
  DOWN,
  MENU,
  START
};

void initAnalogButtons(int pin);
Button readAnalogButton(int pin);

#endif
