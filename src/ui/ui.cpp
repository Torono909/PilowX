#include "ui.h"

#include <ncurses.h>
#include "slider.h"

MainUi::MainUi(AutoClicker *clicker, std::mutex *clickerMutex) {
  this->clicker = clicker;
  this->clickerMutex = clickerMutex;
}

void MainUi::run() {
  initscr();
  cbreak();
  noecho();

  clear();
  Slider *testSlider = new Slider("Test", 0, 5, 3);
  testSlider->render(5, 5, 30);
  refresh();
}
