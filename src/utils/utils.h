#ifndef UTILS_H
#define UTILS_H

#include <string>

struct Dimension {
  int x, y, width, height;
};

long getCurrentTimeMillis();

std::string execCmd(const char *cmd);

int randInt(int min, int max);
float randFloat(float min, float max);
bool checkDeps();

class MSTimer {
public:
  MSTimer();
  ~MSTimer();
  bool hasTimePassed(long time);
  void reset();
private:
  long lastTime;
};

#endif /* end of include guard: UTILS_H */
