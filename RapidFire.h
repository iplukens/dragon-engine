/*
 * RapidFire.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef RAPIDFIRE_H_
#define RAPIDFIRE_H_

#include "Pickup.h"

// Shoot faster!
class RapidFire: public Pickup {
private:
	void hit(EventCollision *p_c);
public:
	RapidFire();
};

#endif /* RAPIDFIRE_H_ */
