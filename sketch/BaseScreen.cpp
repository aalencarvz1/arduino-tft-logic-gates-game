#include "BaseScreen.h"
#include "SCtrl.h"
#include "EVRcpt.h"
#include "Screens.h"

//back button
void BaseScreen::drawBackButton(){
  double px = 5.0;
  double py = 2.0;
  double size = 22.0;
  SCtrl::tft.fillRoundRect(px,py,size,size,3,TFT_DARKGREY);
  SCtrl::drawCenteredText("<",py+5.0, px+((size-px)/2.0));
  EVRcpt* ev = new EVRcpt(0,py+5,size/1.5);
  ev->staticOnClick = [](){
    Screens::goBack();    
  };
}


