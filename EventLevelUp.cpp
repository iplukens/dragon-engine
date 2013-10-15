/*
 * EventLevelUp.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: ian
 */

#include "EventLevelUp.h"

EventLevelUp::EventLevelUp(int current_level) {
	level = current_level;
	setType(LEVEL_UP_EVENT);
}

EventLevelUp::~EventLevelUp() {
	// TODO Auto-generated destructor stub
}

int EventLevelUp::getLevel(){
	return level;
}
