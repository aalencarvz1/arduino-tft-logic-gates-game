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
  if (pR < DEFAULT_GATE_MIN_INPUT_RADIUS) {
    r = DEFAULT_GATE_MIN_INPUT_RADIUS;
  } else if (pR > DEFAULT_GATE_MAX_INPUT_RADIUS) {
    r = DEFAULT_GATE_MAX_INPUT_RADIUS;
  };
  initState(pOn);
};

GateInput::~GateInput() {
  if (ev != nullptr) {
    delete ev;
  }
}

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
  Serial.println("no constructor ");

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
  
  Serial.println("no fim constructor");
};

//destructor;
Gate::~Gate() {
  Serial.println("Gate::~Gate destructor");
  freeInputs();
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

// Método para redimensionar o array
void Gate::setConnectorCount(byte pConnectorCount) {
    // Libera o array antigo, se existir
    freeInputs();

    // Atualiza o tamanho do array
    connectorCount = pConnectorCount;

    // Realoca memória para o novo tamanho
    //inputs = (GateInput*)malloc(sizeof(GateInput) * (connectorCount + 1)); //+1 = last = output connector
     inputs = new GateInput*[connectorCount];

    // Inicializa os novos GateInput no array
    /*for (byte i = 0; i < connectorCount; ++i) {
        inputs[i] = GateInput();  // Inicializa com id e estado falso
    }*/
}


void Gate::drawConnector(int position, double startPos, double pConnectorSize) { 
  Serial.println("Gate::drawConnector "+String(position) + ","+String(startPos) + ","+String(pConnectorSize));
  double connMargin = connectorMargin;
  if (pConnectorSize == -1) {
    pConnectorSize = connectorSize;
  }
  if (position > 0) {            
    connMargin = connMargin + (position * (width - (connMargin * 2)) / (connectorCount - 1));    
  } else if (connectorCount == 1) {
    connMargin = width / 2;
  }
  if (lineWidth > 1) {
    connMargin = connMargin - lineWidth / 2;
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
        setConnectorCount(connectorCount);
      }
      /*if (inputs[position] != nullptr) {
        delete inputs[position];
      }*/
      inputs[position] = new GateInput(
        position,
        x + connMargin,
        startPos+pConnectorSize,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this
      );
      Serial.println("nnnn"+String(position));
      inputs[position]->draw();
      //inputs[position] = input;
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
        setConnectorCount(connectorCount);
      }
      /*if (inputs[position] != nullptr) {
        delete inputs[position];
      }*/
      inputs[position] = new GateInput(
        position,
        startPos-pConnectorSize,
        y + connMargin,
        size * DEFAULT_GATE_INPUT_RADIUS_PERC,
        false,
        this
      );
      Serial.println("nnnn"+position);
      inputs[position]->draw();
      //inputs[position] = input;
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
    if (lineWidth > 1) {
      double pInit = x + (width / 2 ) - (lineWidth / 2);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(pInit+i ,py1,pInit+i,py2 , lineColor);
      }
    } else {
      SCtrl::tft.drawLine(x + (width / 2 ) ,py1,x + (width / 2 ),py2, lineColor);
    }

    if (hasInputs == true) {
      if (inputs == nullptr) {
        setConnectorCount(connectorCount);
      }
      /*if (inputs[connectorCount] != nullptr) {
        delete inputs[connectorCount];
      }*/
      inputs[connectorCount] = new GateInput(
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
    }
  } else {
    double px1 = x + size;
    double px2 = x + size + connectorSize;
    if (hasNot) {
      px1 = px1 + (notRadius * 2);
    }
    if (lineWidth > 1) {
      double pInit = y + (width / 2) - (lineWidth / 2);
      for (int i = 0; i < lineWidth; i++) {
        SCtrl::tft.drawLine(px1 ,pInit + i,px2,pInit + i, lineColor);
      }
    } else {
      SCtrl::tft.drawLine(px1,y + (width/2),px2,y + (width/2), lineColor);
    }

    if (hasInputs == true) {
      if (inputs == nullptr) {
        setConnectorCount(connectorCount);
      }
      /*if (inputs[connectorCount] != nullptr) {
        delete inputs[connectorCount];
      }*/
      inputs[connectorCount] = new GateInput(
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