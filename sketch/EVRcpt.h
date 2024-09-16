#ifndef EVRcpt_H
#define EVRcpt_H

#include "Utils.h"
#include "BaseScreen.h"



class ICallback {
  public:
    virtual void call() = 0; // Função virtual pura
};

template<typename T>
class LambdaCallback : public ICallback {
  public: 
    T lambda;

    LambdaCallback(T lambda) : lambda(lambda) {}

    void call() override {
      lambda(); // Executa a lambda capturada
    }
};


class EVRcpt;//forward declaration
extern EVRcpt* lastEVRcpt;

//para instanciar elementos desenhados em tela que precisam receber eventos de toque (clique)
struct EVRcpt {
  //public: 
  int id = -1;
  double x;
  double y;
  double distance;
  bool enabled = true;
  void (*staticOnClick)() = nullptr;
  ICallback* onClickCallback = nullptr;  // Ponteiro para o callback

  EVRcpt(
    double pX,
    double pY,
    double pDist,
    void (*pStaticOnClick)() = nullptr,
    ICallback* pOnClickCallback = nullptr
  );  

  ~EVRcpt();

  //checa se o elemento foi clicado, basedo nos parametros do construtor, sendo um ponto central e um raio
  bool checkClickEvent(DPoint point);
  EVRcpt* prev = nullptr;
  EVRcpt* next = nullptr;
};

void clearAllEVRcpts();

#endif // EVRcpt_H
