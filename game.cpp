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
	rm.loadSprite("sprites/ship-spr.txt", "ship");

	lm.writeLog("Starting the game! Look, a number, %d, and a string %s", 1, "Hello");
	new IGetDeleted(11);
	new IGetDeleted(16);
	new IGetDeleted(25);
	new IGetDeleted(24);
	new IGetDeleted(23);
	new IGetDeleted(33);
	new IGetDeleted(42);
	new IGetDeleted(41);
	new EndOfWorlds(1, 3, 5);
	new EndOfWorlds(-1, 5, 5);
	new IGetDeleted(40); // this guy will die when the game ends

	game_manager.run();

	// Shut everything down
	game_manager.shutDown();
}
