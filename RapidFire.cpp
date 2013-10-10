/*
 * RapidFire.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include "RapidFire.h"
#include "LogManager.h"
#include "ResourceManager.h"

RapidFire::RapidFire() {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	// setup "bullet" sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("rapid");
	if (!p_temp_sprite) {
		log_manager.writeLog("Rapid::Rapid(): Warning! Sprite '%s' not found",
				"rapid");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
	// set object type
	setType("rapid");
	time_to_spawn = 0;
	SPAWN = 100;
	spawned = false;
	registerInterest(STEP_EVENT);
}

void RapidFire::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		// make sure extra rapid fires stay around
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c->getObject1());
		world_manager.markForDelete(p_c->getObject2());

		new RapidFire;
	}
}
