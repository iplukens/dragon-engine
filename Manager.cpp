/**
 * Manager.cpp
 *
 * auth: ian lukens
 *
 */

#include "Manager.h"
#include "ObjectListIterator.h"
#include "LogManager.h"

Manager::Manager() {
	is_started = false;
	event_count = 0;
}

Manager::~Manager() {
}

// start okay = 0
// bad start = negative number
int Manager::startUp() {
	is_started = true;
	return 0;
}

// shutdown
int Manager::shutDown() {
	is_started = false;
	return 0;
}

// check if game is going (true if yes; false if no)
bool Manager::isStarted() {
	return is_started;
}

// return 0 if okay; else -1
int Manager::registerInterest(Object *p_o, string event_type) {
	int result = -1;
	LogManager &lm = LogManager::getInstance();
	if (isValid(event_type)) {
// Check if previously added this event.
		for (int i = 0; i < event_count; i++) {
			if (event_name[i] == event_type) {
				obj_list[i].insert(p_o);
				return 0;
			}
		}
// Otherwise, this is a new event.
		if (event_count < MAX_EVENTS) {
			event_name[event_count] = event_type;
			obj_list[event_count].insert(p_o);
			event_count++;
			return 0;
		}
	}
	return result;
}

int Manager::unregisterInterest(Object *p_o, string event_type) {
	int result = -1;
// Check if previously added this event.
	for (int i = 0; i < event_count; i++) {
		if (event_name[i] == event_type) {
			obj_list[i].remove(p_o);
			result = 0;
			if (obj_list[i].isEmpty()) {
				event_count--;
				for (int j = i; j < event_count; j++) {
					event_name[j] = event_name[j + 1];
					obj_list[j] = obj_list[j + 1];
				}
			}
			break;
		}
	}
// Otherwise, this is a not an event that we have.
	return result;
}

// Send event to all interested objects.
void Manager::onEvent(Event *p_event) {
	for (int i = 0; i < event_count; i++) {
		if (event_name[i] == p_event->getType()) {
			ObjectListIterator li(&obj_list[i]);
			for (li.first(); not li.isDone(); li.next()) {
				li.currentObject()->eventHandler(p_event);
			}
			break;
		}
	}
}

// checks if an event is valid
bool Manager::isValid(string event_name) {
	return false;
}
