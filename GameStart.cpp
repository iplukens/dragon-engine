/*
 * GameStart.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include <stdlib.h>

#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GraphicsManager.h"	// for COLOR_YELLOW
#include "WorldManager.h"

// game includes
#include "GameStart.h"
#include "Hero.h"
#include "Points.h"
#include "EventKeyboard.h"
#include "RapidFire.h"
#include "HealthPickup.h"
#include "MaxHealthPickup.h"
#include "Monster.h"
#include "MazePiece.h"

// different pickup items
#include "HealthPickup.h"
#include "RapidFire.h"

#define MAZE_WALL_COUNT 30

GameStart::GameStart() {
	// link to "message" sprite
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("game_start");
	if (!p_temp_sprite) {
		LogManager &log_manager = LogManager::getInstance();
		log_manager.writeLog(
				"GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}

	// put in center of screen
	WorldManager &world_manager = WorldManager::getInstance();
	Position pos(
			world_manager.getBoundary().getCorner().getX()
					+ world_manager.getBoundary().getHorizontal() / 2,
			world_manager.getBoundary().getCorner().getY()
					+ world_manager.getBoundary().getVertical() / 2);
	setPosition(pos);

	// register for "keyboard" event
	registerInterest(KEYBOARD_EVENT);
}

// handle event
// return 0 if ignored, else 1
int GameStart::eventHandler(Event *p_e) {
	GameManager &game_manager = GameManager::getInstance();

	// keyboard
	if (p_e->getType() == KEYBOARD_EVENT) {
		EventKeyboard *p_keyboard_event = (EventKeyboard *) p_e;
		switch (p_keyboard_event->getKey()) {
		case 'p': 			// play
			start();
			break;
		case 'q':			// quit
			game_manager.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}

	// if we get here, we have ignored this event
	return 0;
}

void GameStart::start() {
	WorldManager &world_manager = WorldManager::getInstance();
	SceneGraph &scene_graph = world_manager.getSceneGraph();

	// will populate play world with objects
	scene_graph.setLevel(PLAY_LEVEL);
	// create hero
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
		new MazePiece(
				Position(world_manager.getBoundary().getHorizontal() - 1, i));
	}
	for (int i = 1; i < world_manager.getBoundary().getHorizontal(); i++) {
		new MazePiece(Position(i, 3));
		new MazePiece(
				Position(i, world_manager.getBoundary().getVertical() - 1));
	}

	//Inner maze walls
	for (int i = 0; i < MAZE_WALL_COUNT; i++) {
		new MazePiece(
				Position(
						random() % (world_manager.getBoundary().getHorizontal() - 3) + 1,
						random() % (world_manager.getBoundary().getVertical() - 4) + 3));
	}

	new Monster(Position(5, 5));
	new Monster(Position(10, 5));
	new Monster(Position(15, 10));

	new HealthPickup(Position(20, 20));
	new RapidFire(Position(21, 21));

	// tell world manager to goto game level
	world_manager.setLevel(PLAY_LEVEL);
}

// override default draw so as not to display "value"
void GameStart::draw() {
	Object::draw();
}
