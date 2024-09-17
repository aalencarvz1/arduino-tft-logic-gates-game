#include "ScreenMake.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"

ScreenMake::ScreenMake(char* pTitle, bool pHasBack) :
  BaseScreen(pTitle,pHasBack)
{
  
};

void ScreenMake::draw(char* params[]){
  BaseScreen::draw(params);  
};