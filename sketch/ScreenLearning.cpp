#include "ScreenLearning.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenLearningGate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "ScreenPort.h"
#include "NotGate.h"

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
  //ti = SCtrl::drawCenteredText("Escolha uma porta",ti.h+20);

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

  SCtrl::drawRoundButton(x + (col * (x*2.0)),y + marginSup + (lin * (y * 2.0)),r,PESSSEGO_CLARO,"AND",false,true,10.0,[](){
    char* params[] = {"AND", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });
  AndGate* ag = new AndGate(
    x+(col*(x*2.0))-(r*0.35),
    y+marginSup+(lin*(y*2.0))+(r*0.35),
    r*0.7
  );
  ag->lineColor = TFT_LIGHTGREY;
  ag->draw();
  delete ag;
  ag = nullptr;

  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y +marginSup+ (lin * (y * 2)),r,TFT_GREEN,"OR",false,true,10,[](){
    char* params[] = {"OR", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });
  OrGate* og = new OrGate(
    x+(col*(x*2.0))-(r*0.35),
    y+marginSup+(lin*(y*2.0))+(r*0.35),
    r*0.7
  );
  og->lineColor = TFT_DARKGREY;
  og->draw();
  delete og;
  og = nullptr;

  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y +marginSup+ (lin * (y * 2)),r,TFT_RED,"NOT",false,true,10,[](){
    char* params[] = {"NOT", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });
  NotGate* ng = new NotGate(
    x+(col*(x*2.0))-(r*0.35),
    y+marginSup+(lin*(y*2.0))+(r*0.35),
    r*0.7
  );
  ng->lineColor = TFT_DARKGREY;
  ng->draw();
  delete ng;
  ng = nullptr;


  //linha 2
  col = 0;
  lin++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + hSpace + (lin * (y * 2)),r,TFT_YELLOW,"NAND",false,true,10,[](){
    char* params[] = {"NAND", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });
  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + hSpace + (lin * (y * 2)),r,TFT_CYAN,"NOR",false,true,10,[](){
    char* params[] = {"NOR", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });
  col++;
  SCtrl::drawRoundButton(x + (col * (x*2)),y + hSpace + (lin * (y * 2)),r,TFT_MAGENTA,"XOR",false,true,10,[](){
    char* params[] = {"XOR", nullptr};
    Screens::goTo(ScreenLearningGate::SCREEN_ID,params);
  });

};