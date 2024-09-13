#ifndef UTILS_H
#define UTILS_H

struct DPoint{
  double x,y;
};

struct UIPoint{
  int x,y;
};

struct CircleInfo {
  double x,y,r;
};

double getArcAngle(double corda, double raio);
double getCatetoFromPitagoras(double hip, double cat1);
DPoint calcularP3(double a, double b, double c, DPoint p1, DPoint p2);

#endif // UTILS_H