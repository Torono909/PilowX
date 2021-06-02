#include "AutoClicker.h"

#include <stdlib.h>
#include <iostream>
#include <X11/extensions/XTest.h>
#include <X11/Xlib.h>
#include <unistd.h>

AutoClicker::AutoClicker(float cps, int bind) {
  clickTimer = new MSTimer();
  eventTimer = new MSTimer();
  this->cps = cps;
  this->bind = bind;
  eventDelay = 350;
  nextEventDelay = randFloat(0.8, 1.2) * eventDelay;
  dropChance = 0.3;
  spikeChance = 0.2;
  isSpiking = false;
  isDropping = false;
  isEnabled = true;
}

void AutoClicker::update() {
  if (system("xinput --query-state 12 | grep \"button.9.=up\" > /dev/null") && isEnabled) {
    if (clickTimer->hasTimePassed(nextDelay)) {
      clickTimer->reset();
      pressMouse(nextDelay * 1000 / 2);
      updateValues();
    }
  } else {
    clickTimer->reset();
  }
}

void AutoClicker::updateValues() {
  if (eventTimer->hasTimePassed(nextEventDelay)) {
    float randomFloat = randFloat(0, 1);
    if (randomFloat < spikeChance) {
      isSpiking = true;
      isDropping = false;
    } else if (randomFloat < spikeChance + dropChance) {
      isDropping = true;
      isSpiking = false;
    } else {
      isDropping = false;
      isSpiking = false;
    }
    eventTimer->reset();
    nextEventDelay = eventDelay * randFloat(0.8, 1.2);
  }

  float minCps;
  float maxCps;

  float middleCps = cps;
  if (isSpiking)
    middleCps *= randFloat(1.1, 1.2);
  else if (isDropping)
    middleCps *= randFloat(0.8, 0.9);

  maxCps = middleCps + 2;
  minCps = middleCps - 2;

  nextDelay = ((float) 1000) / randFloat(minCps, maxCps);
}

void AutoClicker::pressMouse(long delay) {
  Display *dpy = XOpenDisplay(0);
  XTestFakeButtonEvent(dpy, 1, True, CurrentTime);
  usleep(delay);
  XTestFakeButtonEvent(dpy, 1, False, CurrentTime);
  XCloseDisplay(dpy);
}

void AutoClicker::onKeyPressed(int key) {
  if (key == bind) {
    isEnabled = !isEnabled;
  }
}

float AutoClicker::getCps() {
  return cps;
}

void AutoClicker::setCps(float cps) {
  this->cps = cps;
}

int AutoClicker::getEventDelay() {
  return eventDelay;
}

void AutoClicker::setEventDealy(int eventDelay) {
  this->eventDelay = eventDelay;
}

float AutoClicker::getSpikeChance() {
  return spikeChance;
}

void AutoClicker::setSpikeChance(float spikeChance) {
  this->spikeChance = spikeChance;
}

float AutoClicker::getDropChance() {
  return dropChance;
}

void AutoClicker::setDropChance(float dropChance) {
  this->dropChance = dropChance;
}
