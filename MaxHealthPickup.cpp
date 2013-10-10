/*
 * MaxHealthPickup.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: ian
 */

#include "MaxHealthPickup.h"
#include "LogManager.h"
#include "ResourceManager.h"

MaxHealthPickup::MaxHealthPickup() {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	// setup "bullet" sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("max");
	if (!p_temp_sprite) {
		log_manager.writeLog(
				"MaxHealthPickup::MaxHealthPickup(): Warning! Sprite '%s' not found",
				"max");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
	// set object type
	setType("max");
	time_to_spawn = 0;
	SPAWN = 400;
	spawned = false;
	registerInterest(STEP_EVENT);
}

void MaxHealthPickup::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c->getObject1());
		world_manager.markForDelete(p_c->getObject2());

		// make sure extra max health pickups stay around
		new MaxHealthPickup;
	}
}
