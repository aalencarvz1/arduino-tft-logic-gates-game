#ifndef SCREENLTIME_H
#define SCREENLTIME_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenTime : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 20;
  ScreenTime(char* pTitle = "MODO TEMPO", bool pHasBack = true);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLTIME_H