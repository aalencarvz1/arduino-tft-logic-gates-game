#include "ScreenTime.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"

ScreenTime::ScreenTime(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenTime::draw(char* params[]){
  BaseScreen::draw(params);  
};