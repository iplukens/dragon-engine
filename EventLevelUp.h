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
public:
	EventLevelUp();
	~EventLevelUp();
};

#endif /* EVENTLEVELUP_H_ */
