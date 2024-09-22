#ifndef SCREENPOINTS1_H
#define SCREENPOINTS1_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"
#include "GatesCircuit.h"

struct ScreenPoints1 : public BaseScreen{
  using BaseScreen::BaseScreen;
  static const byte SCREEN_ID = 11;
  Gate* currentGate = nullptr;
  GatesCircuit* currentCircuit = nullptr;
  EVRcpt* evNext = nullptr;
  EVRcpt* evPrev = nullptr;
  char* previousGateName = nullptr;
  char* currentGateName = nullptr;
  int currentDificultyLevel = 5;
  int currentPhase = 1;
  int currentPontuation = 0;
  int** phasesByLevel[7] = {3,5,5,5,5,5,5};

  double gateSize = 0;
  double gateWidth = 0;
  double gateX = 0;
  double gateY = 0;
  double resultX = 0;
  double resultY = 0;
  double resultSize = 50;

  ScreenPoints1(char* pTitle = "MODO PONTUACAO", bool pHasBack = true);
  ~ScreenPoints1();
  void drawGate(char* gateName, double x, double y, double size, int pConnectorCount = DEFAULT_GATE_CONNECTOR_COUNT, double pGateWidth = DEFAULT_GATE_WIDTH);
  void drawNextPhase();
  void drawConfirmButton();
  void pontuationTitle();
  void drawCurrentPontuation();
  void drawResult(bool isCorrect, double centerX, double centerY, double size = 50, bool onlyClean = false);
  void confirm();
  void draw(char* params[] = nullptr) override;
};

#endif // SCREENPOINTS1_H