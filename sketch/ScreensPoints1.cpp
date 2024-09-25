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
  Serial.println("INIT ScreenPoints1::ScreenPoints1");
  Serial.println("END ScreenPoints1::ScreenPoints1");
};

ScreenPoints1::~ScreenPoints1(){
  Serial.println("INIT ScreenPoints1::~ScreenPoints1");
  freeMemory();
  if (evNext != nullptr) {
    //delete evNext;
    event_receipts->remove(evNext);
    evNext = nullptr;
  }
  if (evPrev != nullptr) {
    //delete evPrev;
    event_receipts->remove(evPrev);
    evPrev = nullptr;
  }
  Serial.println("END ScreenPoints1::~ScreenPoints1");
}

void ScreenPoints1::freeMemory(){
  Serial.println("INIT ScreenPoints1::freeMemory");
  if (currentGate != nullptr) {
    delete currentGate;
    currentGate = nullptr;
  }
  if (currentCircuit != nullptr) {
    delete currentCircuit;
    currentCircuit = nullptr;
  }
  Serial.println("END ScreenPoints1::freeMemory");
}





void ScreenPoints1::clearLevelAndPhaseTextSpace(){
  Serial.println("INIT ScreenPoints1::clearLevelAndPhaseTextSpace");
  SCtrl::tft.fillRect(
    containerX+5,
    containerY+5,
    100,
    50,
    DEFAULT_BACKGROUND_COLOR
  );
  Serial.println("END ScreenPoints1::clearLevelAndPhaseTextSpace");
};

void ScreenPoints1::drawLevelAndPhaseText(){
  Serial.println("INIT ScreenPoints1::drawLevelAndPhaseText");
  clearLevelAndPhaseTextSpace();
  SCtrl::tft.setCursor(containerX+5,containerY+5);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(TFT_CYAN);
  SCtrl::tft.print("Nivel " + String(currentDificultyLevel));

  SCtrl::tft.setCursor(containerX+5,containerY+25);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(TFT_DARKGREY);
  SCtrl::tft.print("Fase  " + String(currentPhase));
  Serial.println("END ScreenPoints1::drawLevelAndPhaseText");
}

