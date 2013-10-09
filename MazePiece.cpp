//
// MazePiece.cpp
//

#include "MazePiece.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

#define MAZE_CHAR 178

MazePiece::MazePiece(Position pos) {
	setType("Maze");
	setSolidness(HARD);
	WorldManager &world_manager = WorldManager::getInstance();
	setPosition(pos);
}

void MazePiece::draw() {
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	graphics_manager.drawCh(getPosition(), MAZE_CHAR);
}
