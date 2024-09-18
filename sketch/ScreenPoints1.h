#ifndef SCREENPOINTS1_H
#define SCREENPOINTS1_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"

struct ScreenPoints1 : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 11;
  Gate* currentGate = nullptr;
  EVRcpt* evNext = nullptr;
  EVRcpt* evPrev = nullptr;
  char* previousGateName = nullptr;
  char* currentGateName = nullptr;
  int currentPontuation = 0;
  ScreenPoints1(char* pTitle = "MODO PONTUACAO", bool pHasBack = true);
  ~ScreenPoints1();
  void drawGate(char* gateName, double x, double y, double size);
  void drawPrevGate(double x, double y, double size);
  void drawNextGate(double x, double y, double size);
  void drawConfirmButton();
  void pontuationTitle();
  void pontuationCurrentPontuation();
  void confirm();
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENPOINTS1_H