void ScreenPoints1::clearLeftSide(){
  Serial.println("INIT ScreenPoints1::clearLeftSide");
  double topMargin = 42;
  double sideSapces = 150;
  //left side space
  SCtrl::tft.fillRect(
    containerX+DEFAULT_WINDOW_BORDER_WIDTH,
    containerY+DEFAULT_WINDOW_BORDER_WIDTH + topMargin,
    sideSapces,
    containerHeight - DEFAULT_WINDOW_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  Serial.println("END ScreenPoints1::clearLeftSide");
};

void ScreenPoints1::clearRightSide(){
  Serial.println("INIT ScreenPoints1::clearRightSide");
  double topMargin = 42;
  double sideSapces = 150;
  //right side space
  SCtrl::tft.fillRect(
    containerX + containerWidth - DEFAULT_WINDOW_BORDER_WIDTH - sideSapces,
    containerY+DEFAULT_WINDOW_BORDER_WIDTH + topMargin,
    sideSapces,
    containerHeight - DEFAULT_WINDOW_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  Serial.println("END ScreenPoints1::clearRightSide");
};

void ScreenPoints1::clearCenterSpace(){
  Serial.println("INIT ScreenPoints1::clearCenterSpace");
  double topMargin = 42;
  double sideSapces = 150;
  //center space
  SCtrl::tft.fillRect(
    containerX + DEFAULT_WINDOW_BORDER_WIDTH + sideSapces,
    containerY+DEFAULT_WINDOW_BORDER_WIDTH + topMargin,
    containerWidth - sideSapces * 2,
    containerHeight - DEFAULT_WINDOW_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  Serial.println("END ScreenPoints1::clearCenterSpace");
};

void ScreenPoints1::clearTopTextSpace(){
  Serial.println("INIT ScreenPoints1::clearTopTextSpace");
  double topMargin = 42;
  double sideSapces = 150;
  //center top text space
  SCtrl::tft.fillRect(
    containerX + DEFAULT_WINDOW_BORDER_WIDTH + sideSapces - 40,
    containerY+DEFAULT_WINDOW_BORDER_WIDTH,
    containerWidth - sideSapces * 2 + 70,
    topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  Serial.println("END ScreenPoints1::clearTopTextSpace");
};

void ScreenPoints1::clearGateSpace(Gate* pGate, bool pDelete){
  Serial.println("INIT ScreenPoints1::clearGateSpace");
  if (pGate != nullptr) {
    SCtrl::tft.fillRect(
      pGate->x-DEFAULT_GATE_MAX_INPUT_RADIUS,
      containerY +  25,//pGate->y-pGate->size-pGate->connectorSize,
      pGate->width+DEFAULT_GATE_MAX_INPUT_RADIUS*2,
      containerY + containerHeight - 55, //pGate->size+2*pGate->connectorSize
      DEFAULT_BACKGROUND_COLOR
    );
    if (pDelete) {
      delete pGate;
      pGate = nullptr;
    }
  } else {
    clearCenterSpace();
  }
  Serial.println("END ScreenPoints1::clearGateSpace");
};


void ScreenPoints1::drawGate(char* gateName, double x, double y, double size, int pConnectorCount, double pGateWidth){
  Serial.println("INIT ScreenPoints1::drawGate");
  previousGateName = currentGateName;
  currentGateName = gateName;
  clearGateSpace(currentGate);
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
  Serial.println("END ScreenPoints1::drawGate");
}

void ScreenPoints1::drawGateLevel(){
  Serial.println("INIT ScreenPoints1::drawGateLevel");
  if (currentDificultyLevel <= 4) { //gates

  //clear nivel and phase text
    drawLevelAndPhaseText();

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
  }
  Serial.println("END ScreenPoints1::drawGateLevel");
}

void ScreenPoints1::drawCircuitLevel(){
  Serial.println("INIT ScreenPoints1::drawCircuitLevel");
  //clean areas
  clearLeftSide();
  clearRightSide();
  clearCenterSpace();
  clearTopTextSpace();
  drawLevelAndPhaseText();

  if (currentCircuit != nullptr) {
    delete currentCircuit;
    currentCircuit = nullptr;
  }
  FREERAM_PRINT;
  if (currentDificultyLevel == 5) {
    if (currentPhase == 1) {
      char* gatesNames[] = {"AND","NOT","BYPASS",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
    } else if (currentPhase == 2) {
      char* gatesNames[] = {"NOT","AND",nullptr};  
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
      Serial.println("ok2");
    } else if (currentPhase == 3) {
      char* gatesNames[] = {"OR","AND","NOT",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
    } else if (currentPhase == 4) {
      char* gatesNames[] = {"AND","AND","XOR",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
    } else if (currentPhase == 5) {
      char* gatesNames[] = {"AND","AND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
    } 
  } if (currentDificultyLevel == 6) {
    if (currentPhase == 1) {
      char* gatesNames[] = {"AND","AND","XOR",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        3,
        gatesNames,
        true
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = static_cast<Gate*>(currentCircuit->gates->tail->prev->data);
      Gate* pg1 = static_cast<Gate*>(currentCircuit->gates->tail->prev->prev->data);
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      g->addOutputInput(pg->inputs[0]);
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 2) {
      char* gatesNames[] = {"AND","AND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        3,
        gatesNames,
        true
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = static_cast<Gate*>(currentCircuit->gates->tail->prev->data);
      Gate* pg1 = static_cast<Gate*>(currentCircuit->gates->tail->prev->prev->data);
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      g->addOutputInput(pg->inputs[0]);
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 3) {
      char* gatesNames[] = {"OR","NAND","AND",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        2,
        gatesNames,
        true
      );
    } else if (currentPhase == 4) {
      char* gatesNames[] = {"OR","NAND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        3,
        gatesNames,
        true
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = static_cast<Gate*>(currentCircuit->gates->tail->prev->data);
      Gate* pg1 = static_cast<Gate*>(currentCircuit->gates->tail->prev->prev->data);
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      g->addOutputInput(pg->inputs[0]);
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 5) {
      char* gatesNames[] = {"OR","AND","AND","NOT","BYPASS","BYPASS","BYPASS","BYPASS",nullptr};          
      currentCircuit = new GatesCircuit(
        containerX,
        containerY,
        containerWidth,
        containerHeight,
        4,
        gatesNames,
        true
      );

      Gate* pg = static_cast<Gate*>(currentCircuit->gates->tail->prev->prev->data);
      Gate* pg1 = static_cast<Gate*>(currentCircuit->gates->tail->prev->prev->prev->data);
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x-pg1->x)/2,-1);
      g->addOutputInput(pg->inputs[0]);
      g->draw();
      g = currentCircuit->createGate("NOT");
      g->draw();

      /*Gate* g = static_cast<Gate*>(currentCircuit->gates->tail->data);
      Gate* pg = static_cast<Gate*>(currentCircuit->gates->tail->prev->data);
      g->addOutputInput(pg->inputs[0]);
      g->draw();
      g = currentCircuit->createGate("NOT",pg->inputs[1]);
      g->draw();*/
    }
  }
  FREERAM_PRINT;
  Serial.println("END ScreenPoints1::drawCircuitLevel");
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
  Serial.println("INIT ScreenPoints1::drawNextPhase");
  freeMemory();
  if (currentDificultyLevel <= 4) { //gates
    drawGateLevel();
  } else { //circuits  
    drawCircuitLevel();
  }
  Serial.println("END ScreenPoints1::drawNextPhase");
}

void ScreenPoints1::drawResult(bool isCorrect, double centerX, double centerY, double size, bool onlyClean) {
  Serial.println("INIT ScreenPoints1::drawResult");
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
  Serial.println("END ScreenPoints1::drawResult");
}

void ScreenPoints1::confirm(){
  Serial.println("INIT ScreenPoints1::confirm");
  currentGate->inputs[currentGate->connectorCount]->visible = true;
  currentGate->inputs[currentGate->connectorCount]->draw();
  if (currentGate->outputState) {
    currentPontuation++;
    drawCurrentPontuation();
  }
  drawResult(currentGate->outputState,resultX,resultY,resultSize);
  delay(500); //2000
  if (currentPhase >= phasesByLevel[currentDificultyLevel-1]) {
    currentPhase = 1;
    currentDificultyLevel++;
  } else {
    currentPhase++;
  }  
  drawNextPhase();
  Serial.println("END ScreenPoints1::confirm");
}

void ScreenPoints1::drawConfirmButton(){
  Serial.println("INIT ScreenPoints1::drawConfirmButton");
  double buttonWidth = 120;
  double buttonRightMargin = 0;
  double buttonHeight = 25;
  double buttonTopMargin = 0;
  double borderRadius = 3;
  double x = containerX + containerWidth - buttonWidth - buttonRightMargin;
  double y = containerY - buttonHeight + buttonTopMargin;//+ containerHeight - buttonHeight - buttonTopMargin;
  SCtrl::tft.fillRoundRect(x,y,buttonWidth,buttonHeight,borderRadius,Colors::GREEN);
  SCtrl::drawCenteredText("Confirmar",y+buttonHeight/2-6,x+buttonWidth/2);
  FREERAM_PRINT;
  evPrev = new EVRcpt(x+buttonWidth/2,y+buttonHeight/2,buttonWidth/2);    
  auto f = [this](){
    this->confirm();
  };
  evPrev->onClickCallback = new LambdaCallback<decltype(f)>(f);
  FREERAM_PRINT;
  Serial.println("END ScreenPoints1::drawConfirmButton");
}

void ScreenPoints1::pontuationTitle(){
  Serial.println("INIT ScreenPoints1::pontuationTitle");
  SCtrl::tft.setCursor(containerX + containerWidth - 110, containerY + 8);
  SCtrl::tft.setTextColor(TFT_CYAN);
  SCtrl::tft.print("Pontuacao");
  Serial.println("END ScreenPoints1::pontuationTitle");
}

void ScreenPoints1::drawCurrentPontuation(){
  Serial.println("INIT ScreenPoints1::drawCurrentPontuation");
  SCtrl::tft.fillRect(containerX + containerWidth - 110, containerY + 24,109,19,DEFAULT_BACKGROUND_COLOR);
  char buffer[10]; // Array de char para armazenar o resultado
  itoa(currentPontuation, buffer, 10);
  SCtrl::drawCenteredText(buffer,containerY + 25,containerX + containerWidth - 110 / 2,2,TFT_CYAN);
  Serial.println("END ScreenPoints1::drawCurrentPontuation");
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
  Serial.println("END ScreenPoints1::draw");
};