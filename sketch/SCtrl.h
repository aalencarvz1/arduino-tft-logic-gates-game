#ifndef SCTRL_H
#define SCTRL_H

#include <MCUFRIEND_kbv.h>  // Biblioteca MCUFRIEND_kbv
#include "Utils.h"

struct SCtrl {

  static MCUFRIEND_kbv tft;

  static void init();

  static void drawSmoothArc(double x_center, double y_center, double radius, double start_angle, double end_angle, uint16_t color = TFT_WHITE);
  static CircleInfo drawArcFromArrow(double x1, double y1, double x2, double y2, double arcHeight, int color = TFT_WHITE);
  

};

#endif // SCTRL_H