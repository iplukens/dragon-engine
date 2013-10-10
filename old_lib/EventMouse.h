/*
 * EventMouse.h
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#ifndef EVENTMOUSE_H_
#define EVENTMOUSE_H_

#include "Event.h"
#define MOUSE_EVENT "__mouse__"

// The set of mouse actions recognized by Dragonfly.
enum MouseActionList {	LEFT_BUTTON_CLICK,
	LEFT_BUTTON_DOUBLECLICK,
	RIGHT_BUTTON_CLICK,
	RIGHT_BUTTON_DOUBLECLICK,
	UNDEFINED
};

class EventMouse: public Event {
private:
	MouseActionList mouse_action;
	int mouse_x;
	int mouse_y;
public:
	EventMouse(int x, int y, enum MouseActionList m);
	~EventMouse();
	MouseActionList getMouseAction();
	int getMouseX();
	int getMouseY();
	void setMouseX(int new_x);
	void setMouseY(int new_y);
	void setMouseAction(enum MouseActionList m);
};

#endif /* EVENTMOUSE_H_ */
