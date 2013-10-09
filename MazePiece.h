/*
 * MazePiece.h
 *
 *  Created on: Oct 8, 2013
 *      Author: ian
 */

#ifndef MAZE_PIECE_H_
#define MAZE_PIECE_H_

#include "Object.h"
#include "Position.h"

class MazePiece : public Object {

public:
	MazePiece(Position pos);
	void draw(void);
};

#endif /* MAZE_H_ */
