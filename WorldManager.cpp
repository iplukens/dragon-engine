/*
 * WorldManager.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: ian
 */

#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "utility.h"

//bool boxIntersectsBox(Box box1, Box box2);

WorldManager &WorldManager::getInstance() {
	static WorldManager instance; // Guaranteed to be destroyed.
								  // Instantiated on first use.
	return instance;
}

int WorldManager::startUp() {
	return Manager::startUp();
}

int WorldManager::shutDown() {
	LogManager &lm = LogManager::getInstance();
	ObjectListIterator oi(&updates);
	for (oi.first(); not oi.isDone(); oi.next()) {
		delete oi.currentObject();
	}
	lm.writeLog("WorldManager shut down.");
	return 0;
}

// update all objects
void WorldManager::update() {
	LogManager &lm = LogManager::getInstance();
	// move these objects
	ObjectListIterator i(&updates);
	for (i.first(); not i.isDone(); i.next()) {
		int x = i.currentObject()->getXVelocityStep();
		int y = i.currentObject()->getYVelocityStep();
		Position old_position = i.currentObject()->getPosition();
		Position new_position = Position(old_position.getX() + x,
				old_position.getY() + y);
		moveObject(i.currentObject(), new_position);
	}
	ObjectListIterator li(&deletions);
	for (li.first(); not li.isDone(); li.next()) {
		removeObject(li.currentObject());
		delete li.currentObject();
	}
	deletions.clear();
}

// Add Object to world. Return 0 if ok, else -1.
int WorldManager::insertObject(Object *o) {
	return updates.insert(o);
}
// Remove Object from world. Return 0 if ok, else -1.
int WorldManager::removeObject(Object *o) {
	return updates.remove(o);
}

// return all objects in the world
ObjectList WorldManager::getAllObjects() {
	return updates;
}

// marks an object for deletion
// Return 0 if ok, else -1.
int WorldManager::markForDelete(Object *o) {
	if (deletions.contains(o)) {
		return -1;
	} else {
		return deletions.insert(o);
	}
}

// placeholder draw function; draws all objects!
void WorldManager::draw() {
	LogManager& log_manager = LogManager::getInstance();
	log_manager.writeLog("WorldManager::draw() running...");

	for(int i=0; i <= MAX_ALTITUDE; i++){
		log_manager.writeLog("WorldManager::draw() doing altitude of <%d>", i);
		ObjectListIterator it = updates.createIterator();

		while(!it.isDone()){
			if (it.currentObject() -> getAltitude() == i){
				log_manager.writeLog("WorldManager::draw() asked Object of type <%s> to draw", it.currentObject()->getType().c_str());
				it.currentObject() -> draw();
			}
			it.next();
		}
	}
}

WorldManager::WorldManager() {
	updates.clear();
	deletions.clear();
}

WorldManager::~WorldManager() {
	// TODO Auto-generated destructor stub
}
// Move Object.
// If no collision with solid, move ok else don't move.
// If p_go is Spectral, move ok.
// Return 0 if move ok, else -1 if collision with solid.
int WorldManager::moveObject(Object *p_o, Position where) {
	int result = 0;
	GraphicsManager &gm = GraphicsManager::getInstance();
	ObjectList collisions = isCollision(p_o, where);
	ObjectListIterator li(&collisions);
	if (p_o->getSolidness() != SPECTRAL) {
		for (li.first(); not li.isDone(); li.next()) {
			if (li.currentObject()->getSolidness() == HARD
					|| li.currentObject()->getSolidness() == SOFT) {
				result = -1;
				EventCollision* c = new EventCollision(p_o, li.currentObject(),
						where);
				Event *eve = static_cast<Event*>(c);
				onEvent(eve);
			}
		}
	}
	if (result != -1) {
		p_o->setPosition(where);
		if (where.getX() > gm.getHorizontal() || where.getX() < 0
				|| where.getY() > gm.getVertical()) {
			EventOut* c = new EventOut();
			Event *eve = static_cast<Event*>(c);
			onEvent(eve);
		}
	}
	return result;
}

// Return list of Objects collided with at Position `where'.
// Collisions only with solid Objects.
// Does not consider if p_o is solid or not.
ObjectList WorldManager::isCollision(Object *p_o, Position where) {
	// Make empty list.
	ObjectList collision_list;
	Box temp_box_1 = p_o->getBox();
	Position corner1 = temp_box_1.getCorner();
	corner1.setX(corner1.getX() + where.getX());
	corner1.setY(corner1.getY() + where.getY());
	temp_box_1.setCorner(corner1);
	// Iterate through all objects.
	ObjectListIterator i(&updates);
	for (i.first(); not i.isDone(); i.next()) {
		Object *p_temp_o = i.currentObject();
		Box temp_box = p_temp_o->getBox();
		Position corner = temp_box.getCorner();
		corner.setX(corner.getX() + p_temp_o->getPosition().getX());
		corner.setY(corner.getY() + p_temp_o->getPosition().getY());
		temp_box.setCorner(corner);
		if (p_temp_o != p_o) {
			if (boxIntersectsBox(temp_box, temp_box_1) && p_temp_o->isSolid()) {
				collision_list.insert(p_temp_o);
			}
		}
	}
	return collision_list;
}

bool WorldManager::isValid(string event_name) {
	return true;
}

Box WorldManager::getBoundary(){
	return boundary;
}

void WorldManager::setBoundary(Box new_boundary){
	boundary = new_boundary;
}

Box WorldManager::getView(){
	return view;
}

void WorldManager::setView(Box new_view){
	view = new_view;
}

