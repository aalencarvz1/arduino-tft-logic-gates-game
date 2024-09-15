#ifndef SCTRL_H
#define SCTRL_H

#include <MCUFRIEND_kbv.h>  // Biblioteca MCUFRIEND_kbv
#include <TouchScreen.h>   // Biblioteca para touchscreen
#include "Utils.h"


#define ROSA_CLARO 0xFFB6C1
#define AZUL_CLARO 0xADD8E6
#define VERDE_CLARO 0x90EE90
#define AMARELO_CLARO 0xFFFFE0
#define LILAS_CLARO 0xE6E6FA
#define PESSSEGO_CLARO 0xFFDAB9


//para armazenar informações referente ao dimensionmanto (bounds) de textos em tela
struct TextInfo{
  double x, y;  // Variáveis para armazenar a posição do canto superior esquerdo
  double w, h;  
};

struct SCtrl {

  // Definição dos pinos do touchscreen
  static const int TS_XP  = 8;  // Substitua pelo pino correto
  static const int TS_YP  = A3;//17;//A3;  // Substitua pelo pino correto
  static const int TS_XM  = A2;//16;//A2;  // Substitua pelo pino correto
  static const int TS_YM  = 9;  // Substitua pelo pino correto

  // Definição das variáveis de calibração do touchscreen
  static const int TS_MINX  = 100;
  static const int TS_MAXX  = 920;
  static const int TS_MINY  = 120;
  static const int TS_MAXY  = 920;

  // Configuração do touchscreen
  static TouchScreen ts;

  static MCUFRIEND_kbv tft;

  static void init();

  static TextInfo drawCenteredText(char* text, double y = 0, double centerX = SCtrl::tft.width() * 1.0 / 2.0, double textSize = 2, int color = TFT_WHITE);
  static void drawRoundButton(double x,double y,double r,int color,char* text="", bool hasCenterPlay=true, bool hasBorder=true, double textDistance = 20, void (*onClick)() = nullptr);
  static void drawSmoothArc(double x_center, double y_center, double radius, double start_angle, double end_angle, uint16_t color = TFT_WHITE);
  static CircleInfo drawArcFromArrow(double x1, double y1, double x2, double y2, double arcHeight, int color = TFT_WHITE);
  

};

#endif // SCTRL_H