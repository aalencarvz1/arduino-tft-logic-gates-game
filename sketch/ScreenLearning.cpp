#include "ScreenLearning.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenLearningGate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "ScreenPort.h"
#include "NotGate.h"
#include "NandGate.h"
#include "Gates.h"


void drawGateButton(
  double x,
  double y,
  double r,
  int col,
  int lin,
  double hSupSpace,
  int color,
  char* gateName
){
  SCtrl::drawRoundButton(x + (col * (x*2.0)),y + hSupSpace + (lin * (y * 2.0)),r,color,gateName,false,true,10.0);
  EVRcpt* ev = new EVRcpt(x + (col * (x*2.0)),y + hSupSpace + (lin * (y * 2.0)),r);
  auto f = [gateName](){
    char* params[] = {gateName, nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  };
  ev->onClickCallback = new LambdaCallback<decltype(f)>(f);  
  Gate* g = createGateByName(gateName,x+(col*(x*2.0))-(r*0.35),y+hSupSpace+(lin*(y*2.0))+(r*0.35),r*0.7);    
  if (g != nullptr) {
    g->lineColor = TFT_LIGHTGREY;
    g->draw();
    delete g;
    g = nullptr;
  }
}

void ScreenLearning::draw(char* params[]){
  Serial.println("INIT ScreenLearning::draw");
  Serial.println("ILD");
  SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
  SCtrl::tft.setTextColor(TFT_WHITE);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setCursor(10, 10);
  TextInfo ti = SCtrl::drawCenteredText("MODO APRENDER");
  this->drawBackButton();
  SCtrl::tft.drawRect(5, ti.h+10, SCtrl::tft.width() - 10, SCtrl::tft.height() - (ti.h+10), TFT_WHITE);


  //linha 1, 3 colunas
  int cols = 3;
  int lins = 2;
  double x = (SCtrl::tft.width() * 1.0) / cols;
  x = x / 2.0;
  double y = (SCtrl::tft.height() * 1.0 - ti.y) / lins;
  y = y / 2.0;
  double r = x;
  if (y < x) {
    r = y;
  }
  r = r * 0.5;
  int col = 0;
  int lin = 0;
  double marginSup = 15;
  double hSpace = -15;
  drawGateButton(x,y,r,col,lin,marginSup,TFT_GREEN,"AND");
  drawGateButton(x,y,r,col+1,lin,marginSup,TFT_YELLOW,"OR");
  drawGateButton(x,y,r,col+2,lin,marginSup,TFT_RED,"NOT");

  //linha 2, 4 colunas
  cols = 4;
  x = (SCtrl::tft.width() * 1.0) / cols;
  x = x / 2.0;
  col = 0;
  lin++;
  drawGateButton(x,y,r,col,lin,hSpace,TFT_GREENYELLOW,"NAND");
  drawGateButton(x,y,r,col+1,lin,hSpace,TFT_ORANGE,"NOR");
  drawGateButton(x,y,r,col+2,lin,hSpace,TFT_MAGENTA,"XOR");
  drawGateButton(x,y,r,col+3,lin,hSpace,TFT_PURPLE,"XNOR");
};