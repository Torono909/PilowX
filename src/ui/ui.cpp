#include "ui.h"

MainUi::MainUi(AutoClicker *clicker, std::mutex &clickerMutex) {
  this->clicker = clicker;
  this->clickerMutex = clickerMutex;
}
