/*
 * InputManager.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#include "InputManager.h"
#include <curses.h>
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GraphicsManager.h"
#include "LogManager.h"

InputManager::InputManager() {
	// TODO Auto-generated constructor stub

}

InputManager &InputManager::getInstance() {
	static InputManager instance; // Guaranteed to be destroyed.
								  // Instantiated on first use.
	return instance;
}

int InputManager::startUp() {
	int result = 0;
	GraphicsManager &gm = GraphicsManager::getInstance();
	LogManager &lm = LogManager::getInstance();
	if (gm.isStarted()) {
		// Disable character echo.
		if (noecho()) {
			lm.writeLog("noecho failed");
			result = -1;
		}
		// Normal terminal input buffers until \n or \r, so disable.
		if (cbreak()) {
			lm.writeLog("cbreak failed");
			result = -1;
		}
		// turn on no delay for input
		if (nodelay(stdscr, TRUE)) {
			lm.writeLog("nodelay failed");
			result = -1;
		}
		// Disable newline so can detect “enter” key.
		if (nonl()) {
			lm.writeLog("nonl failed");
			result = -1;
		}
		// Turn off the cursor.
		if (curs_set(0) == ERR) {
			lm.writeLog("curs_set failed");
			result = 0;
		}
		// Enable mouse events – setup mask.
		if (mousemask(ALL_MOUSE_EVENTS, NULL) == ERR) {
			lm.writeLog("mousemask failed");
			result = 0;
		}
		// Other mousemask calls, as needed…
		// Enable keypad.
		if (keypad(stdscr, TRUE) == ERR) {
			lm.writeLog("keypad failed");
			result = -1;
		}
	} else {
		lm.writeLog("Graphics manager not yet started!");
		result = -1;
	}
	return result;
}

int InputManager::shutDown() {
	return Manager::shutDown();
}

bool InputManager::isValid(string event_name) {
	LogManager &lm = LogManager::getInstance();
	bool result = false;
	if (event_name == KEYBOARD_EVENT) {
		result = true;
	} else if (event_name == MOUSE_EVENT) {
		result = true;
	}
	return result;
}

void InputManager::getInput() {
	LogManager &lm = LogManager::getInstance();
	int c = getch();
	lm.writeLog("%c", c);
	if (c != ERR) {
		MEVENT m_event;
		if (c == KEY_MOUSE && getmouse(&m_event) == OK) {
			lm.writeLog("mouse event!");
			int x = m_event.x;
			int y = m_event.y;
			EventMouse me(x, y, UNDEFINED);
			if (BUTTON1_CLICKED & m_event.bstate) {
				me.setMouseAction(LEFT_BUTTON_CLICK);
			} else if (BUTTON1_DOUBLE_CLICKED & m_event.bstate) {
				me.setMouseAction(LEFT_BUTTON_DOUBLECLICK);
			} else if (BUTTON2_CLICKED & m_event.bstate) {
				me.setMouseAction(RIGHT_BUTTON_CLICK);
			} else if (BUTTON2_DOUBLE_CLICKED & m_event.bstate) {
				me.setMouseAction(RIGHT_BUTTON_DOUBLECLICK);
			}
			onEvent((Event*) &me);
		} else {
			lm.writeLog("Keyboard Event! %c", c);
			EventKeyboard* mk = new EventKeyboard(c);
			Event *eve = static_cast<Event*>(mk);
			onEvent(eve);
		}
	} else {
	}
}
