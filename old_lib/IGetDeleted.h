/*
 * IGetDeleted.h
 *
 *  Created on: Sep 17, 2013
 *      Author: ian
 */

#ifndef IGETDELETED_H_
#define IGETDELETED_H_

#include "Object.h"
#include "Event.h"

class IGetDeleted: public Object {
private:
	int step_counter;
	int life;
public:
	IGetDeleted(int in_life);
	~IGetDeleted();
	// handle those step events
	int eventHandler(Event *p_e);
	void draw();
};

#endif /* IGETDELETED_H_ */
