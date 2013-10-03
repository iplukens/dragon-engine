/*
 * Position.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#include "Position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int init_x, int init_y) {
	x = init_x;
	y = init_y;
}

int Position::getX() {
	return x;
}

void Position::setX(int new_x) {
	x = new_x; ///< Set horizontal coordinate.
}
int Position::getY() {
	return y; ///< Get vertical coordinate.
}
void Position::setY(int new_y) {
	y = new_y; ///< Set vertical coordinate.
}
void Position::setXY(int new_x, int new_y) {
	x = new_x;
	y = new_y; ///< Set horizontal & vertical coordinates.
}
