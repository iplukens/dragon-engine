/*
 * Monster.h
 *
 *  Created on: Oct 9, 2013
 *      Author: ian
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include "Object.h"
#include "Position.h"
#include "EventCollision.h"

class Monster: public Object {
private:
	Position hero_pos; // where the hero is currently
	void move_to_hero(); // move to the hero
	int speed_cooldown; // make sure doesn't move every frame
	void handleCollision (EventCollision* e);
	bool haveCollidedWithMaze;
	int collisionWanderCount;
	bool negativeCollisionDirection;
public:
	Monster(Position pos);
	~Monster();
	int eventHandler(Event *p_e);
};

#endif /* MONSTER_H_ */
