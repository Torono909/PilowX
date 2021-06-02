#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <vector>
#include <mutex>
#include "../../hacks/AutoClicker.h"

#define NUM_KEYS 248

class KeyBoardManager {
public:
  void update();
  void registerClicker(AutoClicker *autoClicker);
private:
  bool lastKeys[NUM_KEYS];
  AutoClicker *clicker;
};

#endif /* end of include guard: KEYBOARDMANAGER_H */
