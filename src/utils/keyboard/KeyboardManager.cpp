#include "KeyboardManager.h"

#include "../utils.h"

void KeyBoardManager::update() {
  std::string result = execCmd("xinput --query-state 8");

  for (int i = 0; i < NUM_KEYS; i++) {
    std::string key = "key[";
    key += std::to_string(i);
    key += "]=down";
    if (result.find(key) != std::string::npos) {
      if (!lastKeys[i]) {
        clicker->onKeyPressed(i);
      }
      lastKeys[i] = true;
    } else {
      lastKeys[i] = false;
    }
  }
}

void KeyBoardManager::registerClicker(AutoClicker *autoClicker) {
  clicker = autoClicker;
}
