#include <stdlib.h>         // for exit()
// Engine includes
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"

// Game includes
#include "Hero.h"

void loadResources();

int main(int argc, char *argv[]) {
	LogManager &lm = LogManager::getInstance();

	// Start up Game Manager

	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp()) {
		lm.writeLog("Error starting game manager!\n");
		game_manager.shutDown();
		exit(1);
	}

	loadResources();

	Hero hero;

	game_manager.run();

	// Shut everything down
	game_manager.shutDown();
}

void loadResources(){
		// load saucer sprite
		ResourceManager &rm = ResourceManager::getInstance();
		rm.loadSprite("sprites/heror-spr.txt", "hero_r");
		rm.loadSprite("sprites/herod-spr.txt", "hero_d");
		rm.loadSprite("sprites/herol-spr.txt", "hero_l");
		rm.loadSprite("sprites/herou-spr.txt", "hero_u");

		rm.loadSprite("sprites/monster1-spr.txt", "monster1");

		rm.loadSprite("sprites/bullet-spr.txt", "bullet");
		rm.loadSprite("sprites/explosion-spr.txt", "explosion");
		rm.loadSprite("sprites/rapid-spr.txt", "rapid");
		rm.loadSprite("sprites/health-spr.txt", "health");
		rm.loadSprite("sprites/max-spr.txt", "max");
}
