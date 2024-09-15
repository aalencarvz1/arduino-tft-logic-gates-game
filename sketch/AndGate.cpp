#include "AndGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
AndGate::AndGate(
  double pX,
  double pY,
  double pSize,
  int pConnectorCount,
  bool pVertical,
  int pLineColor,
  double pLineWidth,
  double pAspectRatio,
  double pBaseSizePerc,
  double pConnectorSize,
  double pWidth,
  double pConnectorMargin
) :
  Gate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) {};

void AndGate::drawBody(bool drawConnectors) {
  double arcHeightPerc = 0;
  if (baseSizePerc != DEFAULT_GATE_BASE_SIZE_PERC) {
    arcHeightPerc = 1.0-baseSizePerc;
  } else {
    arcHeightPerc = 1.0/connectorCount;
  }  
  if (arcHeightPerc < DEFAULT_GATE_MIN_ARC_HEIGHT_PERC) {
    arcHeightPerc = DEFAULT_GATE_MIN_ARC_HEIGHT_PERC;
  }
  double arcHeight = size * arcHeightPerc;
  double baseAdjust = 0;
  if (arcHeight >= width/2.0) {
    baseAdjust = arcHeight - (width / 2.0);
  }   
    
  if (vertical) {
    SCtrl::tft.fillRect(x,y-lineWidth,width,lineWidth,lineColor); //base line
    SCtrl::tft.fillRect(x,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //left line
    SCtrl::tft.fillRect(x+width-lineWidth,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //rigth line        
    for (int i = 0; i < lineWidth ; i++) {
      SCtrl::drawArcFromArrow(x+i,y-size+arcHeight-baseAdjust,x+width-i,y-size+arcHeight-baseAdjust,arcHeight-i,lineColor);
    }
  } else {
    SCtrl::tft.fillRect(x,y,lineWidth,width,lineColor);
    SCtrl::tft.fillRect(x,y,size-arcHeight+baseAdjust,lineWidth,lineColor); //left line
    SCtrl::tft.fillRect(x,y+width-lineWidth,size-arcHeight+baseAdjust,lineWidth,lineColor); //rigth line
    for (int i = 0; i < lineWidth ; i++) {
      SCtrl::drawArcFromArrow(x+size-arcHeight+baseAdjust,y+i,x+size-arcHeight+baseAdjust,y+width-i,arcHeight,lineColor);
    }
  }
};

bool AndGate::calcOutputState(){
  Serial.println("calculating gate output");
  outputState = false;
  if (hasInputs == true) {
    if (inputs != nullptr) {
      outputState = true;
      for (size_t i = 0; i < connectorCount; i++) {
        Serial.println("gate("+String(i)+") " + String(inputs[i]->id) + "="+boolToString(inputs[i]->on));
        outputState = outputState && inputs[i]->on;          
        if (!outputState) {
          break;
        };
      };
      outputState = hasNot ? !outputState : outputState;
      bool prevRecalcState = inputs[connectorCount]->recalcOnChange;
      inputs[connectorCount]->recalcOnChange = false; 
      inputs[connectorCount]->setState(outputState); 
      inputs[connectorCount]->recalcOnChange = prevRecalcState;
    };
  };
  Serial.println("calculated gate output:" + boolToString(outputState));
  return outputState;
};