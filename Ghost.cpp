/*
 * Ghost.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rjsmieja, iplukens
 */

//ENGINE INCLUDES
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Ghost.h"
#include "EventHeroMove.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "EventView.h"
#include "Points.h"

#include <stdlib.h>

#define GHOST_VELOCITY 0.025

Ghost::Ghost(Position pos) {
	WorldManager &world_manager = WorldManager::getInstance();

	setPosition(pos);
	setType("Ghost");
	setSolidness(SOFT); //Ghosts can move through anything
	setAltitude(MAX_ALTITUDE);

	//TODO: This takes too long to find, is there a more efficient way?
/*
	ObjectList objects = world_manager.getAllObjects();
	ObjectListIterator iterator = objects.createIterator();

	bool found = false;
	while(!iterator.isDone() && !found){
		if (iterator.currentObject()->getType() == "Hero"){

			hero_pos = iterator.currentObject()->getPosition();

			found = true;
		}
	}
*/

//	if (!found){
		Position h_pos(world_manager.getBoundary().getHorizontal()/ 2, world_manager.getBoundary().getVertical() / 2);
		hero_pos = h_pos;
//	}

	LogManager &lm = LogManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	Sprite *p_temp_sprite;

	p_temp_sprite = rm.getSprite("ghost");
	if (!p_temp_sprite) {
		lm.writeLog("Ghost::Ghost(): Warning! Sprite '%s' not found", "ghost");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}

	speed_cooldown = 30;

	registerInterest(HERO_MOVE_EVENT);
	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);
}

int Ghost::eventHandler(Event *p_e) {
	if (p_e->getType() == HERO_MOVE_EVENT) {
		EventHeroMove *p_hm_e = static_cast<EventHeroMove *>(p_e);
		hero_pos = p_hm_e->getPos();
		return 1;
	}
	if (p_e->getType() == STEP_EVENT) {
		speed_cooldown--;
		if (speed_cooldown == 0) {
			speed_cooldown = 10;
			move_to_hero();
		}
		return 1;
	}
	if (p_e->getType() == COLLISION_EVENT) {
		EventCollision *p_c_e = static_cast<EventCollision *>(p_e);
		handleCollision(p_c_e);
	}
	return 0;
}

void Ghost::move_to_hero() {
	WorldManager &wm = WorldManager::getInstance();
	Position pos = getPosition();

	if (abs(pos.getX() - hero_pos.getX()) > abs(pos.getY() - hero_pos.getY())) {
		if (pos.getX() > hero_pos.getX()) {
			setXVelocity(-GHOST_VELOCITY);
		} else if (pos.getX() < hero_pos.getX()) {
			setXVelocity(GHOST_VELOCITY);
		}
	} else if (pos.getY() > hero_pos.getY()) {
		setYVelocity(-GHOST_VELOCITY);
	} else {
		setYVelocity(GHOST_VELOCITY);
	}
}

void Ghost::handleCollision(EventCollision* e) {
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	string collision_obj1_type = e->getObject1()->getType();
	string collision_obj2_type = e->getObject2()->getType();

	if (collision_obj1_type == "Bullet"
			|| collision_obj2_type == "Bullet") {
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		world_manager.markForDelete(e->getObject1());
		world_manager.markForDelete(e->getObject2());
	}
}

Ghost::~Ghost(){
	WorldManager &wm = WorldManager::getInstance();
	// send "view" event with points to interested ViewObjects
	EventView ev(POINTS_STRING, 10, true);
	wm.onEvent(&ev);
}
