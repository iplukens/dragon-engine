/*
 * EndOfWorlds.h
 *
 *  Created on: Sep 17, 2013
 *      Author: ian
 */

#ifndef ENDOFWORLDS_H_
#define ENDOFWORLDS_H_

#include "Object.h"
#include "Event.h"

class EndOfWorlds : public Object {
private:
	int life;
	int step_count;
public:
	int eventHandler(Event *p_e);
	EndOfWorlds(int in_life, int x, int y);
	~EndOfWorlds();
	void draw();
};

#endif /* ENDOFWORLDS_H_ */
