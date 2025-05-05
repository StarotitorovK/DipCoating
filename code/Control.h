#ifndef CONTROL_H
#define CONTROL_H

#include "Display.h"
#include <EEPROM.h>
#include "GyverStepper2.h"

/**
 * @file Control.h
 * @brief Управление параметрами покрытия и пользовательским интерфейсом.
 */

typedef void (*OptionHandler)();

struct CoatingParameters {
    float speed;
    float coating_distance;
    float wait;

    float& operator[](int index) {
        switch (index) {
        case 0: return speed;
        case 1: return coating_distance;
        case 2: return wait;
        default: return speed; // защита от выхода за пределы
        }
    }
};

extern CoatingParameters parameters;
extern GStepper2< STEPPER2WIRE> stepper;

struct Option {
    const char* name;
    OptionHandler onUp;
    OptionHandler onDown;
    OptionHandler onEnter;
    OptionHandler onCancel;
};

enum Screen {
    MAIN_SCREEN,
    MENU_SCREEN,
    OPTION_SCREEN
};

extern CoatingParameters parameters;
extern Option options[3];
extern int currentOptionIndex;
extern Screen currentScreen;

void initMenu(LcdDisplay& display);
void updateMenu(LcdDisplay& display);

void showMainDisplay(LcdDisplay& display);
void showMenuDisplay(LcdDisplay& display);
void showOptionDisplay(LcdDisplay& display);
void updateOptionDisplay(LcdDisplay& display);

void speedUp();
void speedDown();
void toggleSizeUp();
void toggleSizeDown();
void waitUp();
void waitDown();

void saveOptions();
void loadParameters();
void startProcess();
void manual_coating(bool dir);
int getMaxMenuIndex();

#endif