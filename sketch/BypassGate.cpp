#include "BypassGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
BypassGate::BypassGate(
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
  connectorCount = 1;
};

void BypassGate::drawBody(bool drawConnectors) {
  if (vertical) {
    if (lineWidth > 1) {
      SCtrl::tft.fillRect(x + width / 2 - lineWidth,y-size,width,size,lineColor); //base line
    } else {
      SCtrl::tft.drawLine(x + width / 2,y-size,x+width/2,y,lineColor); //base line
    }
  } else {
    if (lineWidth > 1) {
      SCtrl::tft.fillRect(x,y+width/2-lineWidth,size,width,lineColor);
    } else {
      SCtrl::tft.drawLine(x,y+width/2,x+size,y+width/2,lineColor);
    }
  }
};
