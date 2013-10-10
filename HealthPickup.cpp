/*
 * HealthPickup.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: ian
 */

#include "HealthPickup.h"
#include "LogManager.h"
#include "ResourceManager.h"

HealthPickup::HealthPickup(Position pos) {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("health");
	if (!p_temp_sprite) {
		log_manager.writeLog("Health::Health(): Warning! Sprite '%s' not found",
				"health");
	} else {
		setSprite(p_temp_sprite);
	}
	// set object type
	setType("health");
	setPosition(pos);
	registerInterest(COLLISION_EVENT);
}

void HealthPickup::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		WorldManager &world_manager = WorldManager::getInstance();
		if (p_c->getObject1()->getType() == "Bullet")
			world_manager.markForDelete(p_c->getObject1());
		else
			world_manager.markForDelete(p_c->getObject2());
	}
}
