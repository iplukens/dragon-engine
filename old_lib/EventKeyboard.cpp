/*
 * EventKeyboard.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#include "EventKeyboard.h"

EventKeyboard::EventKeyboard(int key) {
	setType(KEYBOARD_EVENT);
	key_val = key;
}

EventKeyboard::~EventKeyboard() {
	// TODO Auto-generated destructor stub
}

int EventKeyboard::getKey(){
	return key_val;
}

int EventKeyboard::setKey(int new_key){
	key_val = new_key;
	return key_val;
}
