#include "ScreenInitialMenu.h"
#include "Utils.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenLearning.h"
#include "ScreenPoints.h"
#include "ScreenTime.h"
#include "ScreenMake.h"


ScreenInitialMenu::ScreenInitialMenu(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenInitialMenu::draw(char* params[]) {
  BaseScreen::draw(params);
  SCtrl::drawCenteredText("Modos de jogo",titleInfo.h+20);
  double _4Div = SCtrl::tft.width() / 4.0;
  double itemMenuXPos = _4Div / 2.0;
  double itemMenuYPos = SCtrl::tft.height() / 2.0;
  double itemR = itemMenuXPos * 0.6;
  
  SCtrl::drawRoundButton(itemMenuXPos, itemMenuYPos, itemR, TFT_YELLOW,"Tutorial",true,true,20,[](){    
    Screens::goTo(ScreenLearning::SCREEN_ID);
  });
  SCtrl::drawRoundButton(itemMenuXPos + _4Div , itemMenuYPos, itemR, TFT_BLUE,"Pontuacao",true,true,20,[](){    
    Screens::goTo(ScreenPoints::SCREEN_ID);
  });
  SCtrl::drawRoundButton(itemMenuXPos + _4Div * 2, itemMenuYPos, itemR, TFT_GREEN,"Tempo",true,true,20,[](){    
    Screens::goTo(ScreenTime::SCREEN_ID);
  });
  SCtrl::drawRoundButton(itemMenuXPos + _4Div * 3, itemMenuYPos, itemR, TFT_RED,"Construa",true,true,20,[](){    
    Screens::goTo(ScreenMake::SCREEN_ID);
  });
};