#include "XnorGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
XnorGate::XnorGate(
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
  OrGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) 
{
  size = pSize;  
  isExclusive = true;
  setHasNot(true);
};

bool XnorGate::calcOutputState(){
  Serial.println("calculating gate output");
  outputState = false;
  if (hasInputs == true) {
    if (inputs != nullptr) {
      for (size_t i = 0; i < connectorCount; i++) {
        outputState ^= inputs[i]->on;          
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


