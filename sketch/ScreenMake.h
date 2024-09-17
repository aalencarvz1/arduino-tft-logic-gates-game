#ifndef SCREENLMAKE_H
#define SCREENLMAKE_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenMake : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 30;
  ScreenMake(char* pTitle = "MODO CONSTRUA", bool pHasBack = true);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLMAKE_H