/*
 * PointsPickup.cpp
 *
 *  Created on: October 13, 2013
 *      Author: rjsmieja, iplukens
 */

#include "PointsPickup.h"
#include "LogManager.h"
#include "ResourceManager.h"

PointsPickup::PointsPickup(Position pos) {
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("points_pickup");
	if (!p_temp_sprite) {
		log_manager.writeLog("PointsPickup::PointsPickup(): Warning! Sprite '%s' not found",
				"points_pickup");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
	// set object type
	setType("points_pickup");
	registerInterest(COLLISION_EVENT);
	setPosition(pos);
}

void PointsPickup::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Bullet")
			|| (p_c->getObject2()->getType() == "Bullet")) {
		// make sure power-up stays around
		WorldManager &world_manager = WorldManager::getInstance();
		if((p_c->getObject1()->getType() == "Bullet"))
			world_manager.markForDelete(p_c->getObject1());
		else
			world_manager.markForDelete(p_c->getObject2());
	}
}
