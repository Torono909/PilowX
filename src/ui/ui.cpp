#include "ui.h"

#include <ncurses.h>

MainUi::MainUi(AutoClicker *clicker, std::mutex *clickerMutex) {
  this->clicker = clicker;
  this->clickerMutex = clickerMutex;
}

void MainUi::run() {
  initscr();
  cbreak();
  noecho();

  clear();
}
