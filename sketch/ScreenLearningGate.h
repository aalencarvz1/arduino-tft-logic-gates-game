#ifndef SCREENLEARNINGGATE_H
#define SCREENLEARNINGGATE_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"

struct ScreenLearningGate : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 3;
  Gate* currentGate = nullptr;
  EVRcpt* evNext = nullptr;
  EVRcpt* evPrev = nullptr;
  char* previousGateName = nullptr;
  char* currentGateName = nullptr;
  ScreenLearningGate(char* pTitle = "MODO TUTORIAL", bool pHasBack = true);
  ~ScreenLearningGate();
  void drawGate(char* gateName, double x, double y, double size);
  void drawPrevGate(double x, double y, double size);
  void drawNextGate(double x, double y, double size);
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENLEARNINGGATE_H