/*
 * EventHeroMove.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: ian
 */

#include "EventHeroMove.h"

EventHeroMove::EventHeroMove(Position new_pos) {
	setType(HERO_MOVE_EVENT);
	pos = new_pos;
}

Position EventHeroMove::getPos(){
	return pos;
}
