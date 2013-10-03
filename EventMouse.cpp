/*
 * EventMouse.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#include "EventMouse.h"

EventMouse::EventMouse(int x, int y, enum MouseActionList m) {
	mouse_x = x;
	mouse_y = y;
	mouse_action = m;
}

EventMouse::~EventMouse() {
	// TODO Auto-generated destructor stub
}

MouseActionList EventMouse::getMouseAction(){
	return mouse_action;
}

int EventMouse::getMouseX(){
	return mouse_x;
}

int EventMouse::getMouseY(){
	return mouse_y;
}

void EventMouse::setMouseX(int new_x){
	mouse_x = new_x;
}

void EventMouse::setMouseY(int new_y){
	mouse_y = new_y;
}

void EventMouse::setMouseAction(enum MouseActionList m){
	mouse_action = m;
}
