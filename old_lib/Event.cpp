/*
 * Event.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: ian
 */

#include "Event.h"

Event::Event() {
	event_type = UNDEFINED_EVENT;
}

Event::~Event(){
}

void Event::setType(string new_type){
	event_type = new_type;
}

string Event::getType(){
	return event_type;
}
