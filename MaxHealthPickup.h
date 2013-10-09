/*
 * MaxHealthPickup.h
 *
 *  Created on: Sep 5, 2013
 *      Author: ian
 */

#ifndef MAXHEALTHPICKUP_H_
#define MAXHEALTHPICKUP_H_

#include "Pickup.h"

// increase your ship's max health!
class MaxHealthPickup: public Pickup {
private:
	void hit(EventCollision *e);
public:
	MaxHealthPickup();
};

#endif /* MAXHEALTHPICKUP_H_ */
