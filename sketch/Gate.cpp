#include "Gate.h"

GateInput::GateInput(
  int pId,
  double pX,
  double pY,
  double pR,
  bool pOn,
  Gate* pGate,
  bool pClickable
) :
  id(pId),
  x(pX),
  y(pY),
  r(pR),
  on(pOn),
  gate(pGate),
  clickable(pClickable)
{
  Serial.println("INIT GateInput::GateInput 1");
  if (pR < DEFAULT_GATE_MIN_INPUT_RADIUS) {
    r = DEFAULT_GATE_MIN_INPUT_RADIUS;
  } else if (pR > DEFAULT_GATE_MAX_INPUT_RADIUS) {
    r = DEFAULT_GATE_MAX_INPUT_RADIUS;
  };
  initState(pOn);
  Serial.println("END GateInput::GateInput 1");
};

GateInput::GateInput(
  int pId,
  Gate* pGate,
  bool pOn,  
  bool pClickable
) :
  id(pId),
  gate(pGate),
  on(pOn),  
  clickable(pClickable)
{
  Serial.println("INIT GateInput::GateInput 2");
  Serial.println("END GateInput::GateInput 2");
};


GateInput::~GateInput() {
  if (ev != nullptr) {
    delete ev;
  }  
}

void GateInput::setValues(
  int pId,
  double pX,
  double pY,
  double pR,
  bool pOn,
  Gate* pGate,
  bool pClickable
) {
  Serial.println("INIT GateInput::setValues "+String(pId));
  id = pId;
  x = pX;
  y = pY;
  r = pR;
  on = pOn;
  gate = pGate;
  clickable = pClickable;
  if (pR < DEFAULT_GATE_MIN_INPUT_RADIUS) {
    r = DEFAULT_GATE_MIN_INPUT_RADIUS;
  } else if (pR > DEFAULT_GATE_MAX_INPUT_RADIUS) {
    r = DEFAULT_GATE_MAX_INPUT_RADIUS;
  };
  initState(pOn);
  Serial.println("END GateInput::setValues");
};

void GateInput::initState(bool pInitState) {
  this->on = pInitState;
  if (clickable) {
    if (ev != nullptr) {
      delete ev;
      ev = nullptr;
    }
    ev = new EVRcpt(x,y,r);
    auto f = [&](){
      this->setState(!this->on);
    };
    if (ev->onClickCallback != nullptr) {
      delete ev->onClickCallback;
      ev->onClickCallback = nullptr;
    }
    ev->onClickCallback = new LambdaCallback<decltype(f)>(f);  
  }  
}

void GateInput::setState(bool newState) {
  Serial.println("setting state of " +String(id) + " to " + boolToString(newState));
  on = newState;  
  if (redrawOnChange) draw();
  if (recalcOnChange) gate->calcOutputState();
  if (redrawOnChange && gate->visibleOutput) gate->inputs[gate->connectorCount]->draw();
}

void GateInput::setOutputGate(Gate* pGate) {
  outputGate = pGate;
}

void GateInput::draw() {
  if (visible) SCtrl::drawRoundButton(x,y,r,(on == true) ? DEFAULT_GATE_INPUT_ON_COLOR : DEFAULT_GATE_INPUT_OFF_COLOR,nullptr,false,false,0);  
};



