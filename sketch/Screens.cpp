#include "Screens.h"
#include <Arduino.h>
#include <StackArray.h>
#include "BaseScreen.h"
#include "EVRcpt.h"
#include "ScreenInitialMenu.h"
#include "ScreenLearning.h"
#include "ScreenPort.h"
#include "ScreenLearningGate.h"
#include "ScreenPoints.h"
#include "ScreenTime.h"
#include "ScreenMake.h"
#include "ScreenPoints1.h"



//STATIC INITIALIZATIONS
BaseScreen* Screens::currentScreen = nullptr;
StackArray <byte> Screens::stack;


//navigate to screen by id
void Screens::goTo(byte screenId,char* params[]) {      
  Serial.print("going screen ");
  Serial.println(screenId);

  BaseScreen* newScreen = nullptr;

  //find screen by id
  FREERAM_PRINT;
  if (screenId == ScreenInitialMenu::SCREEN_ID) {
    newScreen = new ScreenInitialMenu("PORTAS LOGICAS",false);
  } else if (screenId == ScreenLearning::SCREEN_ID) {
    newScreen = new ScreenLearning();
  } else if (screenId == ScreenPort::SCREEN_ID) {
    newScreen = new ScreenPort();
  } else if (screenId == ScreenLearningGate::SCREEN_ID) {
    newScreen = new ScreenLearningGate();
  } else if (screenId == ScreenPoints::SCREEN_ID) {
    newScreen = new ScreenPoints();
  } else if (screenId == ScreenTime::SCREEN_ID) {
    newScreen = new ScreenTime();
  } else if (screenId == ScreenMake::SCREEN_ID) {
    newScreen = new ScreenMake();
  } else if (screenId == ScreenPoints1::SCREEN_ID) {
    newScreen = new ScreenPoints1();
  };
  FREERAM_PRINT;

  if (newScreen != nullptr) {    

    //clear memory
    clearAllEVRcpts();
    if (currentScreen != nullptr) {
      delete currentScreen;
      currentScreen = nullptr;
    }
    currentScreen = newScreen;

    //add to stack if is not on top
    if (!stack.isEmpty()) {
      if (stack.peek() != screenId) {
        stack.push(screenId);
      }
    } else {
      stack.push(screenId);
    }

    //screen draw
    currentScreen->draw(params);
  } else {
    Serial.println("screen not found: " + String(screenId));
  }
  FREERAM_PRINT;
};

//navigate to previous screen on stack
void Screens::goBack(char* params[]) {  
  stack.pop();
  Screens::goTo(stack.peek(),params);
}