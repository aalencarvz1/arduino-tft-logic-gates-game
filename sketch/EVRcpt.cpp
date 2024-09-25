#include "EVRcpt.h"
#include <Arduino.h>
#include "Utils.h"
#include "DoubleLinkedList.h"

//EVRcpt* lastEVRcpt = nullptr;
DoubleLinkedList<EVRcpt>* event_receipts = nullptr;//new DoubleLinkedList<EVRcpt>();
int currentId = 0;



//constructor
EVRcpt::EVRcpt(
  double pX,
  double pY,
  double pDist,
  void (*pStaticOnClick)(),
  ICallback* pOnClickCallback
) :
  x(pX),
  y(pY),
  distance(pDist),
  staticOnClick(pStaticOnClick),
  onClickCallback(pOnClickCallback)
{
  Serial.println("INIT EVRcpt::EVRcpt");
  id = currentId;
  currentId++;
  /*prev = lastEVRcpt;      
  if (prev != nullptr) {    
    prev->next = this;      
  }
  lastEVRcpt = this;*/
  if (event_receipts == nullptr) {
    FREERAM_PRINT;
    event_receipts = new DoubleLinkedList<EVRcpt>();
  }
  event_receipts->add(this);
  Serial.println("END EVRcpt::EVRcpt");
};

EVRcpt::~EVRcpt(){
  Serial.println("INIT EVRcpt::~EVRcpt");
  /*if (next != nullptr) {
    next->prev = prev;
    Serial.println("have next");
  } else {
    lastEVRcpt = prev;
  }
  if (prev != nullptr) {   
    prev->next = next;
    Serial.println("have prev");
  } */

  //staticOnClick = nullptr;
  if (onClickCallback != nullptr) {
    delete onClickCallback;//?????
  }
  Serial.println("END EVRcpt::~EVRcpt");
}

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool EVRcpt::checkClickEvent(DPoint point) {
  Serial.println("INIT EVRcpt::checkClickEvent");
  if (enabled) {  
    if (abs(x - point.x) <= distance && abs(y - point.y) <= distance) {
      Serial.println("in checkClickEvent1"); 
      if (onClickCallback != nullptr) {
        Serial.println("in checkClickEvent2"); 
        onClickCallback->call();  // Chama a função encapsulada
        Serial.println("in checkClickEvent3"); 
      } else if (staticOnClick != nullptr) {
        Serial.println("in checkClickEvent4"); 
        staticOnClick();
        Serial.println("in checkClickEvent5"); 
      }
      Serial.println("END EVRcpt::checkClickEvent");
      return true;
    }
  }
  Serial.println("END EVRcpt::checkClickEvent");
  return false;
};

void clearAllEVRcpts(){
  Serial.println("INIT clearAllEVRcpts");
  /*EVRcpt* temp = lastEVRcpt;
  while(lastEVRcpt != nullptr) {
    temp = lastEVRcpt;
    lastEVRcpt = lastEVRcpt->prev;
    delete temp;    
  }
  lastEVRcpt = nullptr;*/
  if (event_receipts != nullptr) {
    event_receipts->clear();
  }
  Serial.println("END clearAllEVRcpts");
};