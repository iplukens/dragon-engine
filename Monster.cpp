/*
 * Monster.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: ian
 */

//ENGINE INCLUDES
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Monster.h"
#include "EventHeroMove.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "Explosion.h"

#include <stdlib.h>

Monster::Monster(Position pos) {
	WorldManager &world_manager = WorldManager::getInstance();
	Position h_pos(7, world_manager.getBoundary().getVertical() / 2);
	hero_pos = h_pos;

	setPosition(pos);
	setType("Monster1");

	LogManager &lm = LogManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	Sprite *p_temp_sprite;

	p_temp_sprite = rm.getSprite("monster1");
	if (!p_temp_sprite) {
		lm.writeLog("Monster::Monster(): Warning! Sprite '%s' not found",
				"monster1");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);		// third speed animation
	}

	speed_cooldown = 10;

	registerInterest(HERO_MOVE_EVENT);
	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);
}

int Monster::eventHandler(Event *p_e) {
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
		hit(p_c_e);
	}
	return 0;
}

void Monster::move_to_hero() {
	WorldManager &wm = WorldManager::getInstance();
	Position pos = getPosition();
	Position new_pos(getPosition().getX(), getPosition().getY());

	if (abs(pos.getX() - hero_pos.getX()) > abs(pos.getY() - hero_pos.getY())) {
		if (pos.getX() > hero_pos.getX()) {
			new_pos.setX(getPosition().getX() - 1);
		} else if (pos.getX() < hero_pos.getX()) {
			new_pos.setX(getPosition().getX() + 1);
		}
	} else if (pos.getY() > hero_pos.getY()) {
		new_pos.setY(getPosition().getY() - 1);
	} else {
		new_pos.setY(getPosition().getY() + 1);
	}
	wm.moveObject(this, new_pos);
}

void Monster::hit(EventCollision* e) {
	WorldManager &wm = WorldManager::getInstance();

	if (e->getObject1()->getType() == "Bullet"
			|| e->getObject2()->getType() == "Bullet") {
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		wm.markForDelete(e->getObject1());
		wm.markForDelete(e->getObject2());
	}
}
