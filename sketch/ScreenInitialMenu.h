#ifndef SCREENINITIALMENU_H
#define SCREENINITIALMENU_H

#include <Arduino.h>
#include "BaseScreen.h"



struct ScreenInitialMenu : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 0;    
  ScreenInitialMenu(char* pTitle = "PORTAS LOGICAS", bool pHasBack = true);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENINITIALMENU_H