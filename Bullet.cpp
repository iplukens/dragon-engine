/*
 * Bullet.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include "Bullet.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

Bullet::Bullet(Position hero_pos, HeroDirection direction) {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	// setup "bullet" sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("bullet");
	if (!p_temp_sprite) {
		log_manager.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found",
				"bullet");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}
	// set object type
	setType("Bullet");

	// make sure bullet spawns in correct spot
	int pos_adjust_x = 0;
	int pos_adjust_y = 0;

	// make the bullet go the right way
	switch(direction){
	case RIGHT:
		setXVelocity(1);
		pos_adjust_x = 2;
		break;
	case LEFT:
		setXVelocity(-1);
		pos_adjust_x = -2;
		break;
	case UP:
		setYVelocity(-1);
		pos_adjust_y = -1;
		break;
	case DOWN:
		setYVelocity(1);
		pos_adjust_y = 1;
		break;
	};

	// set starting location, based on the hero's position passed in
	Position pos(hero_pos.getX() + pos_adjust_x, hero_pos.getY() + pos_adjust_y);
	setPosition(pos);

	registerInterest(COLLISION_EVENT);
}

int Bullet::eventHandler(Event *p_e) {
	if (p_e->getType() == OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == COLLISION_EVENT){
		EventCollision *p_c_e = static_cast<EventCollision *>(p_e);
		hit(p_c_e);
	}
	return 0;
}

void Bullet::out() {
	WorldManager &world_manager = WorldManager::getInstance();
	world_manager.markForDelete(this);
}

void Bullet::hit(EventCollision *e) {
	WorldManager &world_manager = WorldManager::getInstance();
	if (e->getObject1()->getType() == "Maze"
			|| e->getObject2()->getType() == "Maze") {
		if (e->getObject1()->getType() == "Bullet")
			world_manager.markForDelete(e->getObject1());
		else
			world_manager.markForDelete(e->getObject2());
	}
}
