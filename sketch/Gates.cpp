#include "Utils.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "XnorGate.h"

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
) {
  Gate* result = nullptr;
  toUpperCase(gateName);
  if (gateName == "AND") {
    result = new AndGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "OR") {
    result = new OrGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NOT") {
    result = new NotGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NAND") {
    result = new NandGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NOR") {
    result = new NorGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "XOR") {
    result = new XorGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "XNOR") {
    result = new XnorGate(pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  }
  return result;
}
