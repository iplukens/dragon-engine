/*
 * HealthPickup.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: ian
 */

#include "HealthPickup.h"
#include "LogManager.h"
#include "ResourceManager.h"

HealthPickup::HealthPickup() {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	// setup "bullet" sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("health");
	if (!p_temp_sprite) {
		log_manager.writeLog("Health::Health(): Warning! Sprite '%s' not found",
				"health");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
	// set object type
	setType("health");
	time_to_spawn = 0;
	SPAWN = 300;
	spawned = false;
	registerInterest(EVENT_STEP);
}

void HealthPickup::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c->getObject1());
		world_manager.markForDelete(p_c->getObject2());

		// make sure extra health pickups stay around
		new HealthPickup;
	}
}
