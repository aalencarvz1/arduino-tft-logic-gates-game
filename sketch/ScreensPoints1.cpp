#include "ScreenPoints1.h"
#include "Utils.h"
#include "SCtrl.h"
#include "Gate.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "Gates.h"
#include "Colors.h"
#include "AndGate.h"
#include "OrGate.h"





ScreenPoints1::ScreenPoints1(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

ScreenPoints1::~ScreenPoints1(){
  if (currentGate != nullptr) {
    delete currentGate;
  }
  if (currentCircuit != nullptr) {
    delete currentCircuit;
  }
  if (evNext != nullptr) {
    delete evNext;
  }
  if (evPrev != nullptr) {
    delete evPrev;
  }
}
void ScreenPoints1::drawGate(char* gateName, double x, double y, double size, int pConnectorCount, double pGateWidth){
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
  }
  
  drawResult(false,resultX,resultY,resultSize,true);

  currentGate = Gates::createGateByName(
    gateName,
    x,
    y,
    size,
    pConnectorCount,
    DEFAULT_GATE_VERTICAL_DIRECTION,
    DEFAULT_GATE_LINE_COLOR,
    DEFAULT_GATE_LINE_WIDTH,
    DEFAULT_GATE_ASPECT_RATIO,
    DEFAULT_GATE_BASE_SIZE_PERC,
    DEFAULT_GATE_CONNECTOR_SIZE,
    pGateWidth
  );
  if (currentGate != nullptr) {
    currentGate->setHasInputs(true);
    currentGate->visibleOutput = false;
    currentGate->draw();
  }

  if (gateName != Gates::gateNames[0]) {

  }
}


/*
LEVELS:
DIFICULTY LEVEL 1 - PHASES 1-3 PORTS AND, OR, NOT WITH NAME
DIFICULTY LEVEL 2 - PHASES 1-4 PORTS NANT,NOR,XOR,XNOR IN RANDOMIC ORDER WITH NAME
DIFICULTY LEVEL 3 - PHASES 1-5 RANDOMIC PORTS WITHOUT NAME
DIFICULTY LEVEL 4 - PHASES 1-5 RANDOMIC PORTS (EXCEPT NOT) WITH 2 - 4 INPUTS 
DIFICULTY LEVEL 5 - PHASES 1-5 RANDOMIC PORTS WITH 2 LEVEL CIRCUIT (2 BASE PORTS + 1 OUTPUT PORT) WITH 2 INPUTS EACH
DIFICULTY LEVEL 6 - PHASES 1-5 RANDOMIC PORTS WITH 2 LEVEL CIRCUIT (2 BASE PORTS + 1 OUTPUT PORT) WITH 3-6 INPUTS EACH
DIFICULTY LEVEL 7+ - PHASES 1+ RANDOMIC PORTS WITH CURRENT LEVEL + 1 EACH 5 LEVELS LEVEL WITH 2-6 INPUTS EACH
*/
void ScreenPoints1::drawNextPhase(){
  if (currentDificultyLevel <= 4) { //gates

    //clear gate name
    SCtrl::tft.fillRect(
      containerX+5,
      containerY+5,
      100,
      50,
      DEFAULT_BACKGROUND_COLOR
    );

    SCtrl::tft.setCursor(containerX+5,containerY+5);
    SCtrl::tft.setTextSize(2);
    SCtrl::tft.setTextColor(TFT_CYAN);
    SCtrl::tft.print("Nivel " + String(currentDificultyLevel));

    SCtrl::tft.setCursor(containerX+5,containerY+25);
    SCtrl::tft.setTextSize(2);
    SCtrl::tft.setTextColor(TFT_DARKGREY);
    SCtrl::tft.print("Fase  " + String(currentPhase));

    int idGateName = currentPhase-1;
    int connectorCount = DEFAULT_GATE_CONNECTOR_COUNT;
    double gateWidth = DEFAULT_GATE_WIDTH;
    if (currentDificultyLevel == 2) {
      idGateName = random(3,7);
    } else if (currentDificultyLevel > 2) {
      idGateName = random(0,7);
    } 
    if (currentDificultyLevel == 4) {
      connectorCount = random(2,5);
    }
    SCtrl::drawCenteredText("Ative a porta",containerY+10);
    if (idGateName == Gates::gateNames[2]) { //NOT
      connectorCount = 1;
    }
    if (connectorCount > DEFAULT_GATE_CONNECTOR_COUNT) {
      gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
      gateWidth = gateWidth * (1 + ((connectorCount - DEFAULT_GATE_CONNECTOR_COUNT) / connectorCount));
    }
    drawGate(Gates::gateNames[idGateName],gateX,gateY,gateSize,connectorCount,gateWidth);
    if (currentDificultyLevel < 3) {
      SCtrl::drawCenteredText(Gates::gateNames[idGateName],currentGate->y-currentGate->size/2);
    }
  } else { //circuits  
    //clean areas

    drawResult(false,resultX,resultY,resultSize,true);
    //clear gate name
    SCtrl::tft.fillRect(
      containerX+5,
      containerY+5,
      100,
      50,
      DEFAULT_BACKGROUND_COLOR
    );

    double g1Size = (containerHeight / DEFAULT_GATE_ASPECT_RATIO) * 0.2;
    double g1Width = g1Size * DEFAULT_GATE_ASPECT_RATIO;
    double g1x = containerX + containerWidth / 2 - g1Width;
    double g1y = containerY + g1Size;

    GatesCircuit* cg = new GatesCircuit(containerX,containerY,containerWidth,containerHeight);
    cg->gateLevelCount = 4;
    cg->intermediaryOutputsVisible = true;
    //cg->intermediaryInputsVisible = true;
    //cg->setVertical(false);
    //cg->gateHorizontalAspectRatio = 0.55;

    currentGate = cg->createGate("OR");
    //currentGate->setConnectorCount(3);
    currentGate->draw();
    Gate* g2;
    for(int i = 0; i < Gates::gateNamesCount; i++) {
      g2 = cg->createGate(Gates::gateNames[i]);
      g2->draw();
    }
    for(int i = 0; i < 6; i++) {
      g2 = cg->createGate(Gates::gateNames[i]);
      g2->draw();
    }
    
  }
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
    drawCurrentPontuation();
  }
  /*drawResult(currentGate->outputState,resultX,resultY,resultSize);
  delay(2000); //2000
  if (currentPhase >= phasesByLevel[currentDificultyLevel-1]) {
    currentPhase = 1;
    currentDificultyLevel++;
  } else {
    currentPhase++;
  }  
  drawNextPhase(); */
}

