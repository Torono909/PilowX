#include "utils.h"

#include <chrono>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <memory>

long getCurrentTimeMillis() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string execCmd(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

bool doesFileExist(const char *path) {
  FILE *file;
  if ((file = fopen(path, "r"))) {
    fclose(file);
    return true;
  }
  return true;
}

bool checkDeps() {
  const char *WAYLAND_DISPLAY = getenv("WAYLAND_DISPLAY");
  if (WAYLAND_DISPLAY != NULL) {
    printf("Only works with X11, you appear to be using wayland");
    return false;
  }

  if (!doesFileExist("/usr/bin/xinput")) {
    printf("You need to install xinput to use this client");
    return false;
  }

  return true;
}

int randInt(int min, int max) {
  if (min > max) {
    throw "Failed to generate random int, min is greater than max";
  }
  return min + (rand() % max - min);
}

float randFloat(float min, float max) {
  if (min > max) {
    throw "Failed to generate a random float, min is more than max";
  }
  float diff = (float) rand() / (float) RAND_MAX;
  return min + (diff * (max - min));
}

MSTimer::MSTimer() {
  lastTime = getCurrentTimeMillis();
}

bool MSTimer::hasTimePassed(long time) {
  return getCurrentTimeMillis() - lastTime > time;
}

void MSTimer::reset() {
  lastTime = getCurrentTimeMillis();
}
