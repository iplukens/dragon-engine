/*
 * Hero.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef HERO_H_
#define HERO_H_

#include "Object.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "Position.h"

using std::string;

// where the hero is facing
enum HeroDirection {	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Hero: public Object {

protected:
	HeroDirection direction;
	int current_health;
	int max_health;
	int fire_slowdown;
	int fire_countdown;
	void kbd(EventKeyboard *p_keyboard_event);
	void moveY(int dy);
	void moveX(int dx);
	void fire();
	void step();
	void changeSprite(string type);
	void hit(EventCollision *e);
	void sendMoveEvent();

public:
	Hero();
	Hero(Position pos);
	~Hero();
	int eventHandler(Event *p_e);
};

#endif /* HERO_H_ */
