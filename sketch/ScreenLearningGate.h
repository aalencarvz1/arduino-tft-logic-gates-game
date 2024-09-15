#ifndef SCREENLEARNINGGATE_H
#define SCREENLEARNINGGATE_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenLearningGate : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 3;
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLEARNINGGATE_H