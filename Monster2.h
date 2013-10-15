/*
 * Monster2.h
 *
 *  Created on: Oct 15, 2013
 *      Author: ian
 */

#ifndef MONSTER2_H_
#define MONSTER2_H_

#include "Object.h"
#include "Position.h"
#include "EventCollision.h"

class Monster2: public Object {
private:
	Position hero_pos; // where the hero is currently
	void move_to_hero(); // move to the hero
	int speed_cooldown; // make sure doesn't move every frame
	void hit (EventCollision* e);
public:
	Monster2(Position pos);
	~Monster2();
	int eventHandler(Event *p_e);
};


#endif /* MONSTER2_H_ */
