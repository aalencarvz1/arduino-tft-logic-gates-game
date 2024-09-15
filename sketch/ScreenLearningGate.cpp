#include "ScreenLearningGate.h"
#include "Utils.h"
#include "SCtrl.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "XnorGate.h"
#include "EVRcpt.h"
#include "Screens.h"

void ScreenLearningGate::draw(char* params[]){
  BaseScreen::draw(params);
  
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
    } else if (params[0] == "NAND") {
      g = new NandGate(
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
    } else if (params[0] == "NOR") {
      g = new NorGate(
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
    } else if (params[0] == "XOR") {
      g = new XorGate(
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
    } else if (params[0] == "XNOR") {
      g = new XnorGate(
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
    } else {
      g = nullptr; //random        
    }
    if (g != nullptr) {
      g->hasInputs = true;
      g->draw();            
    }

    /*delete g;
    g = nullptr;*/

  }
};