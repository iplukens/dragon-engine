/*
 * EventStep.h
 *
 *  Created on: Sep 15, 2013
 *      Author: ian
 */

#ifndef __EVENTSTEP_H_
#define __EVENTSTEP_H_

#define EVENT_STEP "__step__"

#include "Event.h"

class EventStep : public Event {
public:
	EventStep();
	~EventStep();
};

#endif /* EVENTSTEP_H_ */
