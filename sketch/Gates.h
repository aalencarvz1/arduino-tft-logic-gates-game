#ifndef GATES_H
#define GATES_H

Gate* createGateByName(
  char* gateName,
  double pX                = 150.0, 
  double pY                = 250.0,
  double pSize             = DEFAULT_GATE_SIZE,
  int pConnectorCount      = DEFAULT_GATE_CONNECTOR_COUNT,	
  bool pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
  int pLineColor           = DEFAULT_GATE_LINE_COLOR,
  double pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
  double pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
  double pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
  double pConnectorSize    = DEFAULT_GATE_CONNECTOR_SIZE,
  double pWidth            = DEFAULT_GATE_WIDTH,
  double pConnectorMargin  = DEFAULT_GATE_CONNECTOR_MARGIN
);

#endif //GATES_H