#include "NandGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
NandGate::NandGate(
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
  AndGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) 
{
  size = pSize;
  setHasNot(true);
};
