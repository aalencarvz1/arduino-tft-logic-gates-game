#include "ScreenPort.h"
#include "Utils.h"
#include "SCtrl.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "EVRcpt.h"
#include "Screens.h"


void drawRandomGate(Gate* g){
  bool randomGate = false;
  double minX = 0.0;
  double maxX = SCtrl::tft.width() * 0.8;
  double minY = 0.0;
  double maxY = SCtrl::tft.height(); 
  double minS = 50.0;
  double maxS = SCtrl::tft.width() * 0.8;
  while(true) {
    bool vertical = random(0, 2) == 1;
    maxX = SCtrl::tft.width() * 0.8;
    if (vertical) {
      minY = 100.0;
    } else {
      minY = 0.0;
      maxX = SCtrl::tft.width() * 0.60;
    }
    double xPos = random(minX,maxX);
    double yPos = random(minY,maxY);
    byte connectors = random(2,8);
    if (vertical) {
      maxS = SCtrl::tft.height() - yPos;
    } else {
      maxS = SCtrl::tft.width() - xPos;
    }
    double portSize = random(minS,maxS); 
    if (portSize < 50) portSize = 50.0;   
    double lineWidth = 1.0;//random(1,5);    
    double aspectRatio = 2.0/random(1,4);
    int color = random(0,0xFFFFFF);
    double baseSizePerc = double(random(0,90))/100.0;
    double connectorSize = double(random(5,90));
    SCtrl::tft.fillRect(0,0,480,320,TFT_BLACK);
    if (g != nullptr && randomGate != true) {
      g->setValues(
        xPos,
        yPos,
        portSize,
        connectors,
        vertical,
        color,
        lineWidth,
        aspectRatio,
        baseSizePerc,
        connectorSize
      );
    } else {
      randomGate = true;
      int portId = random(0, 12);
      if (portId <= 4) {
        g = new AndGate(
          xPos,
          yPos,
          portSize,
          connectors,
          vertical,
          color,
          lineWidth,
          aspectRatio,
          baseSizePerc,
          connectorSize
        );
      } else if (portId >4 && portId <= 8) {
        g = new OrGate(
          xPos,
          yPos,
          portSize,
          connectors,
          vertical,
          color,
          lineWidth,
          aspectRatio,
          baseSizePerc,
          connectorSize
        );
      } else {
        g = new NotGate(
          xPos,
          yPos,
          portSize,
          1,//connectors,
          vertical,
          color,
          lineWidth,
          aspectRatio,
          baseSizePerc,
          connectorSize
        );
      }
    }
    g->draw();
    delay(1000);
  }  
};



void ScreenPort::draw(char* params[]){
  BaseScreen::draw(params);
  if (params != nullptr) {
    Gate* g = nullptr;
    if (params[0] == "AND") {
      g = new AndGate();        
    } else if (params[0] == "OR") {
      g = new OrGate();
    } else {
      g = nullptr; //random        
    }
    drawRandomGate(g);
    delete g;
    g = nullptr;
  } else {
    drawRandomGate(nullptr);
  }
};