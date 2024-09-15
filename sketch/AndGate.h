#ifndef ANDGATE_H
#define ANDGATE_H

#include "Gate.h"

struct AndGate : public Gate {
  using Gate::Gate;
  void drawBody(bool drawConnectors = true) override;
  bool calcOutputState() override;
};

#endif //ANDGATE_H
