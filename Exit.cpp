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

#include <stdlib.h>

Exit::Exit(Position pos) {
	WorldManager &world_manager = WorldManager::getInstance();

	setPosition(pos);
	setType("Exit");
	setSolidness(SPECTRAL); //Exits stay on top
	setAltitude(MAX_ALTITUDE);

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

	if (collision_obj1_type == "Hero"
			|| collision_obj2_type == "Hero") {

		//TODO Transition level
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		world_manager.markForDelete(e->getObject1());
		world_manager.markForDelete(e->getObject2());
	}
}

Exit::~Exit(){
	WorldManager &wm = WorldManager::getInstance();
	// send "view" event with points to interested ViewObjects
//	EventView ev(POINTS_STRING, 10, true);
//	wm.onEvent(&ev);
}
