/*
 * Ghost.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rjsmieja, iplukens
 */

#ifndef GHOST_H_
#define GHOST_H_

#include "Object.h"
#include "Position.h"
#include "EventCollision.h"

class Ghost: public Object {
private:
	Position hero_pos; // where we are currently
	void move_to_hero(); // move to the hero
	int speed_cooldown; // make sure doesn't move every frame
	void handleCollision (EventCollision* e);
public:
	Ghost(Position pos);
	~Ghost();
	int eventHandler(Event *p_e);
};

#endif /* GHOST_H_ */
