/*
 * EventLevelUp.h
 *
 *  Created on: Oct 15, 2013
 *      Author: ian
 */

#ifndef EVENTLEVELUP_H_
#define EVENTLEVELUP_H_

#include "Event.h"

#define LEVEL_UP_EVENT "level_up"

class EventLevelUp: public Event {
private:
	int level;
public:
	EventLevelUp(int current_level);
	~EventLevelUp();
	int getLevel();
};

#endif /* EVENTLEVELUP_H_ */
