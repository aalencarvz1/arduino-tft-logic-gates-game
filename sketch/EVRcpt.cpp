#include "EVRcpt.h"
#include <Arduino.h>
#include "Utils.h"

EVRcpt* lastEVRcpt = nullptr;
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
  id = currentId;
  currentId++;
  prev = lastEVRcpt;      
  if (prev != nullptr) {    
    prev->next = this;      
  }
  lastEVRcpt = this;
  Serial.println("created event "+String(id));
};

EVRcpt::~EVRcpt(){
  Serial.println("deleting..."+String(id));
  if (next != nullptr) {
    next->prev = prev;
    Serial.println("have next");
  } else {
    lastEVRcpt = prev;
  }
  if (prev != nullptr) {   
    prev->next = next;
    Serial.println("have prev");
  } 

  staticOnClick = nullptr;
  if (onClickCallback != nullptr) {
    delete onClickCallback;
  }
  Serial.println("xxxxxxxxxxxxxxxxxxxxx deleted node"+String(id));
}

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool EVRcpt::checkClickEvent(DPoint point) {
  Serial.println("in checkClickEvent "+String(id)); 
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
      Serial.println("in checkClickEvent6"); 
      return true;
    }
  }
  Serial.println("in checkClickEvent7"); 
  return false;
};

void clearAllEVRcpts(){
  EVRcpt* temp = lastEVRcpt;
  while(lastEVRcpt != nullptr) {
    temp = lastEVRcpt;
    lastEVRcpt = lastEVRcpt->prev;
    delete temp;    
  }
  lastEVRcpt = nullptr;
};