#include "Gates.h"
#include "Utils.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "XnorGate.h"


static char* Gates::gateNames[] = {"AND", "OR", "NOT", "NAND", "NOR", "XOR", "XNOR"};
static int Gates::gateNamesCount = sizeof(Gates::gateNames) / sizeof(Gates::gateNames[0]);

// Função para encontrar a próxima porta no array
static char* Gates::getNext(const char* gateName) {
    for (int i = 0; i < gateNamesCount; i++) {
        if (strcmp(gateNames[i], gateName) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == gateNamesCount - 1) {
                return gateNames[0];
            } else {
                // Senão, retorna a próxima porta
                return gateNames[i + 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}

static char* Gates::getPrev(const char* gateName) {
    for (int i = gateNamesCount-1; i >= 0; i--) {
        if (strcmp(gateNames[i], gateName) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == 0) {
                return gateNames[gateNamesCount-1];
            } else {
                // Senão, retorna a anterior porta
                return gateNames[i - 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}

static Gate* Gates::createGateByName(
  char* gateName,
  double pX, 
  double pY,
  double pSize,
  int pConnectorCount,	
  bool pVertical,
  int pLineColor,
  double pLineWidth,
  double pAspectRatio,
  double pBaseSizePerc,
  double pConnectorSize,
  double pWidth,
  double pConnectorMargin
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
