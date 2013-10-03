/*
 * Box.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: ian
 */

#include "Box.h"

Box::Box() {
	horizontal = 0;
	vertical = 0;
	corner = Position(0, 0);
}

// Create box with an upper-left corner, horiz and vert sizes.
	Box::Box(Position init_corner, int init_horizontal, int init_vertical){
		horizontal = init_horizontal;
		vertical = init_vertical;
		corner = init_corner;
	}
// Get upper left corner of box.
	Position Box::getCorner(){
		return corner;
	}
// Set upper left corner of box.
	void Box::setCorner(Position new_corner){
		corner = new_corner;
	}
// Get horizontal size of box.
	int Box::getHorizontal(){
		return horizontal;
	}
// Set horizontal size of box.
	void Box::setHorizontal(int new_horizontal){
		horizontal = new_horizontal;
	}
// Get vertical size of box.
	int Box::getVertical(){
		return vertical;
	}
// Set vertical size of box.
	void Box::setVertical(int new_vertical){
		vertical = new_vertical;
	}
