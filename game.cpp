#include <stdlib.h>         // for exit()
// Engine includes
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"

// Game includes
#include "IGetDeleted.h"
#include "EndOfWorlds.h"

int main(int argc, char *argv[]) {
	LogManager &lm = LogManager::getInstance();

	// Start up Game Manager

	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp()) {
		lm.writeLog("Error starting game manager!\n");
		game_manager.shutDown();
		exit(1);
	}

	ResourceManager &rm = ResourceManager::getInstance();

	game_manager.run();

	// Shut everything down
	game_manager.shutDown();
}
