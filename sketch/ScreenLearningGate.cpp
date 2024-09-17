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
#include "Gates.h"


const char* portas[] = {"AND", "OR", "NOT", "NAND", "NOR", "XOR", "XNOR"};
const int totalPortas = sizeof(portas) / sizeof(portas[0]);


// Função para encontrar a próxima porta no array
const char* getNext(const char* nomePorta) {
    for (int i = 0; i < totalPortas; i++) {
        if (strcmp(portas[i], nomePorta) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == totalPortas - 1) {
                return portas[0];
            } else {
                // Senão, retorna a próxima porta
                return portas[i + 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}

const char* getPrev(const char* nomePorta) {
    for (int i = totalPortas-1; i >= 0; i--) {
        if (strcmp(portas[i], nomePorta) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == 0) {
                return portas[totalPortas-1];
            } else {
                // Senão, retorna a anterior porta
                return portas[i - 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}


ScreenLearningGate::ScreenLearningGate(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

ScreenLearningGate::~ScreenLearningGate(){
  delete currentGate;
  //delete evNext; //goback limpa os eventos
  //delete previousGateName;
  //delete currentGateName;
}
void ScreenLearningGate::drawGate(char* gateName, double x, double y, double size){
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

  SCtrl::tft.setCursor(containerX+5,containerY+5);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(DEFAULT_TEXT_COLOR);
  SCtrl::tft.print(gateName);

  currentGate = createGateByName(gateName,x,y,size);
  if (currentGate != nullptr) {
    currentGate->hasInputs = true;
    currentGate->draw();
  }

  if (gateName != portas[0]) {

  }


  if (currentGateName != portas[totalPortas-1]) {
    if (currentGateName == portas[0]) {
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
  if (currentGateName != portas[0]) {
    if (currentGateName == portas[totalPortas-1]) {
      if (evNext != nullptr) {
        /*delete evNext;
        evNext = nullptr;*/
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
  } 
}

void ScreenLearningGate::drawNextGate(double x, double y, double size){
  drawGate(getNext(currentGateName),x,y,size);
}

void ScreenLearningGate::drawPrevGate(double x, double y, double size){
  drawGate(getPrev(currentGateName),x,y,size);
}

void ScreenLearningGate::draw(char* params[]){
  Serial.println("INIT ScreenLearningGate::draw");
  BaseScreen::draw(params);    
  if (params != nullptr) {    
    Gate* g = nullptr;
    double gateSize = containerHeight * 0.4;
    double gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
    double gateX = containerX + containerWidth / 2 - gateWidth / 2;//SCtrl::tft.width() / 2 - gateWidth / 2;
    double gateY = containerY + containerHeight - containerHeight * DEFAULT_GATE_CONNECTOR_SIZE_PERC;//SCtrl::tft.height() - 75;
    drawGate(params[0],gateX,gateY,gateSize);   
  }  
};