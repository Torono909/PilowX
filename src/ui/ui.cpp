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

  clickerMutex->lock();

  Slider *cpsSlider = Slider("CPS", 0, 20, (int) clicker->getCps());
  Slider *eventDelaySlider = Slider("Event Delay Time", 0, 3000, clicker->getEventDelay());
  Slider *dropChanceSlider = Slider("Drop Chance", 0, 50, (int) (clicker->getDropChance() * 100.0));
  Slider *spikeChanceSlider = Slider("Spike Chance", 0, 50, (int) (clicker->getSpikeChance() * 100.0));

  clickerMutex->unlock();

  while (true) {
    clear();

    mvaddstr(0, 0, "SomePineaple's MC External Client");

    mvaddstr(3, 0, "AutoClicker");

    refresh();

    int pressed = getch();
  }
}
