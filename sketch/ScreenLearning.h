#ifndef SCREENLEARNING_H
#define SCREENLEARNING_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenLearning : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 1;
  ScreenLearning(char* pTitle = "MODO TUTORIAL", bool pHasBack = true);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLEARNING_H