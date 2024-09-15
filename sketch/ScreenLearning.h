#ifndef SCREENLEARNING_H
#define SCREENLEARNING_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenLearning : public BaseScreen{
  static const byte SCREEN_ID = 1;
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLEARNING_H