/*
 * Exit.h
 *
 *  Created on: Oct 15, 2013
 *      Author: rjsmieja, iplukens
 */

#ifndef EXIT_H_
#define EXIT_H_

#include "Object.h"
#include "Position.h"
#include "EventCollision.h"

class Exit: public Object {
private:
	void handleCollision (EventCollision* e);
public:
	Exit(Position pos);
	~Exit();
	int eventHandler(Event *p_e);
};

#endif /* EXIT_H_ */
