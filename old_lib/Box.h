/*
 * Box.h
 *
 *  Created on: Oct 3, 2013
 *      Author: ian
 */

#ifndef BOX_H_
#define BOX_H_

#include "Position.h"
class Box {
private:
	Position corner;
// Upper left corner of box.
	int horizontal;
// Horizontal dimension.
	int vertical;
// Vertical dimension.
public:
// Create box with (0,0) for the corner, and 0 for horiz and vert.
	Box();
// Create box with an upper-left corner, horiz and vert sizes.
	Box(Position init_corner, int init_horizontal, int init_vertical);
// Get upper left corner of box.
	Position getCorner();
// Set upper left corner of box.
	void
	setCorner(Position new_corner);
// Get horizontal size of box.
	int
	getHorizontal();
// Set horizontal size of box.
	void
	setHorizontal(int new_horizontal);
// Get vertical size of box.
	int
	getVertical();
// Set vertical size of box.
	void
	setVertical(int new_vertical);
};

#endif /* BOX_H_ */
