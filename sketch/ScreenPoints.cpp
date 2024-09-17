#include "ScreenPoints.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"

ScreenPoints::ScreenPoints(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenPoints::draw(char* params[]){
  BaseScreen::draw(params);  
};