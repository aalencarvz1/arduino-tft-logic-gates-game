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
      containerY +  25,//currentGate->y-currentGate->size-currentGate->connectorSize,
      currentGate->width+DEFAULT_GATE_MAX_INPUT_RADIUS*2,
      containerY + containerHeight - 55, //currentGate->size+2*currentGate->connectorSize
      DEFAULT_BACKGROUND_COLOR
    );
    delete currentGate;
    //currentGate = nullptr;

    //clear gate name
    SCtrl::tft.fillRect(
      containerX+5,
      containerY+5,
      100,
      20,
      DEFAULT_BACKGROUND_COLOR
    );
  }
  
  drawResult(false,resultX,resultY,resultSize,true);

  SCtrl::tft.setCursor(containerX+5,containerY+5);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(DEFAULT_TEXT_COLOR);
  SCtrl::tft.print("Fase " + String(currentLevel));
  drawResult(false,resultX,resultY,resultSize,true);

  currentGate = Gates::createGateByName(gateName,x,y,size);
  if (currentGate != nullptr) {
    currentGate->hasInputs = true;
    currentGate->visibleOutput = false;
    currentGate->draw();
  }

  if (gateName != Gates::portas[0]) {

  }

}

void ScreenPoints1::drawNextLevel(double x, double y, double size){
  SCtrl::drawCenteredText("Ative a porta",containerY+10);
  drawGate(currentLevel > 1 ? Gates::getNext(currentGateName) : Gates::portas[0],x,y,size);
}

void ScreenPoints1::drawResult(bool isCorrect, double centerX, double centerY, double size, bool onlyClean) {
  int halfSize = size / 2;

  // Limpa a área onde o símbolo será desenhado
  SCtrl::tft.fillRect(centerX - halfSize - 2, centerY - halfSize - 2, size + 4, size + 4, DEFAULT_BACKGROUND_COLOR);
  if (!onlyClean) {
    if (isCorrect) {
      // Desenha o símbolo de check verde
      SCtrl::tft.drawLine(centerX - halfSize, centerY, centerX - halfSize / 2, centerY + halfSize, TFT_GREEN);
      SCtrl::tft.drawLine(centerX - halfSize / 2, centerY + halfSize, centerX + halfSize, centerY - halfSize, TFT_GREEN);
    } else {
      // Desenha o símbolo de X vermelho
      SCtrl::tft.drawLine(centerX - halfSize, centerY - halfSize, centerX + halfSize, centerY + halfSize, TFT_RED);
      SCtrl::tft.drawLine(centerX + halfSize, centerY - halfSize, centerX - halfSize, centerY + halfSize, TFT_RED);
    }
  }
}

void ScreenPoints1::confirm(){
  currentGate->inputs[currentGate->connectorCount]->visible = true;
  currentGate->inputs[currentGate->connectorCount]->draw();
  if (currentGate->outputState) {
    currentPontuation++;
    pontuationCurrentPontuation();
  }
  drawResult(currentGate->outputState,resultX,resultY,resultSize);
  delay(2000);
  currentLevel++;
  drawNextLevel(gateX,gateY,gateSize); 
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
  gateSize = containerHeight * 0.4;
  gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
  gateX = containerX + containerWidth / 2 - gateWidth / 2;//SCtrl::tft.width() / 2 - gateWidth / 2;
  gateY = containerY + containerHeight - containerHeight * DEFAULT_GATE_CONNECTOR_SIZE_PERC + 15;//SCtrl::tft.height() - 75;   

  resultX = containerX+containerWidth-100;
  resultY = containerY+containerHeight/2;
  resultSize = 50;

  if (params != nullptr) {    
    Gate* g = nullptr;
    drawConfirmButton();
    pontuationTitle();
    pontuationCurrentPontuation();
    //drawGate(params[0],gateX,gateY,gateSize);   
    drawNextLevel(gateX,gateY,gateSize);
  }  
};