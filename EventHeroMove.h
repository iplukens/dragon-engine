/*
 * EventHeroMove.h
 *
 *  Created on: Oct 9, 2013
 *      Author: ian
 */

#ifndef EVENTHEROMOVE_H_
#define EVENTHEROMOVE_H_

#include "Event.h"
#include "Position.h"

#define HERO_MOVE_EVENT "hero_move"

class EventHeroMove: public Event {
private:
	Position pos;
public:
	EventHeroMove(Position new_pos);
	Position getPos();
};

#endif /* EVENTHEROMOVE_H_ */