Gate::Gate(
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
) :
  x(pX),
  y(pY),
  size(pSize),  
  connectorCount(pConnectorCount),
  vertical(pVertical),
  lineColor(pLineColor),
  lineWidth(pLineWidth),
  aspectRatio(pAspectRatio),
  baseSizePerc(pBaseSizePerc),
  connectorSize(pConnectorSize),    
  width(pWidth),
  connectorMargin(pConnectorMargin)  
{
  Serial.println("INIT Gate::Gate");

  /*implementar metodos seters, mas manter as propriedades publicas caso o usuario queira manipulalas manualemnte, 
  nos metodos setters, deverão ser feitas essas mesmas tratativas aqui do constructor*/
  
  if (pSize != DEFAULT_GATE_SIZE) {
    if (pWidth == DEFAULT_GATE_WIDTH) {
      width = pSize * pAspectRatio;
      connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;      
      notRadius = (width + pSize) / 2 * DEFAULT_GATE_NOT_RADIUS_PERC;
      if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
        notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
      }
    } 
    if (pConnectorSize == DEFAULT_GATE_CONNECTOR_SIZE) {
      connectorSize = width * DEFAULT_GATE_CONNECTOR_SIZE_PERC;      
    }
  }
  if (pAspectRatio != DEFAULT_GATE_ASPECT_RATIO) {
    /*if (pBaseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {
      baseSizePerc = pSize * DEFAULT_GATE_BASE_SIZE_PERC;
    }*/
    if (pWidth == DEFAULT_GATE_WIDTH) {      
      width = pSize * pAspectRatio;
      connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;
      notRadius = (width + pSize) / 2 * DEFAULT_GATE_NOT_RADIUS_PERC;
      if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
        notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
      }
    }
  }
  
  if (hasInputs) {
    initInputs();
  }

  Serial.println("END Gate::Gate");
};

//destructor;
Gate::~Gate() {
  Serial.println("Gate::~Gate destructor");
  freeInputs();
  if (outputsInputs != nullptr) {
    delete outputsInputs;
  } 
};

void Gate::updateWidthDependencies(){
  connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;
}

void Gate::updateSizeDependencies(){
  setWidth(size * aspectRatio);
  connectorSize = size * DEFAULT_GATE_CONNECTOR_SIZE_PERC;
}

void Gate::updateAspectRatioDependencies(){
  setWidth(size * aspectRatio);
}

void Gate::setWidth(double pWidth) {
  width = pWidth;
  updateWidthDependencies();
}
void Gate::setAspectRatio(double pAspectRatio) {
  aspectRatio = pAspectRatio;
  updateAspectRatioDependencies();
}

void Gate::setSize(double pSize) {
  size = pSize;
  updateSizeDependencies();
}

void Gate::setHasInputs(bool pHasInputs, bool visible) {
  hasInputs = pHasInputs;
  if (hasInputs) {
    initInputs(visible);
  } else {
    freeInputs();
  }
}


void Gate::setValues(
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
  Serial.println("no constructor ");

  this->x = pX;
  this->y = pY;
  this->size = pSize;
  this->connectorCount = pConnectorCount;
  this->vertical = pVertical;
  this->lineColor = pLineColor;
  this->lineWidth = pLineWidth;
  this->aspectRatio = pAspectRatio;
  this->baseSizePerc = pBaseSizePerc;
  this->connectorSize = pConnectorSize;
  this->width = pWidth;
  this->connectorMargin = pConnectorMargin;

  /*implementar metodos seters, mas manter as propriedades publicas caso o usuario queira manipulalas manualemnte, 
  nos metodos setters, deverão ser feitas essas mesmas tratativas aqui do constructor*/
  
  if (pSize != DEFAULT_GATE_SIZE) {
    if (pWidth == DEFAULT_GATE_WIDTH) {
      width = pSize * pAspectRatio;
      connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;      
    } 
    if (pConnectorSize == DEFAULT_GATE_CONNECTOR_SIZE) {
      connectorSize = width * DEFAULT_GATE_CONNECTOR_SIZE_PERC;      
    }
  }
  if (pAspectRatio != DEFAULT_GATE_ASPECT_RATIO) {
    /*if (pBaseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {
      baseSizePerc = pSize * DEFAULT_GATE_BASE_SIZE_PERC;
    }*/
    if (pWidth == DEFAULT_GATE_WIDTH) {      
      width = pSize * pAspectRatio;
      connectorMargin = width * DEFAULT_GATE_CONNECTOR_MARGIN_PERC;
    }
  }
  Serial.println("no fim constructor");
};

void Gate::setHasNot(bool pHasNot) {
  hasNot = pHasNot;
  if (hasNot) {
    notRadius = ((size + size * aspectRatio) / 2) * DEFAULT_GATE_NOT_RADIUS_PERC;
    if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
      notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
    }
  }
}

