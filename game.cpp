#include <stdlib.h>         // for exit()
// Engine includes
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

#include "LevelManager.h"
#include "GameStart.h"

void loadResources();

int main(int argc, char *argv[]) {
	LogManager &log_manager = LogManager::getInstance();
	LevelManager &level_manager = LevelManager::getInstance();

	// Start up Game Manager

	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp()) {
		log_manager.writeLog("Error starting game manager!\n");
		game_manager.shutDown();
		exit(1);
	}

	level_manager.startUp();

	loadResources();

	new GameStart;

	game_manager.run();

	// Shut everything down
	game_manager.shutDown();
}

void loadResources() {
	// load saucer sprite
	ResourceManager &resource_manager = ResourceManager::getInstance();
	LevelManager &level_manager = LevelManager::getInstance();

	//Hero
	resource_manager.loadSprite("sprites/heror-spr.txt", "hero_r");
	resource_manager.loadSprite("sprites/herod-spr.txt", "hero_d");
	resource_manager.loadSprite("sprites/herol-spr.txt", "hero_l");
	resource_manager.loadSprite("sprites/herou-spr.txt", "hero_u");

	//Monsters
	resource_manager.loadSprite("sprites/monster1-spr.txt", "monster1");
	resource_manager.loadSprite("sprites/ghost-spr.txt", "ghost");

	//Effects
	resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");
	resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");

	//Power ups
	resource_manager.loadSprite("sprites/rapid-spr.txt", "rapid");
	resource_manager.loadSprite("sprites/health-spr.txt", "health");
	resource_manager.loadSprite("sprites/max-spr.txt", "max");
	resource_manager.loadSprite("sprites/points-spr.txt", "points_pickup");

	//Splash screens
	resource_manager.loadSprite("sprites/gamestart-spr.txt", "game_start");
	resource_manager.loadSprite("sprites/gameover-spr.txt", "gameover");

	//Levels
	level_manager.prepareLevel("levels/Level1.txt", "level_1");
}
