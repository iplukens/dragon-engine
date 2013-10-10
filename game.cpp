#include <stdlib.h>         // for exit()
// Engine includes
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

// Game includes
#include "Hero.h"
#include "MazePiece.h"
#include "Monster.h"
#include "Points.h"

// different pickup items
#include "HealthPickup.h"
#include "RapidFire.h"

#define MAZE_WALL_COUNT 40

void loadResources();

int main(int argc, char *argv[]) {
	LogManager &log_manager = LogManager::getInstance();

	// Start up Game Manager

	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp()) {
		log_manager.writeLog("Error starting game manager!\n");
		game_manager.shutDown();
		exit(1);
	}

	loadResources();

	WorldManager &world_manager = WorldManager::getInstance();

	ViewObject *h_vo = new ViewObject; // used for health count
	h_vo->setLocation(TOP_LEFT);
	h_vo->setViewString("Health");
	h_vo->setValue(1);
	h_vo->setColor(COLOR_RED);

	new Points;
	new Hero;

	//Outer maze walls
	for (int i = 3; i < world_manager.getBoundary().getVertical(); i++) {
		new MazePiece(Position(0, i));
		new MazePiece(Position(world_manager.getBoundary().getHorizontal() - 1, i));
	}
	for (int i = 1; i < world_manager.getBoundary().getHorizontal(); i++) {
		new MazePiece(Position(i, 3));
		new MazePiece(Position(i, world_manager.getBoundary().getVertical() - 1));
	}

	//Inner maze walls
	for(int i = 0; i < MAZE_WALL_COUNT; i++){
		new MazePiece(Position(random() % (world_manager.getBoundary().getHorizontal() - 3) + 1, random() % (world_manager.getBoundary().getVertical() - 4) + 3 )) ;
	}

	new Monster(Position(5, 5));
	new Monster(Position(10, 5));
	new Monster(Position(15, 10));

	new HealthPickup(Position(20, 20));
	new RapidFire(Position(21, 21));

	game_manager.run();

	// Shut everything down
	game_manager.shutDown();
}

void loadResources() {
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
	rm.loadSprite("sprites/gamestart-spr.txt", "game_start");
}
