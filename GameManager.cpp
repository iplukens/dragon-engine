/*
 * GameManager.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#include "GameManager.h"
#include "Clock.h"
#include "LogManager.h"
#include <unistd.h>
#include "Object.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

GameManager::GameManager() {
	game_over = false;
	frame_time = 30;
}

int GameManager::startUp() {
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	InputManager &im = InputManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	if (lm.startUp(true)) {
		lm.writeLog(
				"GameManager::startUp(): The Game Manager encountered an error; log manager failed to start");
		return 1;
	}
	if (wm.startUp()) {
		lm.writeLog(
				"GameManager::startUp(): The Game Manager encountered an error; world manager failed to start");
		return 1;
	}
	if (gm.startUp()) {
		lm.writeLog(
				"GameManager::startUp(): The Game Manager encountered an error; graphics manager failed to start");
		return 1;
	}
	if (im.startUp()) {
		lm.writeLog(
				"GameManager::startUp(): The Game Manager encountered an error; input manager failed to start");
		return 1;
	}
	if (rm.startUp()) {
		lm.writeLog(
				"GameManager::startUp(): The Game Manager encountered an error; resource manager failed to start");
		return 1;
	} else {
		lm.writeLog(
				"GameManager::startUp(): The Game, World, Graphics, Input, and Log Manager have started up successfully");
		return Manager::startUp();
	}
}

// shuts down all the managers and the game manager
int GameManager::shutDown() {
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	if (wm.shutDown())
		return 1;
	if (gm.shutDown())
		return 1;
	if (lm.shutDown())
		return 1;
	if (rm.shutDown())
		return 1;
	else
		return Manager::shutDown();
}

void GameManager::run(int fr_time) {
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	InputManager &im = InputManager::getInstance();
	Clock c;
	while (!game_over) {
		c.delta();
		ObjectList world_objects = wm.getAllObjects();
		ObjectListIterator li(&world_objects);
		EventStep* e = new EventStep();
		Event *eve = static_cast<Event*>(e);
		onEvent(eve);
		// get that input
		im.getInput();
		// Update all objects. (deletions)
		wm.update();
		// Draw all objects
		wm.draw();
		gm.swapBuffers();
		// sleep to delay for frame time
		int this_int = (frame_time * 1000) - (c.split() * 1000);
		if (this_int > 0) {
			lm.writeLog("Sleeping for %d", this_int);
			usleep(this_int);
		}
		lm.writeLog("EXITING: Game loop took %d milliseconds", c.split());
	}
	lm.writeLog("Game loop ended.");
}

// Set game over status to indicated value.
// If true (the default), will stop game loop.
void GameManager::setGameOver(bool new_game_over) {
	game_over = new_game_over;
}

// Return frame time.
// Frame time is target time for game loop, in milliseconds.
int GameManager::getFrameTime() {
	return frame_time;
}

GameManager &GameManager::getInstance() {
	static GameManager instance; // Guaranteed to be destroyed.
								 // Instantiated on first use.
	return instance;
}

bool GameManager::isValid(string event_name) {
	bool result = false;
	if (event_name == STEP_EVENT) {
		result = true;
	}
	return result;
}
