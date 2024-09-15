#include "ScreenLearningGate.h"
#include "Utils.h"
#include "SCtrl.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "EVRcpt.h"
#include "Screens.h"



void ScreenLearningGate::draw(char* params[]){
    SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
    SCtrl::tft.setTextColor(TFT_WHITE);
    SCtrl::tft.setTextSize(2);
    SCtrl::tft.setCursor(10, 10);
    TextInfo ti = SCtrl::drawCenteredText("MODO TUTORIAL");
    this->drawBackButton();
    SCtrl::tft.drawRect(5, ti.h+10, SCtrl::tft.width() - 10, SCtrl::tft.height() - (ti.h+10), TFT_WHITE);
    //ti = SCtrl::drawCenteredText("Porta AND",ti.h+20);

    

    if (params != nullptr) {
      Gate* g = nullptr;
      double gateSize = SCtrl::tft.height()-190;
      double gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
      double gateX = SCtrl::tft.width() / 2 - gateWidth / 2;
      double gateY = SCtrl::tft.height() - 75;
      if (params[0] == "AND") {
        g = new AndGate(
          gateX,
          gateY,
          gateSize,
          DEFAULT_GATE_CONNECTOR_COUNT,
          DEFAULT_GATE_VERTICAL_DIRECTION,
          DEFAULT_GATE_LINE_COLOR,
          DEFAULT_GATE_LINE_WIDTH,
          DEFAULT_GATE_ASPECT_RATIO,
          DEFAULT_GATE_BASE_SIZE_PERC,
          DEFAULT_GATE_CONNECTOR_SIZE,
          gateWidth
        );        
      } else if (params[0] == "OR") {
        g = new OrGate(
          gateX,
          gateY,
          gateSize,
          DEFAULT_GATE_CONNECTOR_COUNT,
          DEFAULT_GATE_VERTICAL_DIRECTION,
          DEFAULT_GATE_LINE_COLOR,
          DEFAULT_GATE_LINE_WIDTH,
          DEFAULT_GATE_ASPECT_RATIO,
          DEFAULT_GATE_BASE_SIZE_PERC,
          DEFAULT_GATE_CONNECTOR_SIZE,
          gateWidth
        );
      } else if (params[0] == "NOT") {
        g = new NotGate(
          gateX,
          gateY,
          gateSize,
          1,
          DEFAULT_GATE_VERTICAL_DIRECTION,
          DEFAULT_GATE_LINE_COLOR,
          DEFAULT_GATE_LINE_WIDTH,
          DEFAULT_GATE_ASPECT_RATIO,
          DEFAULT_GATE_BASE_SIZE_PERC,
          DEFAULT_GATE_CONNECTOR_SIZE,
          gateWidth
        );
      } else {
        g = nullptr; //random        
      }
      g->hasInputs = true;
      g->draw();            

      /*delete g;
      g = nullptr;*/

    }
  };