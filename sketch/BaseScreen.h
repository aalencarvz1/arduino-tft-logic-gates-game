#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "SCtrl.h"

#define DEFAULT_BACKGROUND_COLOR TFT_BLACK
#define DEFAULT_WINDOW_BORDER_COLOR TFT_WHITE
#define DEFAULT_WINDOW_TITLE_TEXT_SIZE 2
#define DEFAULT_WINDOW_MARGIN 5
#define DEFAULT_TEXT_COLOR TFT_WHITE

struct BaseScreen {
  char* title = nullptr;
  bool hasBack = true;
  TextInfo titleInfo;
  double containerX = 0;
  double containerY = 0;
  double containerWidth = 0;
  double containerHeight = 0;
  BaseScreen(char* pTitle = nullptr, bool pHasBack = true);
  void drawBackButton();
  virtual void draw(char* params[] = nullptr);
};

#endif //BASESCREEN_H