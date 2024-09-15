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
class EVRcpt {
  public: 
    double x;
    double y;
    double distance;
    void (*staticOnClick)() = nullptr;
    ICallback* onClickCallback = nullptr;  // Ponteiro para o callback

    EVRcpt(
      double pX,
      double pY,
      double pDist,
      void (*pStaticOnClick)() = nullptr,
      ICallback* pOnClickCallback = nullptr
    );  

    //checa se o elemento foi clicado, basedo nos parametros do construtor, sendo um ponto central e um raio
    bool checkClickEvent(DPoint point);
    EVRcpt* prev;
};

void clearAllEVRcpts();

#endif // EVRcpt_H
