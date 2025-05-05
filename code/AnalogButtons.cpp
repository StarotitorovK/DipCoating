#include "AnalogButtons.h"
#include <Arduino.h>

static int analogPin = A0; // по умолчанию, если init не вызван

void initAnalogButtons(int pin) {
  analogPin = pin;
}

Button readAnalogButton(int pin) {
  int value = analogRead(pin);

  // Настроено примерно под 5В питание — подстрой по своим резисторам
  if (value < 211)       return BUTTON_NONE;
  else if (value < 298)  return UP;
  else if (value < 426)  return DOWN;
  else if (value < 767)  return MENU;
  else					 return START;
}
