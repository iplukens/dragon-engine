/*
 * EventOut.h
 *
 *  Created on: Oct 1, 2013
 *      Author: ian
 */

#ifndef EVENTOUT_H_
#define EVENTOUT_H_

#define OUT_EVENT "__out__"

#include "Event.h"

class EventOut: public Event {
public:
	EventOut();
	~EventOut();
};

#endif /* EVENTOUT_H_ */
