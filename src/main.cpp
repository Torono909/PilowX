#include <iostream>
#include <thread>
#include "utils/utils.h"
#include "hacks/AutoClicker.h"
#include "utils/keyboard/KeyboardManager.h"

// Next do gui and then copy the fucking velocity from the windows one.

std::mutex clickerMutex;

int main(int argc, char **argv) {
	if (!checkDeps())
		return 1;

	AutoClicker *clicker = new AutoClicker(16, 52);
	clicker->updateValues();
	KeyBoardManager keyManager;
	keyManager.registerClicker(clicker);

	while (true) {
		clickerMutex.lock();
		keyManager.update();
		clicker->update();
		clickerMutex.unlock();
	}

	return 0;
}
