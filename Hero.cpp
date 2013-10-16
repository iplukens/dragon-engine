/*
 * Hero.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GraphicsManager.h"

#include "Hero.h"
#include "EventStep.h"
#include "Bullet.h"
#include "Explosion.h"
#include "RapidFire.h"
#include "MaxHealthPickup.h"
#include "HealthPickup.h"
#include "PointsPickup.h"
#include "EventHeroMove.h"
#include "EventView.h"
#include "Position.h"
#include "Points.h"

#define UP_KEY 259
#define DOWN_KEY 258
#define LEFT_KEY 260
#define RIGHT_KEY 261

Hero::Hero(Position pos) {
	LogManager &lm = LogManager::getInstance();
	changeSprite("hero_r");

	// player controls hero, so register with keyboard
	registerInterest(KEYBOARD_EVENT);
	registerInterest(STEP_EVENT);
	setType("Hero");
	GraphicsManager &gm = GraphicsManager::getInstance();
	setPosition(pos);

	current_health = 1;
	max_health = 2;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	direction = RIGHT;
}

Hero::Hero() {
	LogManager &lm = LogManager::getInstance();
	changeSprite("hero_r");

	// player controls hero, so register with keyboard
	registerInterest(KEYBOARD_EVENT);
	registerInterest(STEP_EVENT);
	setType("Hero");
	GraphicsManager &gm = GraphicsManager::getInstance();
	Position pos(7, gm.getVertical() / 2);
	setPosition(pos);
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	direction = RIGHT;
}

int Hero::eventHandler(Event *p_e) {
	if (p_e->getType() == KEYBOARD_EVENT) {
		EventKeyboard *p_keyboard_event = static_cast<EventKeyboard *>(p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == COLLISION_EVENT) {
		EventCollision *p_collision_event = static_cast<EventCollision *>(p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

// call move (or do nothing) according to key pressed
void Hero::kbd(EventKeyboard *p_keyboard_event) {

	//std::cout << p_keyboard_event->getKey() << std::endl;
	WorldManager &world_manager = WorldManager::getInstance();

	switch (p_keyboard_event->getKey()) {
	case UP_KEY:		// up arrow
		moveY(-1);
		direction = UP;
		changeSprite("hero_u");
		break;
	case DOWN_KEY:		// down arrow
		moveY(+1);
		direction = DOWN;
		changeSprite("hero_d");
		break;
	case LEFT_KEY:		// left arrow key
		moveX(-1);
		direction = LEFT;
		changeSprite("hero_l");
		break;
	case RIGHT_KEY:		// right arrow key
		moveX(1);
		direction = RIGHT;
		changeSprite("hero_r");
		break;
	case ' ':
		fire();
		break;
	case 'q':			// quit
		world_manager.markForDelete(this);
		gameover();
		break;
	};
	return;
}

// changes the sprite according to the direction the hero is facing
void Hero::changeSprite(string type) {
	LogManager &lm = LogManager::getInstance();
	ResourceManager &rm = ResourceManager::getInstance();
	Sprite *p_temp_sprite;

	p_temp_sprite = rm.getSprite(type);
	if (!p_temp_sprite) {
		lm.writeLog("Hero::Hero(): Warning! Sprite '%s' not found",
				type.c_str());
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);		// third speed animation
	}
}

void Hero::sendMoveEvent() {
	EventHeroMove *move_event = new EventHeroMove(getPosition());
	WorldManager &wm = WorldManager::getInstance();
	wm.onEvent(move_event);
}

// move up or down
void Hero::moveY(int dy) {
	GraphicsManager &gm = GraphicsManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();

	Position new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) && (new_pos.getY() < gm.getVertical()))
		wm.moveObject(this, new_pos);
	sendMoveEvent();
}

// move left or right
void Hero::moveX(int dx) {
	GraphicsManager &gm = GraphicsManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();

	Position new_pos(getPosition().getX() + dx, getPosition().getY());
	if ((new_pos.getX() > 3) && (new_pos.getX() < gm.getHorizontal()))
		wm.moveObject(this, new_pos);
	sendMoveEvent();
}

// fire a bullet
void Hero::fire() {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	new Bullet(getPosition(), direction);
}

// decrease fire restriction
void Hero::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

Hero::~Hero() {
	//Use to be gameover, but removed for level transitions
}

//Gameover
void Hero::gameover() {
	// make big explosion
	for (int i = -8; i <= 8; i += 5) {
		for (int j = -5; j <= 5; j += 3) {
			Position temp_pos = this->getPosition();
			temp_pos.setX(this->getPosition().getX() + i);
			temp_pos.setY(this->getPosition().getY() + j);
			Explosion *p_explosion = new Explosion;
			p_explosion->setPosition(temp_pos);
		}
	}
	GameManager &gm = GameManager::getInstance();
	gm.setGameOver();
}

// evaluates what hit the hero
// goes through checking if it's any of the pickup items or is it a saucer
void Hero::hit(EventCollision *e) {
	WorldManager &world_manager = WorldManager::getInstance();
	if (e->getObject1()->getType() == "rapid"
			|| e->getObject2()->getType() == "rapid") {
		if (fire_slowdown > 4)
			fire_slowdown -= 4;
		if (e->getObject1()->getType() == "rapid")
			world_manager.markForDelete(e->getObject1());
		else
			world_manager.markForDelete(e->getObject2());
	} else if (e->getObject1()->getType() == "health"
			|| e->getObject2()->getType() == "health") {
		if (max_health > current_health) {
			current_health++;
			EventView ev("Health", 1, true);
			world_manager.onEvent(&ev);
		}
		if (e->getObject1()->getType() == "health")
			world_manager.markForDelete(e->getObject1());
		else
			world_manager.markForDelete(e->getObject2());
	} else if (e->getObject1()->getType() == "max"
			|| e->getObject2()->getType() == "max") {
		max_health++;
		if (e->getObject1()->getType() == "max")
			world_manager.markForDelete(e->getObject1());
		else
			world_manager.markForDelete(e->getObject2());

		// if saucer, mark both objects for destruction or lower health
	} else if (((e->getObject1()->getType()) == "Monster1")
			|| ((e->getObject2()->getType()) == "Monster1")) {
		current_health--;
		EventView ev("Health", -1, true);
		world_manager.onEvent(&ev);
		if (current_health == 0) {
			world_manager.markForDelete(e->getObject1());
			world_manager.markForDelete(e->getObject2());

			gameover();
		}

		Explosion *p_explosion = new Explosion;
		if (e->getObject1()->getType() == "Monster1") {
			p_explosion->setPosition(e->getObject1()->getPosition());
			world_manager.markForDelete(e->getObject1());
		} else {
			p_explosion->setPosition(e->getObject2()->getPosition());
			world_manager.markForDelete(e->getObject2());
		}

	} else if (((e->getObject1()->getType()) == "Monster2")
			|| ((e->getObject2()->getType()) == "Monster2")) {
		current_health--;
		EventView ev("Health", -1, true);
		world_manager.onEvent(&ev);
		if (current_health == 0) {
			world_manager.markForDelete(e->getObject1());
			world_manager.markForDelete(e->getObject2());

			gameover();
		}

		Explosion *p_explosion = new Explosion;
		if (e->getObject1()->getType() == "Monster2") {
			p_explosion->setPosition(e->getObject1()->getPosition());
			world_manager.markForDelete(e->getObject1());
		} else {
			p_explosion->setPosition(e->getObject2()->getPosition());
			world_manager.markForDelete(e->getObject2());
		}

	} else if (((e->getObject1()->getType()) == "Ghost")
			|| ((e->getObject2()->getType()) == "Ghost")) {
		current_health--;
		EventView ev("Health", -1, true);
		world_manager.onEvent(&ev);
		if (current_health == 0) {
			world_manager.markForDelete(e->getObject1());
			world_manager.markForDelete(e->getObject2());

			gameover();
		}

		Explosion *p_explosion = new Explosion;
		if (e->getObject1()->getType() == "Ghost") {
			p_explosion->setPosition(e->getObject1()->getPosition());
			world_manager.markForDelete(e->getObject1());
		} else {
			p_explosion->setPosition(e->getObject2()->getPosition());
			world_manager.markForDelete(e->getObject2());
		}

	} else if (((e->getObject1()->getType()) == "points_pickup")
			|| ((e->getObject2()->getType()) == "points_pickup")) {

		//Add to points
		EventView ev(POINTS_STRING, 30, true);
		world_manager.onEvent(&ev);

		//Delete pickup
		if (e->getObject1()->getType() == "points_pickup") {
			world_manager.markForDelete(e->getObject1());
		} else {
			world_manager.markForDelete(e->getObject2());
		}
	}
}
