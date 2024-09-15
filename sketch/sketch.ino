#include "SCtrl.h"
#include "EVRcpt.h"
#include "AndGate.h"
#include "Screens.h"
#include "ScreenInitialMenu.h"
#include "ScreenLearning.h"
#include "ScreenPort.h"

bool inClick = false; //AVOID LOOP ON DISPATH MULTIPLE CLICKS AT SOME TIME

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SCtrl::init(); 
  SCtrl::tft.fillScreen(TFT_BLACK);
  //Screens::goTo(ScreenInitialMenu::SCREEN_ID);
  //Screens::goTo(ScreenLearning::SCREEN_ID);
  Screens::goTo(ScreenPort::SCREEN_ID);
  /*AndGate* g = new AndGate(
    50.0, 
    50.0,
    DEFAULT_GATE_SIZE,
    4,//DEFAULT_GATE_CONNECTOR_COUNT,	
    DEFAULT_GATE_VERTICAL_DIRECTION,
    DEFAULT_GATE_LINE_COLOR,
    DEFAULT_GATE_LINE_WIDTH,
    1.5,//DEFAULT_GATE_ASPECT_RATIO,
    DEFAULT_GATE_BASE_SIZE_PERC,
    DEFAULT_GATE_CONNECTOR_SIZE,
    DEFAULT_GATE_WIDTH,
    DEFAULT_GATE_CONNECTOR_MARGIN
  );
  g->hasInputs=true;
  g->draw();*/

}

void loop() {
  //get clicked point (if cliqued, z > 0, z = pressure)
  TSPoint p = SCtrl::ts.getPoint();

  //stackoverflow credits: restore status of shared pins to avoid not responding tft call functions
  pinMode(SCtrl::TS_XM,OUTPUT);
  pinMode(SCtrl::TS_YP,OUTPUT);

  //clicked
  if (p.z > 0 && !inClick) {
    Serial.println("clicked");
    inClick = true;
    Serial.println("xps "+String(SCtrl::TS_XP)+" " + String(SCtrl::TS_YP) + " " + String(SCtrl::TS_XM) + " " + String(SCtrl::TS_YM));    
    DPoint uiP;
    int16_t px2 = p.x;
    int16_t py2 = p.y;
    Serial.println("clicked 2");
    uiP.x = map(p.y, SCtrl::TS_MINY, SCtrl::TS_MAXY, SCtrl::tft.width(),0);
    uiP.y = map(px2, SCtrl::TS_MINX, SCtrl::TS_MAXX, SCtrl::tft.height(),0);
    Serial.println("clicked on " + String(px2) + "," + String(py2) + " " +String(uiP.x) + "," + String(uiP.y) + " " + String(inClick));

    //loop troght event receptors array, checking if is point in area of element
    EVRcpt* EVRcptTemp = lastEVRcpt;
    while(EVRcptTemp != nullptr) {
      if (EVRcptTemp->checkClickEvent(uiP) == true) {
        break;//not bubble event
      }
      EVRcptTemp = EVRcptTemp->prev;
    }
    inClick = false;
  }  
  //FREERAM_PRINT; //show free memory
  delay(100); //to preserve resources, disable in production
}
