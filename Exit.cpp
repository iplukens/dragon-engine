/*
 * Exit.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: rjsmieja, iplukens
 */

//ENGINE INCLUDES
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Exit.h"
#include "EventHeroMove.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "EventView.h"
#include "Points.h"
#include "LevelManager.h"

#include <stdlib.h>

Exit::Exit(Position pos) {
	WorldManager &world_manager = WorldManager::getInstance();

	setPosition(pos);
	setType("Exit");
	setSolidness(HARD);
	setAltitude(MAX_ALTITUDE); //Exits stay on top

	LogManager &lm = LogManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	Sprite *p_temp_sprite;

	p_temp_sprite = rm.getSprite("exit");
	if (!p_temp_sprite) {
		lm.writeLog("Exit::Exit(): Warning! Sprite '%s' not found", "exit");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	registerInterest(COLLISION_EVENT);
}

int Exit::eventHandler(Event *p_e) {
	if (p_e->getType() == COLLISION_EVENT) {
		EventCollision *p_c_e = static_cast<EventCollision *>(p_e);
		handleCollision(p_c_e);
	}
	return 0;
}

void Exit::handleCollision(EventCollision* e) {
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	string collision_obj1_type = e->getObject1()->getType();
	string collision_obj2_type = e->getObject2()->getType();

	//Transition to next level, hero made it!
	if (collision_obj1_type == "Hero"
			|| collision_obj2_type == "Hero") {

		LevelManager &level_manager = LevelManager::getInstance();
		level_manager.nextLevel();
	} else if (e->getObject1()->getType() == "Bullet") {
		world_manager.markForDelete(e->getObject1());
	} else if (e->getObject2()->getType() == "Bullet"){
		world_manager.markForDelete(e->getObject2());
	}
}

Exit::~Exit(){
	WorldManager &wm = WorldManager::getInstance();

	//send "view" event with points to interested ViewObjects
	EventView ev(POINTS_STRING, 100, true);
	wm.onEvent(&ev);
}
