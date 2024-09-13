#include "OrGate.h"
#include "SCtrl.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
OrGate::OrGate(
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



void OrGate::drawBody() {
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

  double baseArcHeight = width * DEFAULT_GATE_BASE_ARC_HEIGHT_ASPECT_RATIO;
  CircleInfo baseArc;
  if (vertical) {    
    baseArc = SCtrl::drawArcFromArrow(x,y,x+width,y,baseArcHeight,lineColor);
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth ; i++) {
        SCtrl::drawArcFromArrow(x+i,y,x+width-i,y,baseArcHeight-i,lineColor);
      }
    }
    SCtrl::tft.fillRect(x,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //left line
    SCtrl::tft.fillRect(x+width-lineWidth,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //rigth line 

    //adjust connectors;
    double connMargin = connectorMargin;
    if (lineWidth > 1) {
      connMargin = connMargin - lineWidth / 2;
    }
    for(int i = 0; i < connectorCount; i++) {
      
      connMargin = connMargin + (i * (width - (connMargin * 2)) / (connectorCount - 1));
      Serial.println("i" + String(i) + " c1 "+String(connectorSize)+" r " + String(baseArc.r) + " xc " + String(baseArc.x) + " " + String((x+connMargin)) + " y " + String(baseArc.y));
      double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.x-(x+connMargin)); 
      Serial.println("c2 "+String(newConnectorSize));
      double newPos = baseArc.y-newConnectorSize;
      newConnectorSize = newConnectorSize - (baseArc.y - (y + connectorSize));
      Serial.println("c3 "+String(newConnectorSize));
      drawConnector(i,newPos, newConnectorSize);
      
      //break;   
    }

    for (int i = 0; i < lineWidth ; i++) {
      Serial.println("x1="+String(x+(width/2.0)-i)+",y1="+String(y-size-baseAdjust)+"x2="+String(x+width-i)+",y2="+String(y-size+arcHeight-baseAdjust));
      SCtrl::drawArcFromArrow(x+i,y-size+arcHeight-baseAdjust,x+(width/2.0)-i,y-size-baseAdjust,arcHeight*0.2-i,lineColor);
      SCtrl::drawArcFromArrow(x+(width/2.0)-i,y-size-baseAdjust,x+width-i,y-size+arcHeight-baseAdjust,arcHeight*0.2-i,lineColor);
    }
  } else {
    baseArc = SCtrl::drawArcFromArrow(x,y,x,y+width,baseArcHeight,lineColor);
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth ; i++) {
        SCtrl::drawArcFromArrow(x,y+i,x,y+width-i,baseArcHeight-i,lineColor);
      }
    }
    SCtrl::tft.fillRect(x,y,size-arcHeight+baseAdjust,lineWidth,lineColor); //left line
    SCtrl::tft.fillRect(x,y+width-lineWidth,size-arcHeight+baseAdjust,lineWidth,lineColor); //rigth line


    //adjust connectors;
    double connMargin = connectorMargin;
    if (lineWidth > 1) {
      connMargin = connMargin - lineWidth / 2;
    }
    for(int i = 0; i < connectorCount; i++) {
      
      connMargin = connMargin + (i * (width - (connMargin * 2)) / (connectorCount - 1));
      Serial.println("i" + String(i) + " c1 "+String(connectorSize)+" r " + String(baseArc.r) + " xc " + String(baseArc.x) + " " + String((x+connMargin)) + " y " + String(baseArc.y));
      double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.y-(y+connMargin)); 
      Serial.println("c2 "+String(newConnectorSize));
      double newPos = baseArc.x+newConnectorSize;
      newConnectorSize = newConnectorSize - (x - baseArc.x - connectorSize);
      Serial.println("c3 "+String(newConnectorSize));
      drawConnector(i,newPos, newConnectorSize);
      
      //break;   
    }

    for (int i = 0; i < lineWidth ; i++) {
      SCtrl::drawArcFromArrow(x+size-arcHeight+baseAdjust,y+i,x+size-arcHeight+baseAdjust,y+width-i,arcHeight,lineColor);
    }
  }
};