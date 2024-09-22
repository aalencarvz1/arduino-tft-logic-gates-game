#include "GatesCircuit.h"
#include "Gates.h"



GatesCircuit::GatesCircuit(
  double pContainerX,
  double pContainerY,
  double pContainerWidth,
  double pContainerHeight)
  : containerX(pContainerX),
    containerY(pContainerY),
    containerWidth(pContainerWidth),
    containerHeight(pContainerHeight) {
  gates = new DoublyLinkedList();
};

GatesCircuit::~GatesCircuit() {
  delete gates;
  delete topGate;
};

Gate* GatesCircuit::createGate(
  char* gateName,
  GateInput* outputInput,
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
  double pConnectorMargin) {

  int currentCircuitLevel = 0;
  //adjust creation gate values
  if (gateName == nullptr) {
    gateName = Gates::gateNames[0];
  };
  Gate* outputGate = nullptr;

  if (outputInput == nullptr) {
    //find next input without outputGate
    Node* current = gates->head;
    while (current != nullptr) {
      outputGate = current->data;
      Serial.println("passing port in " + String(outputGate->x) + " " + String(outputGate->y));
      for (size_t i = 0; i < outputGate->connectorCount; i++) {
        if (outputGate->inputs[i]->outputGate == nullptr) {
          outputInput = outputGate->inputs[i];
          break;
        }
      };
      if (outputInput != nullptr) break;
      current = current->next;
    }
  } else {
    outputGate = outputInput->gate;
  }

  if (outputGate != nullptr) {
    currentCircuitLevel = outputGate->currentCircuitLevel + 1;
  }

  if (pSize == DEFAULT_GATE_SIZE) {
    if (vertical) {
      pSize = (containerHeight / gateLevelCount) * gateVerticalSizePerc;
    } else {
      pSize = (containerWidth / gateLevelCount) * gateHorizontalSizePerc;
    }
  }
  if (pWidth == DEFAULT_GATE_WIDTH) {
    pWidth = pSize * (vertical ? DEFAULT_GATE_ASPECT_RATIO : gateHorizontalAspectRatio);
  }
  if (pConnectorSize == DEFAULT_GATE_CONNECTOR_SIZE) {
    pConnectorSize = pSize * DEFAULT_GATE_CONNECTOR_SIZE_PERC;
  }
  if (pConnectorMargin == DEFAULT_GATE_CONNECTOR_MARGIN) {
    pConnectorMargin = pWidth * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;
  }
  double lastLevelWidth = (pow(2,gateLevelCount - 1) * pWidth) + ((pow(2,gateLevelCount - 1) - 1) * (pWidth * (vertical ? gateSpacingPerc : gateVerticalSpacingPerc)));
  double currentGateSapce = lastLevelWidth / pow(2,currentCircuitLevel);

  //double gateSpacing = (pWidth * (vertical ? gateSpacingPerc : gateVerticalSpacingPerc)) / currentCircuitLevel;
  if (pX == -1) {
    if (topGate == nullptr) {
      if (vertical) {
        pX = containerX + containerWidth / 2 - pWidth / 2;
      } else {
        pX = containerX + containerWidth - pSize - pConnectorSize * 2 -10;
      }
    } else {      
      if (vertical) {
        double levelGateWidth = outputGate->connectorCount * currentGateSapce;//pWidth + ((outputGate->connectorCount - 1) * gateSpacing);
        double x1 = outputGate->x + outputGate->width / 2 - levelGateWidth / 2;
        x1 = x1 + currentGateSapce / 2 - pWidth / 2;
        pX = x1 + outputInput->id * currentGateSapce;//(pWidth + gateSpacing); 
      } else {
        pX = outputInput->x - (pSize + outputGate->size * gateHorizontalLevelSpacingPerc) - pConnectorSize;
      }
    }
  }
  if (pY == -1) {
    if (topGate == nullptr) {
      if (vertical) {
        pY = containerY + pSize;
      } else {
        pY = containerY + containerHeight / 2 - pWidth / 2;
      }
    } else {
      if (vertical) {
        pY = outputGate->y + pSize + outputGate->size * gateLevelSpacingPerc;  //@todo implement detect current input wich is connectec output this gate to calculate x, implement on set inputoutpu, set also gateoutput on inpu
      } else {
        /*double levelGateWidth = outputGate->connectorCount * pWidth + ((outputGate->connectorCount - 1) * gateSpacing);
        double y1 = outputGate->y + outputGate->width / 2 - levelGateWidth / 2;
        pY = y1 + outputInput->id * (pWidth + gateSpacing); */


        double levelGateWidth = outputGate->connectorCount * currentGateSapce;//pWidth + ((outputGate->connectorCount - 1) * gateSpacing);
        double y1 = outputGate->y + outputGate->width / 2 - levelGateWidth / 2;
        y1 = y1 + currentGateSapce / 2 - pWidth / 2;
        pY = y1 + outputInput->id * currentGateSapce;//(pWidth + gateSpacing); 
      }
    }
  }
  lastCreatedGate = Gates::createGateByName(
    gateName,
    pX,
    pY,
    pSize,
    pConnectorCount,
    vertical,//pVertical,
    pLineColor,
    pLineWidth,
    pAspectRatio,
    pBaseSizePerc,
    pConnectorSize,
    pWidth,
    pConnectorMargin);
  if (vertical) {
    lastCreatedGate->y = lastCreatedGate->y + lastCreatedGate->connectorSize * 2;  //adjust top position, if vertical
  } else {
    //do implement
  }
  lastCreatedGate->setHasInputs(hasInputs,intermediaryInputsVisible);
  lastCreatedGate->visibleOutput = intermediaryOutputsVisible;
  lastCreatedGate->currentCircuitLevel = currentCircuitLevel;
  if (topGate == nullptr) {
    topGate = lastCreatedGate;                
    lastCreatedGate->visibleOutput = topOutputVisible;        
  } else {
    lastCreatedGate->visibleOutput = intermediaryOutputsVisible;
  };
  if (lastCreatedGate->currentCircuitLevel == gateLevelCount-1) {
    lastCreatedGate->setIsVisibleInputs(true);
  } else {
    lastCreatedGate->setIsVisibleInputs(intermediaryInputsVisible);
  }
  if (outputInput != nullptr) {
    lastCreatedGate->addOutputInput(outputInput);
  };
  gates->add(lastCreatedGate);
  return lastCreatedGate;
};

void GatesCircuit::draw() {
  if (gates != nullptr) {
    Node* current = gates->head;
    Gate* gate = nullptr;
    while (current != nullptr) {
      gate = current->data;
      gate->draw();
      current = current->next;
    }
  }
}

void GatesCircuit::setVertical(bool pNewVertical){
  vertical = pNewVertical;
  if (gateSpacingPerc == DEFAULT_GATE_SPACING_PERC || gateSpacingPerc == DEFAULT_GATE_VERTICAL_SPACING_PERC) {
    if (vertical == true) {
      gateSpacingPerc = DEFAULT_GATE_SPACING_PERC;
    } else {
      gateSpacingPerc = DEFAULT_GATE_VERTICAL_SPACING_PERC;
    }
  }
}