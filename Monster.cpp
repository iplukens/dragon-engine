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
#include "EventLevelUp.h"
#include "Explosion.h"
#include "EventView.h"
#include "Points.h"
#include "LevelManager.h"

#include <stdlib.h>

//Random number between 0 to 2, -1 to make it -1 to 1
//#define RANDOM_POSITIVE_OR_NEGATIVE_INT ((random() % 5) - 2)
#define COLLISION_COUNT_MAX 4

Monster::Monster(Position pos) {
	WorldManager &world_manager = WorldManager::getInstance();

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
	Position h_pos(world_manager.getBoundary().getHorizontal() / 2,
			world_manager.getBoundary().getVertical() / 2);
	hero_pos = h_pos;
//	}

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
	max_speed_cooldown = 10;

	haveCollidedWithMaze = false;
	collisionWanderCount = 0;
	negativeCollisionDirection = false;

	registerInterest(HERO_MOVE_EVENT);
	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);
	registerInterest(LEVEL_UP_EVENT);
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
			speed_cooldown = max_speed_cooldown;
			move_to_hero();
		}
		return 1;
	}
	if (p_e->getType() == COLLISION_EVENT) {
		EventCollision *p_c_e = static_cast<EventCollision *>(p_e);
		handleCollision(p_c_e);
	}
	if (p_e->getType() == LEVEL_UP_EVENT) {
		EventLevelUp *le = static_cast<EventLevelUp *>(p_e);
		max_speed_cooldown -= le->getLevel();
		if (max_speed_cooldown < 1) {
			max_speed_cooldown = 1;
		}
	}
	return 0;
}

void Monster::move_to_hero() {
	WorldManager &wm = WorldManager::getInstance();
	Position pos = getPosition();
	Position new_pos(getPosition().getX(), getPosition().getY());

	if (!haveCollidedWithMaze) {
		if (abs(pos.getX() - hero_pos.getX())
				> abs(pos.getY() - hero_pos.getY())) {
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
	} else {
		if (abs(pos.getX() - hero_pos.getX())
				> abs(pos.getY() - hero_pos.getY())) {
			if (negativeCollisionDirection) {
				new_pos.setY(getPosition().getY() + 1);
			} else {
				new_pos.setY(getPosition().getY() - 1);
			}
		} else {
			if (negativeCollisionDirection) {
				new_pos.setX(getPosition().getX() + 1);
			} else {
				new_pos.setX(getPosition().getX() - 1);
			}
		}
		wm.moveObject(this, new_pos);

		collisionWanderCount--;

		if (collisionWanderCount == 0) {
			haveCollidedWithMaze = false;
		}
	}
}

void Monster::handleCollision(EventCollision* e) {
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	string collision_obj1_type = e->getObject1()->getType();
	string collision_obj2_type = e->getObject2()->getType();

	if (collision_obj1_type == "Bullet" || collision_obj2_type == "Bullet") {
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		world_manager.markForDelete(e->getObject1());
		world_manager.markForDelete(e->getObject2());
	} else {
		//Go crazy, AHWAHWAHWAHWAHWAHWAH
		haveCollidedWithMaze = true;
		collisionWanderCount = COLLISION_COUNT_MAX;

		//Random direction perpendicular to hero
		negativeCollisionDirection = random() % 2;
	}
}

Monster::~Monster() {
	WorldManager &wm = WorldManager::getInstance();
	LevelManager &level_manager = LevelManager::getInstance();
	// send "view" event with points to interested ViewObjects
	EventView ev(POINTS_STRING, 10, true);
	wm.onEvent(&ev);

	level_manager.objectDelete(this);
}