void Gate::freeInputs(){
  if (inputs != nullptr) {
    for (size_t i = 0; i < connectorCount; i++) {
      delete inputs[i];  // Desaloca cada objeto GateInput
      inputs[i] = nullptr;
    }
    delete[] inputs; 
    inputs = nullptr;
  }
};

void Gate::initInputs(bool visible){
  Serial.println("INIT Gate::initInputs");
  if (hasInputs) {
    freeInputs();
    inputs = new GateInput*[connectorCount+1]; //+1 for output
    for(int i = 0; i <= connectorCount; i++) {
      inputs[i] = new GateInput(i,this);
      inputs[i]->visible = visible;
    }
  }
  Serial.println("END Gate::initInputs");
}

// Método para redimensionar o array
void Gate::setConnectorCount(byte pConnectorCount) {
    // Libera o array antigo, se existir
    freeInputs();

    // Atualiza o tamanho do array
    connectorCount = pConnectorCount;
    
    initInputs();
}

double Gate::getConnectorMargin(int position) {
  double connMargin = connectorMargin;
  if (position > 0) {            
    connMargin = connMargin + (position * (width - (connMargin * 2)) / (connectorCount - 1));    
  } else if (connectorCount == 1) {
    connMargin = width / 2;
  }
  if (lineWidth > 1) {
    connMargin = connMargin - lineWidth / 2;
  }  
  return connMargin;
}

void Gate::drawConnector(int position, double startPos, double pConnectorSize) { 
  Serial.println("Gate::drawConnector "+String(position) + ","+String(startPos) + ","+String(pConnectorSize));
  double connMargin = getConnectorMargin(position);
  if (pConnectorSize == -1) {
    pConnectorSize = connectorSize;
  }

  if (vertical) {
    if (startPos == -1) {
      startPos = y;
    }
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(x + connMargin+i,startPos,x + connMargin+i,startPos + pConnectorSize, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + connMargin,startPos,x + connMargin,startPos + pConnectorSize, lineColor);
    }
    if (hasInputs == true) {
      if (inputs == nullptr) {
        initInputs();
      }
      inputs[position]->setValues(
        position,
        x + connMargin,
        startPos+pConnectorSize,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this
      );
      inputs[position]->draw();      
    }

  } else {
    if (startPos == -1) {
      startPos = x;
    }
    if (lineWidth > 1) {
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(startPos, y + connMargin + i,startPos - pConnectorSize,y + connMargin+i, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(startPos, y + connMargin,startPos - pConnectorSize,y + connMargin, lineColor);
    }
    
    if (hasInputs == true) {
      if (inputs == nullptr) {
        initInputs();
      }
      inputs[position]->setValues(
        position,
        startPos-pConnectorSize,
        y + connMargin,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this
      );
      inputs[position]->draw();
    }
  }
};

