#include "ScreenInitialMenu.h"
#include "Utils.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenLearning.h"


void ScreenInitialMenu::draw(char* params[]) {
  BaseScreen::draw(params);
  /*SCtrl::tft.fillScreen(TFT_BLACK);  // Limpa a tela
  SCtrl::tft.setTextColor(TFT_WHITE);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setCursor(10, 10);
  TextInfo ti = SCtrl::drawCenteredText("PORTAS E CIRCUITOS");*/
  //SCtrl::tft.drawRect(5, titleInfo.h+10, SCtrl::tft.width() - 10, SCtrl::tft.height() - (titleInfo.h+10), TFT_WHITE);
  SCtrl::drawCenteredText("Modos de jogo",titleInfo.h+20);
  double _4Div = SCtrl::tft.width() / 4.0;
  double itemMenuXPos = _4Div / 2.0;
  double itemMenuYPos = SCtrl::tft.height() / 2.0;
  double itemR = itemMenuXPos * 0.6;
  
  SCtrl::drawRoundButton(itemMenuXPos, itemMenuYPos, itemR, TFT_YELLOW,"Tutorial",true,true,20,[](){    
    Screens::goTo(ScreenLearning::SCREEN_ID);
  });
  SCtrl::drawRoundButton(itemMenuXPos + _4Div , itemMenuYPos, itemR, TFT_BLUE,"Pontuacao",true,true,20);
  SCtrl::drawRoundButton(itemMenuXPos + _4Div * 2, itemMenuYPos, itemR, TFT_GREEN,"Tempo",true,true,20);
  SCtrl::drawRoundButton(itemMenuXPos + _4Div * 3, itemMenuYPos, itemR, TFT_RED,"Construa",true,true,20);
};