#include "ScreenPoints.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"
#include "ScreenPoints1.h"
#include "Colors.h"

ScreenPoints::ScreenPoints(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenPoints::draw(char* params[]){
  BaseScreen::draw(params);  
  double x = containerX + containerWidth / 2;
  x = x /2;
  double y = containerY + containerHeight / 2;
  double r = y;
  if (y > x) {
    r = x;
  }
  r = r * 0.4;

  SCtrl::drawRoundButton(x,y,r,Colors::BLUE,"Jogar",true,true,10.0,[](){
    char* params[] = {"AND", nullptr};
    Screens::goTo(ScreenPoints1::SCREEN_ID,params);
  });  

};