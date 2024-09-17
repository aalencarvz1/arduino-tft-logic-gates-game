#ifndef SCREENLPOINTS_H
#define SCREENLPOINTS_H

#include <Arduino.h>
#include "BaseScreen.h"

struct ScreenPoints : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 10;
  ScreenPoints(char* pTitle = "MODO PONTUACAO", bool pHasBack = true);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLPOINTS_H