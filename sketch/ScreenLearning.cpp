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
  FREERAM_PRINT;
  EVRcpt* ev = new EVRcpt(x + (col * (x*2.0)),y + hSupSpace + (lin * (y * 2.0)),r);
  auto f = [gateName](){
    char* params[] = {gateName, nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  };
  ev->onClickCallback = new LambdaCallback<decltype(f)>(f);
  Gate* g = Gates::createGateByName(gateName,x+(col*(x*2.0))-(r*0.35),y+hSupSpace+(lin*(y*2.0))+(r*0.35),r*0.7);    
  if (g != nullptr) {
    g->lineColor = TFT_WHITE;//TFT_BLACK;//TFT_LIGHTGREY;
    g->draw();
    delete g;
    g = nullptr;
  }
  FREERAM_PRINT;
}


ScreenLearning::ScreenLearning(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenLearning::draw(char* params[]){
  BaseScreen::draw(params);

  //linha 1, 3 colunas
  int cols = 3;
  int lins = 2;
  double x = containerWidth / cols;
  x = x / 2.0;
  double y = containerHeight / lins;
  y = y / 2.0;
  double r = x;
  if (y < x) {
    r = y;
  }
  r = r * 0.5;
  int col = 0;
  int lin = 0;
  double marginSup = 15;
  double hSpace = 0;

  //Gate* g = createGateByName("AND",x+(col*(x*2.0))-(r*0.35),y+marginSup+(lin*(y*2.0))+(r*0.35),r*2);    
  //g->draw();
  /*AndGate* g = new AndGate(107.4989,201.954,109.799889);
  //g->lineWidth = 3;
  g->draw();*/

  drawGateButton(x,y,r,col,lin,marginSup,TFT_DARKCYAN,"AND");
  drawGateButton(x,y,r,col+1,lin,marginSup,TFT_DARKGREY,"OR");
  drawGateButton(x,y,r,col+2,lin,marginSup,TFT_RED,"NOT");

  //linha 2, 4 colunas
  cols = 4;
  x = containerWidth / cols;
  x = x / 2.0;
  col = 0;
  lin++;
  drawGateButton(x,y,r,col,lin,hSpace,TFT_OLIVE,"NAND");
  drawGateButton(x,y,r,col+1,lin,hSpace,TFT_ORANGE,"NOR");
  drawGateButton(x,y,r,col+2,lin,hSpace,TFT_MAGENTA,"XOR");
  drawGateButton(x,y,r,col+3,lin,hSpace,TFT_PURPLE,"XNOR");
};