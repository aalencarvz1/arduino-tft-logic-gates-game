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
  Gate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) 
{
  if (pBaseSizePerc < DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC;
  } else if (pBaseSizePerc > DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC;
  }
};


void OrGate::setValues(
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
) {

  Gate::setValues(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);

  if (pBaseSizePerc < DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC;
  } else if (pBaseSizePerc > DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC;
  } 
};


void OrGate::drawBody(bool drawConnectors) {
  double arcHeightPerc = 0;
  if (baseSizePerc != DEFAULT_GATE_BASE_SIZE_PERC) {
    arcHeightPerc = 1.0-baseSizePerc;
  } else {
    arcHeightPerc = 1.0/connectorCount;
  }  
  double arcHeight = size * arcHeightPerc;
  double baseAdjust = 0;

  double baseArcHeight = width * DEFAULT_GATE_BASE_ARC_HEIGHT_ASPECT_RATIO;
  CircleInfo baseArc;
  if (vertical) {  

    //draw curved base  
    baseArc = SCtrl::drawArcFromArrow(x,y,x+width,y,baseArcHeight,lineColor);
    if (lineWidth > 1) {
      for (int i = 1; i < lineWidth ; i++) {
        SCtrl::drawArcFromArrow(x+i,y,x+width-i,y,baseArcHeight-i,lineColor);
      }
    }

    // draw curved exclusive base    
    if (isExclusive) {
      SCtrl::drawArcFromArrow(x,y+size * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,x+width,y+size * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,baseArcHeight,lineColor);
    }

    //draw laterals
    if (lineWidth > 1) {
      SCtrl::tft.fillRect(x,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //left line
      SCtrl::tft.fillRect(x+width-lineWidth,y-size+arcHeight-baseAdjust,lineWidth,size-arcHeight+baseAdjust,lineColor); //rigth line 
    } else {
      SCtrl::tft.drawLine(x,y-size+arcHeight-baseAdjust,x,y,lineColor); //left line
      SCtrl::tft.drawLine(x+width,y-size+arcHeight-baseAdjust,x+width,y,lineColor); //rigth line 
    }

    //draw connectors
    if (drawConnectors == true) {
      double connMargin = connectorMargin;
      if (lineWidth > 1) {
        connMargin = connMargin - lineWidth / 2;
      }
      for(int i = 0; i <= connectorCount / 2; i++) {        
        connMargin = connMargin + (i * (width - (connMargin * 2)) / (connectorCount - 1));
        double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.x-(x+connMargin)); 
        double newPos = baseArc.y-newConnectorSize;
        newConnectorSize = newConnectorSize - (baseArc.y - (y + connectorSize));
        drawConnector(i,newPos, newConnectorSize);
        drawConnector(connectorCount-(i+1),newPos, newConnectorSize);
      }
    }

    //draw top curved arcs
    double arcHeight2 = sqrt(pow((x+(width/2.0)) - x, 2.0) + pow((y-size+arcHeight-baseAdjust) - (y-size-baseAdjust), 2.0));  // Distância entre P1 e P2 (lado a)
    arcHeight2 = arcHeight2 / 15; //divide o circulo em 15 partes, 
    for (int i = 0; i < lineWidth ; i++) {
      Serial.println("x1="+String(x+(width/2.0)-i)+",y1="+String(y-size-baseAdjust)+"x2="+String(x+width-i)+",y2="+String(y-size+arcHeight-baseAdjust));
      SCtrl::drawArcFromArrow(x+i,y-size+arcHeight-baseAdjust,x+(width/2.0)-i,y-size-baseAdjust,arcHeight2-i,lineColor);
      SCtrl::drawArcFromArrow(x+(width/2.0)-i,y-size-baseAdjust,x+width-i,y-size+arcHeight-baseAdjust,arcHeight2-i,lineColor);
    }
  } else {

    //draw base arc
    baseArc = SCtrl::drawArcFromArrow(x,y,x,y+width,baseArcHeight,lineColor);
    if (lineWidth > 1) {
      for (int i = 1; i < lineWidth ; i++) {
        SCtrl::drawArcFromArrow(x,y+i,x,y+width-i,baseArcHeight-i,lineColor);
      }
    }

    //draw exclusive curved bar
    if (isExclusive) {
      baseArc = SCtrl::drawArcFromArrow(x-size * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,y,x-size * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,y+width,baseArcHeight,lineColor);
    }

    //draw laterals
    if (lineWidth > 1) {
      SCtrl::tft.fillRect(x,y,size-arcHeight+baseAdjust,lineWidth,lineColor); //left line
      SCtrl::tft.fillRect(x,y+width-lineWidth,size-arcHeight+baseAdjust,lineWidth,lineColor); //rigth line
    } else {
      SCtrl::tft.drawLine(x,y,x+size-arcHeight+baseAdjust,y,lineColor); //left line
      SCtrl::tft.drawLine(x,y+width,x+size-arcHeight+baseAdjust,y,lineColor); //rigth line
    }

    //draw conectors
    if (drawConnectors == true) {
      double connMargin = connectorMargin;
      if (lineWidth > 1) {
        connMargin = connMargin - lineWidth / 2;
      }
      for(int i = 0; i <= connectorCount / 2; i++) {        
        connMargin = connMargin + (i * (width - (connMargin * 2)) / (connectorCount - 1));
        double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.y-(y+connMargin)); 
        double newPos = baseArc.x+newConnectorSize;
        newConnectorSize = newConnectorSize - (x - baseArc.x - connectorSize);
        drawConnector(i,newPos, newConnectorSize);
        drawConnector(connectorCount-(i+1),newPos, newConnectorSize);
      }
    }

    //draw top curved arcs
    double arcHeight2 = sqrt(pow((x+size-baseAdjust) - (x+size-arcHeight-baseAdjust), 2.0) + pow((y+width/2) - (y), 2.0));  // Distância entre P1 e P2 (lado a)
    arcHeight2 = arcHeight2 / 15; //divide o circulo em 15 partes para obter uma curva suave (raio grande), 
    for (int i = 0; i < lineWidth ; i++) {
      Serial.println("x1="+String(x+(width/2.0)-i)+",y1="+String(y-size-baseAdjust)+"x2="+String(x+width-i)+",y2="+String(y-size+arcHeight-baseAdjust));
      SCtrl::drawArcFromArrow(x+size-arcHeight-baseAdjust,y+i,x+size-baseAdjust,y+width/2+i,arcHeight2-i,lineColor);
      SCtrl::drawArcFromArrow(x+size-baseAdjust,y+width/2-i,x+size-arcHeight-baseAdjust,y+width-i,arcHeight2-i,lineColor);
    }
  }
};

void OrGate::draw(bool drawConnectors) {  
  drawBody(drawConnectors);
  if (drawConnectors == true) {
    drawOutputConnector();
  }
  drawNot();
};

bool OrGate::calcOutputState(){
  Serial.println("calculating gate output");
  outputState = false;
  if (hasInputs == true) {
    if (inputs != nullptr) {
      for (size_t i = 0; i < connectorCount; i++) {
        Serial.println("gate("+String(i)+") " + String(inputs[i]->id) + "="+boolToString(inputs[i]->on));
        outputState = outputState || inputs[i]->on;          
        if (outputState) {
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