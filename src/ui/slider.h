#ifndef SLIDER_H
#define SLIDER_H

#define SLIDER_HEIGHT 5

class Slider {
public:
  Slider(const char *name, int min, int max, int defaultVal);
  void render(int x, int y, int width);
  int getMin();
  int getMax();
  int getCurrent();
  void setCurrent(int current);
private:
  void drawBox(int x, int y, int width);
  int min, max, current;
  const char *name;
};

#endif /* end of include guard: SLIDER_H */
