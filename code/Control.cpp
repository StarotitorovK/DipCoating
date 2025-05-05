#include "Control.h"
#include "Display.h"
#include <EEPROM.h>

CoatingParameters parameters = { 1.0, 1.0, 0.0 };
Screen currentScreen = MAIN_SCREEN;
int currentOptionIndex = 0;

Option options[3] = {
    { "Speed", speedUp, speedDown, saveOptions, loadParameters },
    { "Height", toggleSizeUp, toggleSizeDown, saveOptions, loadParameters },
    { "Wait", waitUp, waitDown, saveOptions, loadParameters }
};

void initMenu(LcdDisplay& display) {
    currentScreen = MAIN_SCREEN;
    currentOptionIndex = 0;
    showMainDisplay(display);
}

void updateMenu(LcdDisplay& display) {
    switch (currentScreen) {
    case MAIN_SCREEN:
        showMainDisplay(display);
        break;
    case MENU_SCREEN:
        showMenuDisplay(display);
        break;
    case OPTION_SCREEN:
        showOptionDisplay(display);
        break;
    }
}

void showMainDisplay(LcdDisplay& display) {
    display.clear();
    display.printLine(0, "Press start");
    display.printLine(1, "to coat");
}

void showMenuDisplay(LcdDisplay& display) {
    display.clear();
    display.printLine(0, options[currentOptionIndex].name);
}

void showOptionDisplay(LcdDisplay& display) {
    display.clear();
    display.printLine(0, options[currentOptionIndex].name);
    updateOptionDisplay(display);
}

void updateOptionDisplay(LcdDisplay& display) {
    auto val = String(parameters[currentOptionIndex]);
    display.printLine(1, val);
}

void speedUp() {
    if ((parameters.speed >= 1.0) && (parameters.speed <= 19.5)) {
        if (parameters.speed <= 10.0) parameters.speed += 0.1;
        else if (parameters.speed <= 20.0) parameters.speed += 0.5;
    }
}
void speedDown() {
    if ((parameters.speed >= 1.1) && (parameters.speed <= 20.0)) {
        if (parameters.speed <= 10.0) parameters.speed -= 0.1;
        else if (parameters.speed <= 20.0) parameters.speed -= 0.5;
    }
}

void toggleSizeUp() {
    if ((parameters.coating_distance >= 1.0) && (parameters.coating_distance <= 7.9)) {
        parameters.coating_distance += 0.1;
    }
}
void toggleSizeDown() {
    if ((parameters.coating_distance >= 1.1) && (parameters.coating_distance <= 8.0)) {
        parameters.coating_distance -= 0.1;
    }
}

void waitUp() {
    if ((parameters.wait >= 0.0) && (parameters.wait <= 9.9)) {
        parameters.wait += 0.1;
    }
}

void waitDown() {
    if ((parameters.wait >= 0.1) && (parameters.wait <= 10.0)) {
        parameters.wait -= 0.1;
    }
}


void saveOptions() {
  EEPROM.put(0, parameters);
}

void loadParameters() {
  EEPROM.get(0, parameters);

  if (isnan(parameters.speed) || isnan(parameters.coating_distance) || isnan(parameters.wait)) {
    parameters = {1.0f, 1.0f, 0.0f};
    saveOptions();
  }
}


float evaluateSPS(float speed, int steps) {
    float i = 1; // передаточное число редуктора
	float d = 40; // диаметр шестерни
	return steps * i * speed / (d * 3.14); // скорость в шаг/с
}

float evaluateAccel(float speed, int steps) {
	return evaluateSPS(speed, steps) * speed; // ускорение в шаг/с^2
}

void startProcess() {
    stepper.setMaxSpeed(evaluateSPS(parameters.speed, 6400));    
    stepper.setAcceleration(evaluateAccel(parameters.speed, 6400));
    stepper.setTarget(6400 * 3);

    while (!stepper.ready()) {
        stepper.tick(); 
    }
}

void manual_coating(bool dir) {
    // реализуй ручное управление
}

int getMaxMenuIndex() {
    return 2; 
}
