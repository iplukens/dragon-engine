/*
 * HealthPickup.h
 *
 *  Created on: Sep 5, 2013
 *      Author: ian
 */

#ifndef HEALTHPICKUP_H_
#define HEALTHPICKUP_H_

#include "Pickup.h"

// get more health!
class HealthPickup : public Pickup {
private:
	void hit(EventCollision *p_c);
public:
	HealthPickup(Position pos);
};

#endif /* HEALTHPICKUP_H_ */
