#include "Display.h"

LcdDisplay::LcdDisplay(uint8_t rs, uint8_t rw, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    : lcd(rs, rw, en, d4, d5, d6, d7) {}

void LcdDisplay::init() {
    lcd.begin(16, 2); // 16 символов, 2 строки
    lcd.clear();
}

void LcdDisplay::printLine(uint8_t line, const String& text) {
    if (line > 1) return; // только строки 0 и 1
    lcd.setCursor(0, line);
    lcd.print("                "); // очистить строку
    lcd.setCursor(0, line);
    lcd.print(text);
}

void LcdDisplay::clear() {
    lcd.clear();
}
