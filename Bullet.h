/*
 * Bullet.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Object.h"
#include "Hero.h"

class Bullet: public Object {

protected:
	void out();

public:
	Bullet(Position hero_pos, HeroDirection direction);
	int eventHandler(Event *p_e);
};

#endif /* BULLET_H_ */
