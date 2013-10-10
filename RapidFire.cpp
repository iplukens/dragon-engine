/*
 * RapidFire.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include "RapidFire.h"
#include "LogManager.h"
#include "ResourceManager.h"

RapidFire::RapidFire(Position pos) {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
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
	registerInterest(COLLISION_EVENT);
	setPosition(pos);
}

void RapidFire::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		// make sure extra rapid fires stay around
		WorldManager &world_manager = WorldManager::getInstance();
		if((p_c->getObject1()->getType() == "Bullet"))
			world_manager.markForDelete(p_c->getObject1());
		else
			world_manager.markForDelete(p_c->getObject2());
	}
}
