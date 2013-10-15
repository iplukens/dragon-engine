/*
 * Points.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#include "Points.h"
#include "EventStep.h"
#include "GraphicsManager.h"

Points::Points() {
	setLocation(TOP_RIGHT);
	setViewString (POINTS_STRING);
	setType(POINTS_STRING);
	setColor (COLOR_YELLOW);
	step_count = 0;
}

int Points::eventHandler(Event *p_e) {
	if (ViewObject::eventHandler(p_e)) {
		return 1;
	}
	if(p_e->getType() == STEP_EVENT)
		// probably will level up if getValue() == some_number
		return 1;
	return 0;
}
