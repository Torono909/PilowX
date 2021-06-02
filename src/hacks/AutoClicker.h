#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include "../utils/utils.h"

class AutoClicker {
public:
  AutoClicker(float cps, int bind);
  void update();
  float getCps();
  void setCps(float cps);
  int getEventDelay();
  void setEventDealy(int eventDelay);
  float getDropChance();
  void setDropChance(float dropChance);
  void updateValues();
  float getSpikeChance();
  void setSpikeChance(float spikeChance);
  void onKeyPressed(int key);
private:
  bool isEnabled;
  void pressMouse(long delay);
  MSTimer *clickTimer;
  MSTimer *eventTimer;
  int bind;
  float cps;
  int nextDelay;
  int eventDelay;
  int nextEventDelay;
  float dropChance;
  float spikeChance;
  bool isSpiking;
  bool isDropping;
};

#endif /* end of include guard: AUTOCLICKER_H */