void ScreenPoints1::drawConfirmButton(){
  double buttonWidth = 120;
  double buttonRightMargin = 5;
  double buttonHeight = 30;
  double buttonBottomMargin = buttonRightMargin;
  double borderRadius = 3;
  double x = containerX + containerWidth - buttonWidth - buttonRightMargin;
  double y = containerY -buttonHeight;//+ containerHeight - buttonHeight - buttonBottomMargin;
  SCtrl::tft.fillRoundRect(x,y,buttonWidth,buttonHeight,borderRadius,Colors::GREEN);
  SCtrl::drawCenteredText("Confirmar",y+buttonHeight/2-6,x+buttonWidth/2);
  evPrev = new EVRcpt(x+buttonWidth/2,y+buttonHeight/2,buttonWidth/2);    
  auto f = [this](){
    this->confirm();
  };
  evPrev->onClickCallback = new LambdaCallback<decltype(f)>(f);
}

void ScreenPoints1::pontuationTitle(){
  SCtrl::tft.setCursor(containerX + containerWidth - 110, containerY + 8);
  SCtrl::tft.setTextColor(TFT_CYAN);
  SCtrl::tft.print("Pontuacao");
}

void ScreenPoints1::drawCurrentPontuation(){
  SCtrl::tft.fillRect(containerX + containerWidth - 110, containerY + 24,109,19,DEFAULT_BACKGROUND_COLOR);
  char buffer[10]; // Array de char para armazenar o resultado
  itoa(currentPontuation, buffer, 10);
  SCtrl::drawCenteredText(buffer,containerY + 25,containerX + containerWidth - 110 / 2,2,TFT_CYAN);
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

  //if (params != nullptr) {    
    Gate* g = nullptr;
    drawConfirmButton();
    pontuationTitle();
    drawCurrentPontuation();
    //drawGate(params[0],gateX,gateY,gateSize);   
    drawNextPhase();
  //}  
};