void Gate::drawOutputConnector() {   
  if (vertical) {
    double py1 = y - size - connectorSize;
    double py2 = y - size;
    if (hasNot) {
      py2 = py2 - (notRadius * 2);
    }

    //draw output connector line
    if (lineWidth > 1) {
      double pInit = x + (width / 2 ) - (lineWidth / 2);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(pInit+i ,py1,pInit+i,py2 , lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + (width / 2 ) ,py1,x + (width / 2 ),py2, lineColor);
    }

    if (hasInputs == true) {

      //draw output button
      if (inputs == nullptr) {
        initInputs();
      }
      inputs[connectorCount]->setValues(
        connectorCount,
        x + (width / 2 ),
        y - size - connectorSize,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this,
        false 
      );
      inputs[connectorCount]->isOutput = true;
      inputs[connectorCount]->visible = visibleOutput;
      calcOutputState();
      inputs[connectorCount]->draw();

      //draw connector between this output and output input gate
      if (outputsInputs != nullptr) {
        Node* current = outputsInputs->head;
        GateInput* gInput = nullptr;
        double x1 = inputs[connectorCount]->x;
        double y1 = inputs[connectorCount]->y;
        double x2 = 0;
        double y2 = 0;
        while(current != nullptr) {
          gInput = static_cast<GateInput*>(current->data);
          x2 = x1;
          y2 = y1 - ((y1 - gInput->y) / 2);
          SCtrl::tft.drawLine(
            x1,
            y1,
            x2,
            y2,
            lineColor
          );
          SCtrl::tft.drawLine(
            gInput->x,
            gInput->y,
            gInput->x,
            gInput->y + ((y1 - gInput->y) / 2),
            lineColor
          );
          SCtrl::tft.drawLine(
            x1,
            y2,
            gInput->x,
            gInput->y + ((y1 - gInput->y) / 2),
            lineColor
          );
          current = current->next;
        }
      }

    }
  } else {
    double px1 = x + size;
    double px2 = x + size + connectorSize;
    if (hasNot) {
      px1 = px1 + (notRadius * 2);
    }

    //draw output connector line
    if (lineWidth > 1) {
      double pInit = y + (width / 2) - (lineWidth / 2);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(px1 ,pInit + i,px2,pInit + i, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(px1,y + (width/2),px2,y + (width/2), lineColor);
    }

    if (hasInputs == true) {

      //draw output input button
      if (inputs == nullptr) {
        initInputs();
      }
      inputs[connectorCount]->setValues(
        connectorCount,
        x + size + connectorSize,
        y + width / 2,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this,
        false 
      );
      inputs[connectorCount]->isOutput = true;
      inputs[connectorCount]->visible = visibleOutput;
      calcOutputState();
      inputs[connectorCount]->draw();

      //draw connector between this output and output input gate
      if (outputsInputs != nullptr) {
        Node* current = outputsInputs->head;
        GateInput* gInput = nullptr;
        double x1 = inputs[connectorCount]->x;
        double y1 = inputs[connectorCount]->y;
        double x2 = 0;
        double y2 = 0;
        while(current != nullptr) {
          gInput = static_cast<GateInput*>(current->data);
          x2 = x1 + ((gInput->x - x1) / 2);
          y2 = y1; //y1 - ((y1 - gInput->y) / 2);
          SCtrl::tft.drawLine(
            x1,
            y1,
            x2,
            y2,
            lineColor
          );
          SCtrl::tft.drawLine(
            gInput->x,
            gInput->y,
            gInput->x - ((gInput->x - x1) / 2),
            gInput->y, //+ ((y1 - gInput->y) / 2),
            lineColor
          );
          SCtrl::tft.drawLine(
            x2,
            y2,
            gInput->x - ((gInput->x - x1) / 2),
            gInput->y, //+ ((y1 - gInput->y) / 2),
            lineColor
          );
          current = current->next;
        }
      }
    }
  }
};

void Gate::drawBody(bool drawConnectors) {
  //to override
}

void Gate::drawNot(){
  if (hasNot) {
    double cx = x+width/2;
    double cy = y-size-notRadius;
    if (!vertical) {
      cx = x+size+notRadius;
      cy = y+width/2;
    }
    SCtrl::tft.drawCircle(cx,cy,notRadius,lineColor);
  }
}

void Gate::draw(bool drawConnectors) {
  Serial.println("connectors " + connectorCount);
  if (drawConnectors == true) {
    for(int i = 0; i < connectorCount; i++) {
      drawConnector(i);
    }
    drawOutputConnector();
  }
  drawBody(drawConnectors);
  drawNot();
};

bool Gate::calcOutputState(){
  //to override
  return outputState;
};

void Gate::afterCalcOutputState() {
  if (outputsInputs != nullptr) {
    Node* current = outputsInputs->head;
    GateInput* gInput = nullptr;
    while(current != nullptr) {
      gInput = static_cast<GateInput*>(current->data);
      gInput->setState(outputState);
      current = current->next;
    }
  }
}

void Gate::addOutputInput(GateInput* pGateInput) {
  if (outputsInputs == nullptr) {
    outputsInputs = new DoublyLinkedList();
  }
  pGateInput->setState(outputState);
  outputsInputs->add(pGateInput);
  pGateInput->setOutputGate(this);
}

void Gate::setIsVisibleInputs(bool pIsVisibleInputs){
  isVisibleInputs = pIsVisibleInputs;
  if (hasInputs && inputs != nullptr) {
    for (size_t i = 0; i < connectorCount; i++) {
      inputs[i]->visible = isVisibleInputs;
    }
  }
}

