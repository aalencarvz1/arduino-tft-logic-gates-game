#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

struct DPoint{
  double x,y;
};

struct UIPoint{
  int x,y;
};

struct CircleInfo {
  double x,y,r;
};

String boolToString(bool v);
void toUpperCase(char* str);
void toLowerCase(char* str);
double getArcAngle(double corda, double raio);
double getCatetoFromPitagoras(double hip, double cat1);
DPoint calcularP3(double a, double b, double c, DPoint p1, DPoint p2);

#endif // UTILS_H