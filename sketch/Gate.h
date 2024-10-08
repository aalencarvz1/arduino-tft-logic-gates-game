#ifndef GATE_H
#define GATE_H

#include "SCtrl.h"
#include "EVRcpt.h"

#define DEFAULT_GATE_SIZE 150.0
#define DEFAULT_GATE_CONNECTOR_COUNT 2
#define DEFAULT_GATE_VERTICAL_DIRECTION true
#define DEFAULT_GATE_LINE_COLOR TFT_WHITE
#define DEFAULT_GATE_LINE_WIDTH 1.0
#define DEFAULT_GATE_ASPECT_RATIO 1.0
#define DEFAULT_GATE_BASE_SIZE_PERC 0.5
#define DEFAULT_GATE_BASE_CURVE_PERC 0.3

#define DEFAULT_GATE_CONNECTOR_MARGIN_PERC 0.1
#define DEFAULT_GATE_CONNECTOR_SIZE_PERC 0.3
#define DEFAULT_GATE_WIDTH DEFAULT_GATE_SIZE * DEFAULT_GATE_ASPECT_RATIO
#define DEFAULT_GATE_CONNECTOR_SIZE DEFAULT_GATE_SIZE * DEFAULT_GATE_CONNECTOR_SIZE_PERC
#define DEFAULT_GATE_CONNECTOR_MARGIN DEFAULT_GATE_WIDTH * DEFAULT_GATE_CONNECTOR_MARGIN_PERC

#define DEFAULT_GATE_MIN_ARC_HEIGHT_PERC 0.2
#define DEFAULT_GATE_BASE_ARC_HEIGHT_ASPECT_RATIO 0.3
#define DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC 0.3
#define DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC 0.6
#define DEFAULT_GATE_NOT_RADIUS_PERC 0.12
#define DEFAULT_GATE_MAX_NOT_RADIUS 8.0
#define DEFAULT_GATE_EXCLUSIVE_SPACE_PERC 0.1

#define DEFAULT_GATE_INPUT_OFF_COLOR TFT_RED
#define DEFAULT_GATE_INPUT_ON_COLOR TFT_GREEN
#define DEFAULT_GATE_INPUT_RADIUS_PERC 0.15
#define DEFAULT_GATE_MIN_INPUT_RADIUS 10.0
#define DEFAULT_GATE_MAX_INPUT_RADIUS 30.0


struct Gate; //forhard

struct GateInput {
  int id;
  double x;
  double y;
  double r;  
  bool on = false;
  EVRcpt* ev = nullptr;
  Gate* gate = nullptr;
  bool visible = true;
  bool clickable = true;
  bool redrawOnChange = true;
  bool recalcOnChange = true;  
  bool isOutput = false;
  
  GateInput(
    int pId,
    double pX = 0,
    double pY = 0,
    double pR = DEFAULT_GATE_MIN_INPUT_RADIUS + ((DEFAULT_GATE_MAX_INPUT_RADIUS - DEFAULT_GATE_MIN_INPUT_RADIUS) / 2),
    bool pOn = false,
    Gate* pGate = nullptr,
    bool pClickable = true
  );
  ~GateInput();
  void initState(bool pInitState = false);
  void setState(bool newState);
  void draw();
};


struct Gate {

  double x;
  double y;
  double size;
  int connectorCount;
  bool vertical;
  int lineColor;
  double lineWidth;
  double aspectRatio;
  double baseSizePerc;
  double connectorSize;
  double width;  
  double connectorMargin;

  double firstConnectorX;
  double firstConnectorY;

  bool hasInputs = false;
  bool hasNot = false;
  double notRadius = 0;

  bool isExclusive = false;

  GateInput** inputs = nullptr;

  bool outputState = false;
  bool visibleOutput = true;


  Gate(
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
  virtual ~Gate();


  void updateWidthDependencies();
  void updateSizeDependencies();
  void updateAspectRatioDependencies();
  void setWidth(double pWidth);
  void setAspectRatio(double pAspectRatio);
  void setSize(double pSize);
  void setConnectorCount(byte pConnectorCount);
  void setHasNot(bool pHasNot = false);
  virtual void setValues(
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

  void freeInputs();

  virtual void drawConnector(int position, double startPos = -1, double pConnectorSize = -1);
  virtual void drawOutputConnector();
  virtual void drawBody(bool drawConnectors = true);      
  virtual void draw(bool drawConnectors = true);
  virtual void drawNot();
  virtual bool calcOutputState();
};

#endif //GATE_H