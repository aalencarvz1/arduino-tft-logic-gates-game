#include "ScreenPoints1.h"
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
#include "Gates.h"
#include "Colors.h"


ScreenPoints1::ScreenPoints1(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

ScreenPoints1::~ScreenPoints1(){
  delete currentGate;
}
void ScreenPoints1::drawGate(char* gateName, double x, double y, double size){
  previousGateName = currentGateName;
  currentGateName = gateName;
  //clear previous gate space
  if (currentGate != nullptr) {
    SCtrl::tft.fillRect(
      currentGate->x-DEFAULT_GATE_MAX_INPUT_RADIUS,
      containerY + 1,//currentGate->y-currentGate->size-currentGate->connectorSize,
      currentGate->width+DEFAULT_GATE_MAX_INPUT_RADIUS*2,
      containerY + containerHeight - 30, //currentGate->size+2*currentGate->connectorSize
      DEFAULT_BACKGROUND_COLOR
    );
    delete currentGate;
    //currentGate = nullptr;

    //clear gate name
    SCtrl::tft.fillRect(
      containerX+5,
      containerY+5,
      50,
      20,
      DEFAULT_BACKGROUND_COLOR
    );
  }

  /*SCtrl::tft.setCursor(containerX+5,containerY+5);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(DEFAULT_TEXT_COLOR);
  SCtrl::tft.print(gateName);*/

  currentGate = Gates::createGateByName(gateName,x,y,size);
  if (currentGate != nullptr) {
    currentGate->hasInputs = true;
    currentGate->visibleOutput = false;
    currentGate->draw();
  }

  if (gateName != Gates::portas[0]) {

  }


  /*if (currentGateName != Gates::portas[Gates::totalPortas-1]) {
    if (currentGateName == Gates::portas[0]) {
      if (evPrev != nullptr) {
        //delete evPrev;
        //evPrev = nullptr;
        evPrev->enabled = false;
      }
      SCtrl::drawRoundedPlay(containerX+50,containerY + containerHeight /2,35,4,DEFAULT_BACKGROUND_COLOR,DEFAULT_BACKGROUND_COLOR,-1);  
    }
    if (evNext == nullptr) {
      evNext = new EVRcpt(containerX+containerWidth-50,containerY + containerHeight /2,30);    
      auto f = [this,x,y,size](){
        this->drawNextGate(x,y,size);
      };
      evNext->onClickCallback = new LambdaCallback<decltype(f)>(f);
      SCtrl::drawRoundedPlay(containerX+containerWidth-50,containerY + containerHeight /2,30,4,DEFAULT_BACKGROUND_COLOR,TFT_YELLOW);
    } else if (!evNext->enabled) {
      evNext->enabled = true;
      SCtrl::drawRoundedPlay(containerX+containerWidth-50,containerY + containerHeight /2,30,4,DEFAULT_BACKGROUND_COLOR,TFT_YELLOW);
    }
  } 
  if (currentGateName != Gates::portas[0]) {
    if (currentGateName == Gates::portas[Gates::totalPortas-1]) {
      if (evNext != nullptr) {
        evNext->enabled = false;
      }
      SCtrl::drawRoundedPlay(containerX+containerWidth-50,containerY + containerHeight /2,35,4,DEFAULT_BACKGROUND_COLOR,DEFAULT_BACKGROUND_COLOR);
    }
    if (evPrev == nullptr) {
      evPrev = new EVRcpt(containerX+50,containerY + containerHeight /2,30);    
      auto f = [this,x,y,size](){
        this->drawPrevGate(x,y,size);
      };
      evPrev->onClickCallback = new LambdaCallback<decltype(f)>(f);
      SCtrl::drawRoundedPlay(containerX+50,containerY + containerHeight /2,30,4,DEFAULT_BACKGROUND_COLOR,TFT_YELLOW,-1);  
    } else if (!evPrev->enabled){
      evPrev->enabled = true;
      SCtrl::drawRoundedPlay(containerX+50,containerY + containerHeight /2,30,4,DEFAULT_BACKGROUND_COLOR,TFT_YELLOW,-1);  
    }       
  } */
}

void ScreenPoints1::drawNextGate(double x, double y, double size){
  drawGate(Gates::getNext(currentGateName),x,y,size);
}

void ScreenPoints1::drawPrevGate(double x, double y, double size){
  drawGate(Gates::getPrev(currentGateName),x,y,size);
}

void ScreenPoints1::confirm(){
  currentGate->inputs[currentGate->connectorCount]->visible = true;
  currentGate->inputs[currentGate->connectorCount]->draw();
  if (currentGate->outputState) {
    currentPontuation++;
    pontuationCurrentPontuation();
  }
}

void ScreenPoints1::drawConfirmButton(){
  double buttonWidth = 120;
  double buttonRightMargin = 5;
  double buttonHeight = 30;
  double buttonBottomMargin = buttonRightMargin;
  double borderRadius = 3;
  double x = containerX + containerWidth - buttonWidth - buttonRightMargin;
  double y = containerY + containerHeight - buttonHeight - buttonBottomMargin;
  SCtrl::tft.fillRoundRect(x,y,buttonWidth,buttonHeight,borderRadius,Colors::GREEN);
  SCtrl::drawCenteredText("Confirmar",y+buttonHeight/2-6,x+buttonWidth/2);
  evPrev = new EVRcpt(x+buttonWidth/2,containerY + y+buttonHeight/2,buttonWidth);    
  auto f = [this](){
    this->confirm();
  };
  evPrev->onClickCallback = new LambdaCallback<decltype(f)>(f);
}

void ScreenPoints1::pontuationTitle(){
  SCtrl::tft.setCursor(containerX + containerWidth - 110, containerY + 8);
  SCtrl::tft.print("Pontuacao");
}

void ScreenPoints1::pontuationCurrentPontuation(){
  SCtrl::tft.fillRect(containerX + containerWidth - 110, containerY + 24,109,19,DEFAULT_BACKGROUND_COLOR);
  char buffer[10]; // Array de char para armazenar o resultado
  itoa(currentPontuation, buffer, 10);
  SCtrl::drawCenteredText(buffer,containerY + 25,containerX + containerWidth - 110 / 2);
}

void ScreenPoints1::draw(char* params[]){
  Serial.println("INIT ScreenPoints1::draw");
  BaseScreen::draw(params);    
  if (params != nullptr) {    
    Gate* g = nullptr;
    double gateSize = containerHeight * 0.4;
    double gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
    double gateX = containerX + containerWidth / 2 - gateWidth / 2;//SCtrl::tft.width() / 2 - gateWidth / 2;
    double gateY = containerY + containerHeight - containerHeight * DEFAULT_GATE_CONNECTOR_SIZE_PERC;//SCtrl::tft.height() - 75;
    drawConfirmButton();
    pontuationTitle();
    pontuationCurrentPontuation();
    drawGate(params[0],gateX,gateY,gateSize);   
  }  
};