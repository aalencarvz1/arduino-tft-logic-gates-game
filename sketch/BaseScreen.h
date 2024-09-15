#ifndef BASESCREEN_H
#define BASESCREEN_H

#define DEFAULT_BACKGROUND_COLOR TFT_BLACK

struct BaseScreen {
  void drawBackButton();
  virtual void draw(char* params[] = nullptr);
};

#endif //BASESCREEN_H