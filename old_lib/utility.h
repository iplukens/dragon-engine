//
// Utility functions to support Dragonfly and its games.
//
// Functions here do not use any attributes of any classes, so
// can stand alone.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

// System includes
#include <sstream>		// for intToString()

// Engine includes
#include "Box.h"
#include "Object.h"
#include "Position.h"

// Function prototypes

// Return true if value is between min and max (inclusive).
bool valueInRange(int value, int min, int max);

// Convert relative bounding Box for Object to absolute world Box.
Box getWorldBox(Object *p_o);

// Return true if Boxes intersect.
bool boxIntersectsBox(Box box1, Box box2);

Position worldToView(Position world_pos);

// Convert view position to world position.
Position viewToWorld(Position view_pos);

// Convert integer to string, returning string.
string intToString(int number);

#endif // __UTILITY_H__
