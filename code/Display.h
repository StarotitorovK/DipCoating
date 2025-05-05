#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class LcdDisplay {
public:
    LcdDisplay(uint8_t rs, uint8_t rw, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    void init();                          // инициализация дисплея
    void printLine(uint8_t line, const String& text);  // печать текста на строку (0 или 1)
    void clear();                         // очистить экран

private:
    LiquidCrystal lcd;
};

#endif
