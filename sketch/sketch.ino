#include "SCtrl.h"
#include "AndGate.h"
#include "OrGate.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SCtrl::init(); 
  SCtrl::tft.fillScreen(TFT_BLACK);
  
  AndGate* ga = new AndGate(10); 
  //g->vertical = false;  
  //g->setAspectRatio(1.25);
  //g->setSize(50);
  //g->lineWidth = 6.0;
  ga->draw();
  delete ga;
  ga = nullptr;

  OrGate* g = new OrGate(250); 
  //g->vertical = false;
  //g->y = 50;
  //g->setAspectRatio(1.25);
  //g->setSize(50);
  //g->lineWidth = 6.0;
  g->draw();
  delete g;
  g = nullptr;

  

  //SCtrl::drawArcFromArrow(150,150,200,100,50,TFT_BLUE);
}

void loop() {
  // put your main code here, to run repeatedly:
}
