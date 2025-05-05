#include "AnalogButtons.h"
#include "Control.h"
#include "Display.h"
#include "GyverStepper2.h"

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
#define DEBUG(x) Serial.println(x)
#else
#define DEBUG(x)
#endif

int KEYBOARD = A0;
int STEP = 5;                  // Светодиод подсоединен к цифровому выводу 13
int DIR = 4;
int EN = 6;
int D4 = 10;
int D5 = 11;
int D6 = 12;
int D7 = 13;
int RS = 7;
int RW = 8;
int E = 9;

LcdDisplay display(RS, RW, E, D4, D5, D6, D7);
GStepper2< STEPPER2WIRE> stepper(400, STEP, DIR);
bool manualCoatingFlag = false;
bool dir = true;

void setup() {
  #ifdef DEBUG_ENABLE
  Serial.begin(9600);
  #endif


  display.init();
  initAnalogButtons(KEYBOARD); 
  initMenu(display);


  pinMode(STEP, OUTPUT);       // устанавливаем режим работы вывода, как "выход"
  pinMode(DIR, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(DIR, LOW);
  digitalWrite(EN, LOW);
}

void loop() {
  Button btn = readAnalogButton(KEYBOARD);
  manualCoatingFlag = false;

  switch (btn) {
    case UP:
        if (currentScreen == MAIN_SCREEN) manual_coating(true);
        else if (currentScreen == MENU_SCREEN) {
            currentOptionIndex--;
            if (currentOptionIndex < 0) currentOptionIndex = getMaxMenuIndex();
        }
        else if (currentScreen == OPTION_SCREEN && options[currentOptionIndex].onUp) {
            options[currentOptionIndex].onUp();
            showOptionDisplay(display);
        }
      break;
    case DOWN:
        if (currentScreen == MAIN_SCREEN) manual_coating(false);
        else if (currentScreen == MENU_SCREEN) {
            currentOptionIndex++;
            if (currentOptionIndex > getMaxMenuIndex()) currentOptionIndex = 0;
        }
        else if (currentScreen == OPTION_SCREEN && options[currentOptionIndex].onDown) {
            options[currentOptionIndex].onDown();
            showOptionDisplay(display);
        }
      break;
    case MENU:
        if (currentScreen == MAIN_SCREEN) {
            currentScreen = MENU_SCREEN;
        } else if (currentScreen == MENU_SCREEN) {
            currentScreen = MAIN_SCREEN;
        } else if (currentScreen == OPTION_SCREEN && options[currentOptionIndex].onCancel) {
            options[currentOptionIndex].onCancel();
            currentScreen = MENU_SCREEN;
        }
      break;
    case START:
        if (currentScreen == MAIN_SCREEN) startProcess();
        else if (currentScreen == MENU_SCREEN) currentScreen = OPTION_SCREEN;
        else if (currentScreen == OPTION_SCREEN && options[currentOptionIndex].onEnter)
            options[currentOptionIndex].onEnter();
      break;
    default:
      break;
  }
  
  updateMenu(display);
  delay(200);
}


// void loop()
// {
//   digitalWrite(STEP, HIGH);   
//   delay(20);                   
//   digitalWrite(STEP, LOW);    
//   delay(20);                   
// }