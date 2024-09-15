#include "BaseScreen.h"
#include "EVRcpt.h"
#include "Screens.h"

BaseScreen::BaseScreen(char* pTitle, bool pHasBack) :
  title(pTitle),
  hasBack(pHasBack)
{

};

//back button
void BaseScreen::drawBackButton(){
  double px = 5.0;
  double py = 2.0;
  double w = 30.0;
  double h = 20.0;  
  SCtrl::tft.fillRoundRect(px,py,w,h,3,TFT_DARKGREY);
  SCtrl::tft.setCursor(px+w/2-8, py+3);
  SCtrl::tft.setTextSize(2);
  SCtrl::tft.setTextColor(DEFAULT_TEXT_COLOR);
  SCtrl::tft.print("<");
  EVRcpt* ev = new EVRcpt(px+w/2,py+h/2,w);
  ev->staticOnClick = [](){
    Screens::goBack();    
  };
};

void BaseScreen::draw(char* params[]) {
  SCtrl::tft.fillScreen(DEFAULT_BACKGROUND_COLOR);   
  titleInfo = SCtrl::drawCenteredText(title,DEFAULT_WINDOW_MARGIN,SCtrl::tft.width()/2,DEFAULT_WINDOW_TITLE_TEXT_SIZE,DEFAULT_TEXT_COLOR);
  containerX = DEFAULT_WINDOW_MARGIN;
  containerY = titleInfo.h+DEFAULT_WINDOW_MARGIN+5;
  containerWidth = SCtrl::tft.width() - DEFAULT_WINDOW_MARGIN * 2;
  containerHeight = SCtrl::tft.height() - (titleInfo.h+DEFAULT_WINDOW_MARGIN*2);
  SCtrl::tft.drawRect(containerX, containerY, containerWidth, containerHeight, DEFAULT_WINDOW_BORDER_COLOR);
  if (hasBack) {
    drawBackButton();
  }
};


