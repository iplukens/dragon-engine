/*
 * WorldManager.h
 *
 *  Created on: Sep 15, 2013
 *      Author: ian
 */

#ifndef __WORLDMANAGER_H_
#define __WORLDMANAGER_H_

#include "Object.h"
#include "ObjectList.h"
#include "Manager.h"

#define MAX_ALTITUDE 4

class WorldManager : public Manager {
private:
	ObjectList updates;
	ObjectList deletions;
	Box boundary;                 // World boundary.
	Box view;                     // Player view of world.
	WorldManager();
	WorldManager (WorldManager const&);    ///< Don't allow copy.
	void operator=(WorldManager const&); ///< Don't allow assignment.
public:
	static WorldManager &getInstance();
	~WorldManager();
	int shutDown();
	int startUp();
	void draw();
	// update all objects
	void update();
	// Add Object to world. Return 0 if ok, else -1.
	int insertObject(Object *o);
	// Remove Object from world. Return 0 if ok, else -1.
	int removeObject(Object *o);
	// return all the objects in the world
	ObjectList getAllObjects();
	// marks an object for deletion
	// Return 0 if ok, else -1.
	int markForDelete(Object *o);
	// Return list of Objects collided with at Position `where'.
	// Collisions only with solid Objects.
	// Does not consider if p_o is solid or not.
	ObjectList isCollision(Object *p_o, Position where);
	// Move Object.
	// If no collision with solid, move ok else don't move.
	// If p_go is Spectral, move ok.
	// Return 0 if move ok, else -1 if collision with solid.
	int moveObject(Object *p_o, Position where);

	bool isValid(string event_name);

	// Get game world boundary.
	Box getBoundary();

	// Set game world boundary.
	void setBoundary(Box new_boundary);

	// Get player view of game world.
	Box getView();

	// Set player view of game world.
	void setView(Box new_view);
};

#endif /* WORLDMANAGER_H_ */
