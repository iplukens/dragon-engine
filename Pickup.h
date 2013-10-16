/*
 * Pickup.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Object.h"
#include "WorldManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "LevelManager.h"

// standard header for Object that the hero can pick up
class Pickup: public Object {
protected:
	virtual void hit(EventCollision *p_c){};
public:
	virtual int eventHandler(Event *p_e) {
		if (p_e->getType() == COLLISION_EVENT) {
			EventCollision *p_collision_event =
					static_cast<EventCollision *>(p_e);
			hit(p_collision_event);
			return 1;
		}
		return 0;
	}

	virtual ~Pickup(){
		LevelManager &level_manager = LevelManager::getInstance();

		level_manager.objectDelete(this);
	}
};

#endif /* PICKUP_H_ */
