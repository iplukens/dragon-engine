/*
 * Event.h
 *
 *  Created on: Sep 15, 2013
 *      Author: ian
 */

#ifndef __EVENT_H_
#define __EVENT_H_

#include <string>
using std::string;

#define UNDEFINED_EVENT "__undefined__"

class Event {
private:
	string event_type; // Holds event type.
public:
// Create base event.
	Event();
// Destructor.
	virtual ~Event();
// Set event type.
	void setType(string new_type);
// Get event type.
	string getType();
};

#endif
