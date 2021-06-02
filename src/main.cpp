#include <iostream>
#include <thread>
#include "utils/utils.h"
#include "hacks/AutoClicker.h"
#include "utils/keyboard/KeyboardManager.h"
#include "ui/ui.h"

// Next do gui and then copy the fucking velocity from the windows one.

std::mutex clickerMutex;
AutoClicker *clicker;

void runUi() {
	MainUi *ui = new MainUi(clicker, &clickerMutex);
	ui->run();
}

int main() {
	if (!checkDeps())
		return EXIT_FAILURE;

	clicker = new AutoClicker(16, 52);
	clicker->updateValues();
	KeyBoardManager keyManager;
	keyManager.registerClicker(clicker);

  std::thread uiThread(runUi);

	while (true) {
		clickerMutex.lock();
		keyManager.update();
		clicker->update();
		clickerMutex.unlock();
	}

	return 0;
}
