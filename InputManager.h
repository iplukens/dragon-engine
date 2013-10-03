/*
 * InputManager.h
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#ifndef __INPUTMANAGER_H_
#define __INPUTMANAGER_H_

#include "Manager.h"

class InputManager: public Manager {
private:
	InputManager();
	InputManager(InputManager const&);
	void operator=(InputManager const&);
public:
// Get the one and only instance of the InputManager.
	static InputManager &getInstance();
// Get terminal ready to capture input.
// Return 0 if ok, else return negative number.
	int startUp();
// Revert back to normal terminal mode.
	int shutDown();
// Input manager only accepts keyboard and mouse events.
// Return false if not one of them.
	bool isValid(string event_name);
// Get input from the keyboard and mouse.
// For each object interested, pass event along.
	void getInput();
};

#endif /* INPUTMANAGER_H_ */
