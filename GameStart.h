/*
 * GameStart.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef GAMESTART_H_
#define GAMESTART_H_

#define MENU_LEVEL 1
#define PLAY_LEVEL 2

#include "ViewObject.h"

class GameStart: public ViewObject {

protected:
	void step();
	void start();

public:
	GameStart();
	int eventHandler(Event *e);
	void draw();
};

#endif /* GAMESTART_H_ */
