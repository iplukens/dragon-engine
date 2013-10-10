/*
 * EventKeyboard.h
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#ifndef __EVENTKEYBOARD_H_
#define __EVENTKEYBOARD_H_

#include "Event.h"

#define KEYBOARD_EVENT "__keyboard__"

class EventKeyboard : public Event {
private:
	int key_val;
public:
	EventKeyboard(int key);
	~EventKeyboard();
	int getKey();
	int setKey(int new_key);
};

#endif /* EVENTKEYBOARD_H_ */
