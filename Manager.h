/*
 * Manager.h
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifndef __MANAGER_H_
#define __MANAGER_H_

#include "ObjectList.h"
using std::string;

#define MAX_EVENTS 100

class Manager {
private:
	int event_count; // Number of events.
	string event_name[MAX_EVENTS]; // List of events.
	ObjectList obj_list[MAX_EVENTS]; // Objects interested in event
	// check if an event is valid
	virtual bool isValid(string event_name);

protected:
	bool is_started;

public:
	Manager();
	virtual ~Manager();

	// start okay = 0
	// bad start = negative number
	virtual int startUp();

	// shutdown
	virtual int shutDown();

	// Indicate interest in event.
	// Return 0 if ok, else -1.
	// (Note, doesn't check to see if Object is already registered.)
	int registerInterest(Object *p_o, string event_type);
	// Indicate no more interest in event.
	// Return 0 if ok, else -1.
	int unregisterInterest(Object *p_o, string event_type);
	// Send event to all interested objects.
	void onEvent(Event *p_event);

	// check if game is going (true if yes; false if no)
	bool isStarted();
};

#endif /* MANAGER_H_ */
