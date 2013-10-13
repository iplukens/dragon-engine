/*
 * PointsPickup.h
 *
 *  Created on: October 13, 2013
 *      Author: rjsmieja, iplukens
 */

#ifndef POINTS_PICKUP_H_
#define POINTS_PICKUP_H_

#define POINTS_PICKUP_AMOUNT 30

#include "Pickup.h"

// Bonus points
class PointsPickup: public Pickup {
private:
	void hit(EventCollision *p_c);
public:
	PointsPickup(Position pos);
};

#endif /* POINTS_PICKUP_H_ */
