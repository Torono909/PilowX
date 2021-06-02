#ifndef UI_H
#define UI_H

#include "../hacks/AutoClicker.h"
#include <mutex>

class MainUi {
public:
  MainUi(AutoClicker *clicker, std::mutex &clickerMutex);
  void run();
private:
  AutoClicker *clicker;
  std::mutex &clickerMutex;
};

#endif /* end of include guard: UI_H */
