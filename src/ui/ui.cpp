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
  keypad(stdscr, true);

  clickerMutex->lock();

  Slider *cpsSlider = new Slider("CPS", 0, 20, (int) clicker->getCps());
  Slider *eventDelaySlider = new Slider("Event Delay Time", 0, 3000, clicker->getEventDelay());
  Slider *dropChanceSlider = new Slider("Drop Chance", 0, 50, (int) (clicker->getDropChance() * 100.0));
  Slider *spikeChanceSlider = new Slider("Spike Chance", 0, 50, (int) (clicker->getSpikeChance() * 100.0));

  clickerMutex->unlock();

  int selectedOption = 0;
  int numOptions = 4;

  while (true) {
    clear();

    mvaddstr(0, 0, "SomePineaple's MC External Client");

    mvaddstr(3, 0, "AutoClicker");

    cpsSlider->render(2, 5, COLS - 6);
    eventDelaySlider->render(2, 10, COLS - 6);
    dropChanceSlider->render(2, 15, COLS - 6);
    spikeChanceSlider->render(2, 20, COLS - 6);

    mvaddch(5 + (5 * selectedOption), 1, '-');

    refresh();

    int pressed = getch();

    switch (pressed) {
      case KEY_UP:
        selectedOption--;
        if (selectedOption < 0)
          selectedOption = numOptions - 1;
        break;
      case KEY_DOWN:
        selectedOption++;
        if (!(selectedOption < numOptions))
          selectedOption = 0;
        break;
      case KEY_RIGHT:
        clickerMutex->lock();
        switch (selectedOption) {
          case 0:
            clicker->setCps(clicker->getCps() + 1);
            cpsSlider->setCurrent((int) clicker->getCps());
            break;
          case 1:
            clicker->setEventDelay(clicker->getEventDelay() + 50);
            eventDelaySlider->setCurrent(clicker->getEventDelay());
            break;
          case 2:
            clicker->setDropChance(clicker->getDropChance() + 0.01);
            dropChanceSlider->setCurrent((int) (clicker->getDropChance() * 100.0));
            break;
          case 3:
            clicker->setSpikeChance(clicker->getSpikeChance() + 0.01);
            spikeChanceSlider->setCurrent(clicker->getSpikeChance() * 100.0);
            break;
          default:
            break;
        }
        clickerMutex->unlock();
        break;
      case KEY_LEFT:
        clickerMutex->lock();
        switch (selectedOption) {
          case 0:
            clicker->setCps(clicker->getCps() - 1);
            cpsSlider->setCurrent((int) clicker->getCps());
            break;
          case 1:
            clicker->setEventDelay(clicker->getEventDelay() - 50);
            eventDelaySlider->setCurrent(clicker->getEventDelay());
            break;
          case 2:
            clicker->setDropChance(clicker->getDropChance() - 0.01);
            dropChanceSlider->setCurrent((int) (clicker->getDropChance() * 100.0));
            break;
          case 3:
            clicker->setSpikeChance(clicker->getSpikeChance() - 0.01);
            spikeChanceSlider->setCurrent(clicker->getSpikeChance() * 100.0);
            break;
          default:
            break;
        }
        clickerMutex->unlock();
        break;
      default:
        break;
    }
  }
}
