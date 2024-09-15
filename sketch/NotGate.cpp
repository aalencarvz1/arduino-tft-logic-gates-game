#include "NotGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
NotGate::NotGate(
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
  Gate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) 
{
  size = pSize;
  setHasNot(true);
};

void NotGate::drawBody(bool drawConnectors) {
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
    SCtrl::tft.drawLine(x,y,x+width,y, lineColor);
    SCtrl::tft.drawLine(x,y,x+width/2,y-size, lineColor);
    SCtrl::tft.drawLine(x+width,y,x+width/2,y-size, lineColor);
    //SCtrl::tft.fillCircle(x+width/2,y-size-nr/2,nr,DEFAULT_BACKGROUND_COLOR);
    //SCtrl::tft.drawCircle(x+width/2,y-size-nr/2,nr,lineColor);
  } else {
    SCtrl::tft.drawLine(x,y,x,y+width, lineColor);
    SCtrl::tft.drawLine(x,y,x+size,y+width/2, lineColor);
    SCtrl::tft.drawLine(x,y+width,x+size,y+width/2, lineColor);
    //SCtrl::tft.fillCircle(x+size+nr/2,y+width/2,nr,DEFAULT_BACKGROUND_COLOR);
    //SCtrl::tft.drawCircle(x+size+nr/2,y+width/2,nr,lineColor);
  }    
};

bool NotGate::calcOutputState(){
  Serial.println("calculating gate output");
  outputState = true;
  if (hasInputs == true) {
    if (inputs != nullptr) {
      outputState = !inputs[connectorCount-1]->on;      
      bool prevRecalcState = inputs[connectorCount]->recalcOnChange;
      inputs[connectorCount]->recalcOnChange = false; 
      inputs[connectorCount]->setState(outputState); 
      inputs[connectorCount]->recalcOnChange = prevRecalcState;
    };
  };
  Serial.println("calculated gate output:" + boolToString(outputState));
  return outputState;
};